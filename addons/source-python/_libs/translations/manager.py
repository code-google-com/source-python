# ../_libs/translations/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Configobj
from configobj import ConfigObj

# Source.Python Imports
from paths import DATA_PATH


# =============================================================================
# >> CLASSES
# =============================================================================
class _LanguageManager(ConfigObj):
    '''Dictionary class used to store languages and their shortnames'''

    # en should always be used as the "fallback",
    # since most addons will have English values
    fallback = 'en'

    def _register_default_language(self, language):
        '''Registers the default language for the current server'''

        # Get the shortname for the given language
        language = self.get_language(language)

        # Was a language returned?
        if not language is None:

            # Set the default language
            self.default = language

        # Was no language shortname found?
        else:

            # Set the default language to English
            self.default = 'en'

    def get_language(self, language):
        '''Returns the shortname for the given language'''

        # Is the given language an item in the dictionary?
        if language in self:

            # Return the language's shortname
            return self[language]

        # Is the given language a known shortname?
        if language in self.values():

            # Return the shortname
            return language

        # If the value is not found, return None
        return None

# Get the _LanguageManager instance for the server's languages file
LanguageManager = _LanguageManager(DATA_PATH.joinpath('languages.ini'))
