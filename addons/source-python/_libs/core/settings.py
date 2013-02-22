# ../_libs/core/settings.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Configobj
from configobj import ConfigObj

# Source.Python Imports
from paths import GAME_PATH
from paths import CFG_PATH
#   Auth
from auth.paths import AUTH_PROVIDER_PATH
#   Translations
from translations.strings import LangStrings


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the core language strings
_core_strings = LangStrings('_core/core_settings_strings')

# Get a list of auth providers
_auth_providers = [
    provider.namebase for provider in AUTH_PROVIDER_PATH.files() +
    AUTH_PROVIDER_PATH.dirs() if not provider.namebase.startswith('__')]


# =============================================================================
# >> CLASSES
# =============================================================================
class _CoreSettings(ConfigObj):
    '''Class used to store core settings'''

    def __init__(self, infile):
        '''
            Adds missing items and sets their comments to the server's language
        '''

        # Import the file
        super(_CoreSettings, self).__init__(infile)

        # Check the base settings
        self._check_base_settings()

        # Check the auth settings
        self._check_auth_settings()

        # Add the initial comment
        self.initial_comment = ['../' + self.filename.replace(GAME_PATH, '')]

        # Loop through all sections
        for section in self:

            # Add a blank line prior to the section
            self.comments[section] = ['']

        # Write the file
        self.write()

    def _check_base_settings(self):
        '''Adds base settings if they are missing'''

        # Are there any base settings in the file?
        if not 'BASE_SETTINGS' in self:

            # Add the base settings
            self['BASE_SETTINGS'] = {}

        # Is there a language setting?
        if not 'language' in self['BASE_SETTINGS']:

            # Add the language setting
            self['BASE_SETTINGS']['language'] = 'english'

        # Get the server's language
        self._language = self['BASE_SETTINGS']['language']

        # Set the language comments
        self['BASE_SETTINGS'].comments['language'] = _core_strings[
            'language'].get_string(self._language).splitlines()

    def _check_auth_settings(self):
        '''Adds auth settings if they are missing'''

        # Are there any auth settings in the file?
        if not 'AUTH_SETTINGS' in self:

            # Add the auth settings
            self['AUTH_SETTINGS'] = {}

        # Is there a providers setting?
        if not 'providers' in self['AUTH_SETTINGS']:

            # Add the providers setting
            self['AUTH_SETTINGS']['providers'] = ''

        # Set the auth provider comments
        self['AUTH_SETTINGS'].comments['providers'] = _core_strings[
            'providers'].get_string(
            self._language, providers='\n'.join(_auth_providers),
            single=_auth_providers[0],
            multiple=' '.join(_auth_providers[:3])).splitlines()

# Get the _CoreSettings instance
CoreSettings = _CoreSettings(CFG_PATH.joinpath('core_settings.ini'))
