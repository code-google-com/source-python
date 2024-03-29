"""Building blocks for installers.

When used as a script, this module installs a release thanks to info
obtained from an index (e.g. PyPI), with dependencies.

This is a higher-level module built on packaging.database and
packaging.pypi.
"""
import os
import sys
import stat
import errno
import shutil
import logging
import tempfile
from sysconfig import get_config_var, get_path, is_python_build

from packaging import logger
from packaging.dist import Distribution
from packaging.util import (_is_archive_file, ask, get_install_method,
                            egginfo_to_distinfo)
from packaging.pypi import wrapper
from packaging.version import get_version_predicate
from packaging.database import get_distributions, get_distribution
from packaging.depgraph import generate_graph

from packaging.errors import (PackagingError, InstallationException,
                              InstallationConflict, CCompilerError)
from packaging.pypi.errors import ProjectNotFound, ReleaseNotFound
from packaging import database


__all__ = ['install_dists', 'install_from_infos', 'get_infos', 'remove',
           'install', 'install_local_project']


def _move_files(files, destination):
    """Move the list of files in the destination folder, keeping the same
    structure.

    Return a list of tuple (old, new) emplacement of files

    :param files: a list of files to move.
    :param destination: the destination directory to put on the files.
    """

    for old in files:
        filename = os.path.split(old)[-1]
        new = os.path.join(destination, filename)
        # try to make the paths.
        try:
            os.makedirs(os.path.dirname(new))
        except OSError as e:
            if e.errno != errno.EEXIST:
                raise
        os.rename(old, new)
        yield old, new


def _run_distutils_install(path):
    # backward compat: using setuptools or plain-distutils
    cmd = '%s setup.py install --record=%s'
    record_file = os.path.join(path, 'RECORD')
    os.system(cmd % (sys.executable, record_file))
    if not os.path.exists(record_file):
        raise ValueError('failed to install')
    else:
        egginfo_to_distinfo(record_file, remove_egginfo=True)


def _run_setuptools_install(path):
    cmd = '%s setup.py install --record=%s --single-version-externally-managed'
    record_file = os.path.join(path, 'RECORD')

    os.system(cmd % (sys.executable, record_file))
    if not os.path.exists(record_file):
        raise ValueError('failed to install')
    else:
        egginfo_to_distinfo(record_file, remove_egginfo=True)


def _run_packaging_install(path):
    # XXX check for a valid setup.cfg?
    dist = Distribution()
    dist.parse_config_files()
    try:
        dist.run_command('install_dist')
        name = dist.metadata['Name']
        return database.get_distribution(name) is not None
    except (IOError, os.error, PackagingError, CCompilerError) as msg:
        raise ValueError("Failed to install, " + str(msg))


def _install_dist(dist, path):
    """Install a distribution into a path.

    This:

    * unpack the distribution
    * copy the files in "path"
    * determine if the distribution is packaging or distutils1.
    """
    where = dist.unpack()

    if where is None:
        raise ValueError('Cannot locate the unpacked archive')

    return _run_install_from_archive(where)


def install_local_project(path):
    """Install a distribution from a source directory.

    If the source directory contains a setup.py install using distutils1.
    If a setup.cfg is found, install using the install_dist command.

    Returns True on success, False on Failure.
    """
    path = os.path.abspath(path)
    if os.path.isdir(path):
        logger.info('Installing from source directory: %r', path)
        return _run_install_from_dir(path)
    elif _is_archive_file(path):
        logger.info('Installing from archive: %r', path)
        _unpacked_dir = tempfile.mkdtemp()
        try:
            shutil.unpack_archive(path, _unpacked_dir)
            return _run_install_from_archive(_unpacked_dir)
        finally:
            shutil.rmtree(_unpacked_dir)
    else:
        logger.warning('No project to install.')
        return False


def _run_install_from_archive(source_dir):
    # XXX need a better way
    for item in os.listdir(source_dir):
        fullpath = os.path.join(source_dir, item)
        if os.path.isdir(fullpath):
            source_dir = fullpath
            break
    return _run_install_from_dir(source_dir)


install_methods = {
    'packaging': _run_packaging_install,
    'setuptools': _run_setuptools_install,
    'distutils': _run_distutils_install}


def _run_install_from_dir(source_dir):
    old_dir = os.getcwd()
    os.chdir(source_dir)
    install_method = get_install_method(source_dir)
    func = install_methods[install_method]
    try:
        func = install_methods[install_method]
        try:
            func(source_dir)
            return True
        except ValueError as err:
            # failed to install
            logger.info(str(err))
            return False
    finally:
        os.chdir(old_dir)


