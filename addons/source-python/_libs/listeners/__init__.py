# ../_libs/listeners/__init__.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import AutoUnload
#   Listeners
from listeners.tick import TickListeners


# =============================================================================
# >> CLASSES
# =============================================================================
class Tick(AutoUnload):
    '''Decorator class used to register/unregister a tick listener'''

    def __init__(self, callback):
        '''Store the callback and register the tick listener'''

        # Is the callback callable?
        if not callable(callback):

            # Raise an error
            raise TypeError(
                "'" + type(callback).__name__ + "' object is not callable")

        # Store the callback
        self.callback = callback

        # Register the tick listener
        TickListeners.register_tick_listener(self.callback)

    def __call__(self):
        '''Calls the tick listener'''

        # Call the listener
        return self.callback()

    def _unload_instance(self):
        '''Unregisters the tick listener'''

        # Unregister the tick listener
        TickListeners.unregister_tick_listener(self.callback)
