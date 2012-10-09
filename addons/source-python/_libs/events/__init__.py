# ../_libs/events/__init__.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core.decorators import BaseDecorator
#   Events
from events.manager import EventRegistry


# =============================================================================
# >> CLASSES
# =============================================================================
class Event(BaseDecorator):
    '''Event decorator class'''

    def __init__(self, callback):
        '''Store the callback and register the event'''

        # Is the callback callable?
        if not callable(callback):

            # Raise an error
            raise TypeError(
                "'" + type(callback).__name__ + "' object is not callable")

        # Store the callback
        self.callback = callback

        # Register the event
        EventRegistry.register_for_event(self.callback.__name__, self.callback)

    def __call__(self, GameEvent):
        '''Calls the Event callback with the GameEvent instance'''

        # Call the Event callback
        return self.callback(GameEvent)

    def _unregister_decorator(self):
        '''Unregisters the event'''

        # Unregister the event
        EventRegistry.unregister_for_event(
            self.callback.__name__, self.callback)
