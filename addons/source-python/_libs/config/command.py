# ../_libs/config/command.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Translations
from translations.manager import LanguageManager
from translations.strings import TranslationStrings


# =============================================================================
# >> CLASSES
# =============================================================================
class CommandManager(object):
    '''Class used to store a command instance'''

    def __init__(self, name, description):
        '''Called on instanciation'''

        # Store the base attributes for the command
        self.name = name
        self.description = description

        # Is the given description a TranslationStrings instance?
        if isinstance(self.description, TranslationStrings):

            # Store the description as the proper language string
            self.description = self.description.get_string(
                LanguageManager.default)
