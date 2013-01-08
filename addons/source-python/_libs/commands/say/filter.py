# ../_libs/commands/say/filter.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import AutoUnload


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
SayFilterList = list()


# =============================================================================
# >> CLASSES
# =============================================================================
class SayFilter(AutoUnload):
    '''Class used to register a SayFilter'''

    def __init__(self, callback):
        '''Store the callback and register the say filter'''

        # Is the callback callable?
        if not callable(callback):

            # Raise an error
            raise TypeError(
                "'" + type(callback).__name__ + "' object is not callable")

        # Store the callback
        self.callback = callback

        # Register the say filter
        SayFilterList.append(self)

    def __call__(self, index, teamonly, CCommand):
        '''Calls the say filter with the provided arguments'''
        return self.callback(index, teamonly, CCommand)

    def _unload_instance(self):
        '''Unregisters the say filter'''
        SayFilterList.remove(self)
