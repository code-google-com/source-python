# ../_libs/events/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Sys
import sys

# Source.Python Imports
from Source import Event
#   Core
from core.excepthook import ExceptHooks


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the CGameEventManager instance
GameEventManager = Event.get_game_event_manager()


# =============================================================================
# >> CLASSES
# =============================================================================
class _EventRegistry(dict):
    '''Dictionary object used to hold Event names with all registered callbacks
    '''

    def __missing__(self, event):
        '''Adds an event to the dictionary and registers for it'''

        # Get an _EventListener instance
        listener = self[event] = _EventListener(event)

        # Add the listener to the GameEventManager
        GameEventManager.add_listener(listener, event)

        # Return the instance
        return listener

    def register_for_event(self, event, callback):
        '''Registers the callback for the given event'''

        # Is the callback callable?
        if not callable(callback):

            raise ValueError('Callback "%s" is not callable' % callback)

        # Is the callback already registered for the given event?
        if event in self and callback in self[event]:

            # Raise an error
            raise ValueError(
                'Event callback "%s" is already ' % callback +
                'registered for event "%s"' % event)

        # Add the callback to the event's registered callback list
        self[event].append(callback)

    def unregister_for_event(self, event, callback):
        '''Unregisters the callback for the given event'''

        # Is the event registered?
        if not event in self:

            # Raise an error
            raise ValueError('Event "%s" is not registered' % event)

        # Is the callback registered for the event?
        if not callback in self[event]:

            # Raise an error
            raise ValueError(
                'Event callback "%s" is not ' % callback +
                'registered for the event "%s"' % event)

        # Remove the callback from the event's list
        self[event].remove(callback)

        # Are there any callbacks remaining for the event?
        if not self[event]:

            # Remove the listener from the GameEventManager
            GameEventManager.remove_listener(self[event], event)

            # Remove the event from the dictionary
            del self[event]

# Get the _EventRegistry instance
EventRegistry = _EventRegistry()


class _EventListener(Event.CGameEventListener):
    '''Stores callbacks for the given event'''

    def __init__(self, event):
        '''
            Instanciates the class and creates an empty list to store callbacks
        '''
        super(_EventListener, self).__init__()
        self._order = list()

    def __contains__(self, callback):
        '''Returns whether the callback is in the event's list'''
        return callback in self._order

    def append(self, callback):
        '''Adds the callback to the event's list'''
        self._order.append(callback)

    def remove(self, callback):
        '''Removes the callback from the event's list'''
        self._order.remove(callback)

    def fire_game_event(self, GameEvent):
        '''Loops through all callbacks for an event and calls them'''

        # Loop through each callback in the event's list
        for callback in self._order:

            # Try to call the callback
            try:

                # Call the callback
                callback(GameEvent)

            # Was an error encountered?
            except:

                # Get the error
                error = sys.exc_info()

                # Print the exception to the console
                ExceptHooks.print_exception(*error)
