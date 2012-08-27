# ../_libs/listeners/decorators.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core.decorators import BaseDecorator
#   Listeners
from listeners.tick import TickListeners


# =============================================================================
# >> CLASSES
# =============================================================================
class Tick(BaseDecorator):
    ''''''

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
        TickListeners.RegisterTickListener(self.callback)

    def __call__(self):
        '''Calls the tick listener'''

        # Call the listener
        return self.callback()

    def _UnregisterDecorator(self):
        '''Unregisters the tick listener'''

        # Unregister the tick listener
        TickListeners.UnregisterTickListener(self.callback)
