# ../_libs/tick/listeners.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from tick_c import CTickListenerManager
from excepthooks import ExceptHooks


# =============================================================================
# >> CLASSES
# =============================================================================
class _TickListeners(CTickListenerManager):
    '''Registers/unregisters tick listeners and fires them each tick'''

    def append(self, callback):
        '''Adds a listener to the list'''

        # Is the listener already registered?
        if callback in self:

            # If so, raise an error that it cannot be registered
            raise NameError(
                'Cannot register tick-listener "' +
                '%s", callback is already registered.' % callback.__name__)

        # Is the listener callback?
        if not callable(callback):

            # If not, raise an error that the callback must be callable
            raise TypeError(
                "'" + type(callback).__name__ + "' object is not callable")

        # Add the listener to the list
        self.add_listener(callback)

    def remove(self, callback):
        '''Removes a listener from the list'''

        # Is the listener registered?
        if not callback in self:

            # If not, raise an error that the listener cannot be unregistered
            raise NameError(
                'Cannot unregister tick-listener "' +
                '%s", callback is not registered.' % callback.__name__)

        # Remove the listener from the list
        self.remove_listener(callback)

    def __contains__(self, callback):
        '''Returns whether or not the callback is registered'''
        return self.is_registered(callback)

    def __len__(self):
        '''Returns the number of callbacks that are registered'''
        return self.count()

    def __iter__(self):
        '''Iterates over all of the registered callbacks'''

        # 
        for index in range(len(self)):

            # 
            yield self.get_value_from_index(index)

    def call_tick_listeners(self):
        '''Calls all tick listeners in order'''

        # Loop through all the listeners
        for callback in self:

            # Use try/except to handle errors
            try:

                # Call the listener
                callback()

            # Was an error encountered?
            except:

                # Print the exception to the console
                ExceptHooks.print_exception()

    def register_tick_listener(self, callback):
        '''Registers a tick listener'''

        # Add the listener to the list
        self.append(callback)

    def unregister_tick_listener(self, callback):
        '''Unregisters a tick listener'''

        # Remove the listener from the list
        self.remove(callback)

# Get the _TickListeners instance
TickListeners = _TickListeners()
