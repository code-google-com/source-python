# ../_libs/events/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from event_c import get_game_event_manager
from loggers import _SPLogger
from public import public
#   Events
from events.listener import _EventListener


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the CGameEventManager instance
GameEventManager = get_game_event_manager()

# Get the sp.events.manager logger
EventsManagerLogger = _SPLogger.events.manager


# =============================================================================
# >> CLASSES
# =============================================================================
@public
class _EventRegistry(dict):
    '''Dictionary object used to hold Event names with all registered callbacks
    '''

    def __missing__(self, event):
        '''Adds an event to the dictionary and registers for it'''

        # Get an _EventListener instance
        listener = self[event] = _EventListener(event)

        # Add the listener to the GameEventManager
        GameEventManager.add_listener(listener.listener, event)

        # Return the instance
        return listener

    def register_for_event(self, event, callback):
        '''Registers the callback for the given event'''

        # Is the callback callable?
        if not callable(callback):

            # Raise an error
            raise ValueError('Callback "%s" is not callable' % callback)

        # Add the callback to the event's registered callback list
        self[event].append(callback)

    def unregister_for_event(self, event, callback):
        '''Unregisters the callback for the given event'''

        # Is the event registered?
        if not event in self:

            # Raise an error
            raise ValueError('Event "%s" is not registered' % event)

        # Remove the callback from the event's list
        self[event].remove(callback)

        # Are there any callbacks remaining for the event?
        if not self[event]:

            # Remove the listener from the GameEventManager
            GameEventManager.remove_listener(self[event].listener)

            # Remove the event from the dictionary
            del self[event]

# Get the _EventRegistry instance
EventRegistry = _EventRegistry()
