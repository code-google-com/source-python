# ../_libs/commands/say/filter.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from core import AutoUnload
#   Commands
from commands.say.manager import SayCommandRegistry


# =============================================================================
# >> CLASSES
# =============================================================================
class SayFilter(AutoUnload):
    '''Class used to register a say filter'''

    def __init__(self, callback):
        '''Store the callback and registers the say filter'''

        # Is the callback callable?
        if not callable(callback):

            # Raise an error
            raise TypeError(
                "'" + type(callback).__name__ + "' object is not callable")

        # Store the callback
        self.callback = callback

        # Register the say filter
        SayCommandRegistry.register_filter(self.callback)

    def _unload_instance(self):
        '''Unregisters the say filter'''
        SayCommandRegistry.unregister_filter(self.callback)
