# ../_libs/addons/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
import os

# Source.Python Imports
from paths import addon_path


# =============================================================================
# >> CLASSES
# =============================================================================
class _AddonManagementDictionary(dict):
    def __getitem__(self, addon):
        if addon in self:
            return super(_AddonManagementDictionary, self).__getitem__(addon)
        value = self[addon] = _LoadedAddon(addon)
        return value

    def __delitem__(self, addon_name):
        if not addon_name in self:
            return
        print('[SP] Unloading "%s"' % addon_name)
        addon_import = addon_name + '.' + addon_name
        if addon_import in sys.modules:
            del sys.modules[addon_import]
        super(_AddonManagementDictionary, self).__delitem__(addon)

AddonManager = _AddonManagementDictionary()


class _LoadedAddon(object):
    def __init__(self, addon_name):
        file_path = '%s/%s/%s.py' % (addon_path, addon_name, addon_name)
        if not os.path.isfile(file_path):
            print(
                '[SP] Unable to load "%s", missing file ' % addon_name +
                '../addons/source-python/%s/%s.py' % (addon_name, addon_name))
            raise ImportError
        print('[SP] Loaded "%s"' % addon_name)
        try:
            addon = __import__(addon_name + '.' + addon_name)
            self.globals = dict(addon.__dict__)
        except ImportError as error:
            raise
