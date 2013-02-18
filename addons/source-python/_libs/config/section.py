# ../_libs/config/section.py

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
class SectionManager(object):
    '''Class used to store a section instance'''

    def __init__(self, name, separator):
        '''Called on instanciation'''

        # Store the base attributes for the section
        self.name = name
        self.separator = separator

        # Is the given name a TranslationStrings instance?
        if isinstance(self.name, TranslationStrings):

            # Store the name as the proper language string
            self.name = self.name.get_string(LanguageManager.default)
