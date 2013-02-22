# ../_libs/events/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Sys
import sys

# Source.Python Imports
#   Core
from core.excepthook import ExceptHooks


# =============================================================================
# >> CLASSES
# =============================================================================
class _EventRegistry(dict):
    '''Dictionary object used to hold Event names with all registered callbacks
    '''

    def register_for_event(self, event, callback):
        '''Registers the callback for the given event'''

        # Does the dictionary contain the event?
        if not event in self:

            # Add the event to the dictionary
            self[event] = _EventManager()

        # Add the callback to the event's registered callback list
        self[event].append(callback)

    def unregister_for_event(self, event, callback):
        '''Unregisters the callback for the given event'''

        # Does the dictionary contain the event?
        if event in self:

            # Remove the callback from the event's registered callbacks
            self[event].remove(callback)

        # Are there any callbacks remaining for the event?
        if not self[event]:

            # Remove the event from the dictionary
            del self[event]

    def call_event_callbacks(self, GameEvent):
        '''Calls all callbacks for the current event if any are registered'''

        # Get the event's name
        event_name = GameEvent.get_name()

        # Does the dictionary contain the event?
        if event_name in self:

            # Call each callback for the current event
            self[event_name]._call_event(GameEvent)

# Get the _EventRegistry instance
EventRegistry = _EventRegistry()


class _EventManager(list):
    '''Stores callbacks for the given event'''

    def append(self, callback):
        '''Override the append method to verify the
            callback has not already been registered'''

        # Has the callback been registered for this event?
        if not callback in self:

            # Add the callback to the list
            super(_EventManager, self).append(callback)

    def remove(self, callback):
        '''Override the remove method to verify the
            callback is registered for the event'''

        # Is the callback registered for this event?
        if callback in self:

            # Remove the callback from the list
            super(_EventManager, self).remove(callback)

    def _call_event(self, GameEvent):
        '''Loops through all callbacks for an event and calls them'''

        # Loop through each callback in the event's list
        for callback in self:

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