def install_dists(dists, path, paths=None):
    """Install all distributions provided in dists, with the given prefix.

    If an error occurs while installing one of the distributions, uninstall all
    the installed distribution (in the context if this function).

    Return a list of installed dists.

    :param dists: distributions to install
    :param path: base path to install distribution in
    :param paths: list of paths (defaults to sys.path) to look for info
    """

    installed_dists = []
    for dist in dists:
        logger.info('Installing %r %s...', dist.name, dist.version)
        try:
            _install_dist(dist, path)
            installed_dists.append(dist)
        except Exception as e:
            logger.info('Failed: %s', e)

            # reverting
            for installed_dist in installed_dists:
                logger.info('Reverting %r', installed_dist)
                remove(installed_dist.name, paths)
            raise e
    return installed_dists


def install_from_infos(install_path=None, install=[], remove=[], conflicts=[],
                       paths=None):
    """Install and remove the given distributions.

    The function signature is made to be compatible with the one of get_infos.
    The aim of this script is to povide a way to install/remove what's asked,
    and to rollback if needed.

    So, it's not possible to be in an inconsistant state, it could be either
    installed, either uninstalled, not half-installed.

    The process follow those steps:

        1. Move all distributions that will be removed in a temporary location
        2. Install all the distributions that will be installed in a temp. loc.
        3. If the installation fails, rollback (eg. move back) those
           distributions, or remove what have been installed.
        4. Else, move the distributions to the right locations, and remove for
           real the distributions thats need to be removed.

    :param install_path: the installation path where we want to install the
                         distributions.
    :param install: list of distributions that will be installed; install_path
                    must be provided if this list is not empty.
    :param remove: list of distributions that will be removed.
    :param conflicts: list of conflicting distributions, eg. that will be in
                      conflict once the install and remove distribution will be
                      processed.
    :param paths: list of paths (defaults to sys.path) to look for info
    """
    # first of all, if we have conflicts, stop here.
    if conflicts:
        raise InstallationConflict(conflicts)

    if install and not install_path:
        raise ValueError("Distributions are to be installed but `install_path`"
                         " is not provided.")

    # before removing the files, we will start by moving them away
    # then, if any error occurs, we could replace them in the good place.
    temp_files = {}  # contains lists of {dist: (old, new)} paths
    temp_dir = None
    if remove:
        temp_dir = tempfile.mkdtemp()
        for dist in remove:
            files = dist.list_installed_files()
            temp_files[dist] = _move_files(files, temp_dir)
    try:
        if install:
            install_dists(install, install_path, paths)
    except:
        # if an error occurs, put back the files in the right place.
        for files in temp_files.values():
            for old, new in files:
                shutil.move(new, old)
        if temp_dir:
            shutil.rmtree(temp_dir)
        # now re-raising
        raise

    # we can remove them for good
    for files in temp_files.values():
        for old, new in files:
            os.remove(new)
    if temp_dir:
        shutil.rmtree(temp_dir)


def _get_setuptools_deps(release):
    # NotImplementedError
    pass


def get_infos(requirements, index=None, installed=None, prefer_final=True):
    """Return the informations on what's going to be installed and upgraded.

    :param requirements: is a *string* containing the requirements for this
                         project (for instance "FooBar 1.1" or "BarBaz (<1.2)")
    :param index: If an index is specified, use this one, otherwise, use
                  :class index.ClientWrapper: to get project metadatas.
    :param installed: a list of already installed distributions.
    :param prefer_final: when picking up the releases, prefer a "final" one
                         over a beta/alpha/etc one.

    The results are returned in a dict, containing all the operations
    needed to install the given requirements::

        >>> get_install_info("FooBar (<=1.2)")
        {'install': [<FooBar 1.1>], 'remove': [], 'conflict': []}

    Conflict contains all the conflicting distributions, if there is a
    conflict.
    """
    # this function does several things:
    # 1. get a release specified by the requirements
    # 2. gather its metadata, using setuptools compatibility if needed
    # 3. compare this tree with what is currently installed on the system,
    #    return the requirements of what is missing
    # 4. do that recursively and merge back the results
    # 5. return a dict containing information about what is needed to install
    #    or remove

    if not installed:
        logger.debug('Reading installed distributions')
        installed = list(get_distributions(use_egg_info=True))

    infos = {'install': [], 'remove': [], 'conflict': []}
    # Is a compatible version of the project already installed ?
    predicate = get_version_predicate(requirements)
    found = False

    # check that the project isn't already installed
    for installed_project in installed:
        # is it a compatible project ?
        if predicate.name.lower() != installed_project.name.lower():
            continue
        found = True
        logger.info('Found %r %s', installed_project.name,
                    installed_project.version)

        # if we already have something installed, check it matches the
        # requirements
        if predicate.match(installed_project.version):
            return infos
        break

    if not found:
        logger.debug('Project not installed')

    if not index:
        index = wrapper.ClientWrapper()

    if not installed:
        installed = get_distributions(use_egg_info=True)

    # Get all the releases that match the requirements
    try:
        release = index.get_release(requirements)
    except (ReleaseNotFound, ProjectNotFound):
        raise InstallationException('Release not found: %r' % requirements)

    if release is None:
        logger.info('Could not find a matching project')
        return infos

    metadata = release.fetch_metadata()

    # we need to build setuptools deps if any
    if 'requires_dist' not in metadata:
        metadata['requires_dist'] = _get_setuptools_deps(release)

    # build the dependency graph with local and required dependencies
    dists = list(installed)
    dists.append(release)
    depgraph = generate_graph(dists)

    # Get what the missing deps are
    dists = depgraph.missing[release]
    if dists:
        logger.info("Missing dependencies found, retrieving metadata")
        # we have missing deps
        for dist in dists:
            _update_infos(infos, get_infos(dist, index, installed))

    # Fill in the infos
    existing = [d for d in installed if d.name == release.name]
    if existing:
        infos['remove'].append(existing[0])
        infos['conflict'].extend(depgraph.reverse_list[existing[0]])
    infos['install'].append(release)
    return infos


