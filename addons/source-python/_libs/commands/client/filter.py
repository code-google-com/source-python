# ../_libs/commands/client/filter.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import AutoUnload
#   Commands
from commands.client.manager import ClientCommandRegistry


# =============================================================================
# >> CLASSES
# =============================================================================
class ClientCommandFilter(AutoUnload):
    '''Class used to register a client command filter'''

    def __init__(self, callback):
        '''Store the callback and registers the client command filter'''

        # Is the callback callable?
        if not callable(callback):

            # Raise an error
            raise TypeError(
                "'" + type(callback).__name__ + "' object is not callable")

        # Store the callback
        self.callback = callback

        # Register the client command filter
        ClientCommandRegistry.register_filter(self.callback)

    def _unload_instance(self):
        '''Unregisters the client command filter'''
        ClientCommandRegistry.unregister_filter(self.callback)