def _update_infos(infos, new_infos):
    """extends the lists contained in the `info` dict with those contained
    in the `new_info` one
    """
    for key, value in infos.items():
        if key in new_infos:
            infos[key].extend(new_infos[key])


def remove(project_name, paths=None, auto_confirm=True):
    """Removes a single project from the installation.

    Returns True on success
    """
    dist = get_distribution(project_name, use_egg_info=True, paths=paths)
    if dist is None:
        raise PackagingError('Distribution %r not found' % project_name)
    files = dist.list_installed_files(local=True)
    rmdirs = []
    rmfiles = []
    tmp = tempfile.mkdtemp(prefix=project_name + '-uninstall')

    def _move_file(source, target):
        try:
            os.rename(source, target)
        except OSError as err:
            return err
        return None

    success = True
    error = None
    try:
        for file_, md5, size in files:
            if os.path.isfile(file_):
                dirname, filename = os.path.split(file_)
                tmpfile = os.path.join(tmp, filename)
                try:
                    error = _move_file(file_, tmpfile)
                    if error is not None:
                        success = False
                        break
                finally:
                    if not os.path.isfile(file_):
                        os.rename(tmpfile, file_)
                if file_ not in rmfiles:
                    rmfiles.append(file_)
                if dirname not in rmdirs:
                    rmdirs.append(dirname)
    finally:
        shutil.rmtree(tmp)

    if not success:
        logger.info('%r cannot be removed.', project_name)
        logger.info('Error: %s', error)
        return False

    logger.info('Removing %r: ', project_name)

    for file_ in rmfiles:
        logger.info('  %s', file_)

    # Taken from the pip project
    if auto_confirm:
        response = 'y'
    else:
        response = ask('Proceed (y/n)? ', ('y', 'n'))

    if response == 'y':
        file_count = 0
        for file_ in rmfiles:
            os.remove(file_)
            file_count += 1

        dir_count = 0
        for dirname in rmdirs:
            if not os.path.exists(dirname):
                # could
                continue

            files_count = 0
            for root, dir, files in os.walk(dirname):
                files_count += len(files)

            if files_count > 0:
                # XXX Warning
                continue

            # empty dirs with only empty dirs
            if os.stat(dirname).st_mode & stat.S_IWUSR:
                # XXX Add a callable in shutil.rmtree to count
                # the number of deleted elements
                shutil.rmtree(dirname)
                dir_count += 1

        # removing the top path
        # XXX count it ?
        if os.path.exists(dist.path):
            shutil.rmtree(dist.path)

        logger.info('Success: removed %d files and %d dirs',
                    file_count, dir_count)

    return True


def install(project):
    """Installs a project.

    Returns True on success, False on failure
    """
    if is_python_build():
        # Python would try to install into the site-packages directory under
        # $PREFIX, but when running from an uninstalled code checkout we don't
        # want to create directories under the installation root
        message = ('installing third-party projects from an uninstalled '
                   'Python is not supported')
        logger.error(message)
        return False

    logger.info('Checking the installation location...')
    purelib_path = get_path('purelib')

    # trying to write a file there
    try:
        with tempfile.NamedTemporaryFile(suffix=project,
                                         dir=purelib_path) as testfile:
            testfile.write(b'test')
    except OSError:
        # FIXME this should check the errno, or be removed altogether (race
        # condition: the directory permissions could be changed between here
        # and the actual install)
        logger.info('Unable to write in "%s". Do you have the permissions ?'
                    % purelib_path)
        return False

    logger.info('Getting information about %r...', project)
    try:
        info = get_infos(project)
    except InstallationException:
        logger.info('Cound not find %r', project)
        return False

    if info['install'] == []:
        logger.info('Nothing to install')
        return False

    install_path = get_config_var('base')
    try:
        install_from_infos(install_path,
                           info['install'], info['remove'], info['conflict'])

    except InstallationConflict as e:
        if logger.isEnabledFor(logging.INFO):
            projects = ('%r %s' % (p.name, p.version) for p in e.args[0])
            logger.info('%r conflicts with %s', project, ','.join(projects))

    return True
