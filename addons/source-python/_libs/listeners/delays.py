# ../_libs/listeners/delays.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Sys
import sys
#   Time
import time

# Source.Python Imports
#   Core
from core.excepthook import ExceptHooks
#   Listeners
from listeners.tick import TickListeners


# =============================================================================
# >> CLASSES
# =============================================================================
class _Delay(object):
    '''Stores a delay object that scripters can use to
        change arguments, cancel the delay, etc...'''

    def __init__(self, seconds, callback, *args, **kw):
        '''Called when an instance is instanciated'''

        # Store the time to execute the callback
        self.exec_time = time.time() + seconds

        # Store the callback, arguments, and keywords
        self.callback = callback
        self.args = args
        self.kw = kw

    def __call__(self):
        '''Calls the delay with the proper arguments and keywords'''

        # Use try/except in case an error is encountered
        try:

            # Execute the callback with the arguments and keywords
            self.callback(*self.args, **self.kw)

        # Was an error encountered?
        except:

            # Get the error
            error = sys.exc_info()

            # Print the exception to the console
            ExceptHooks.print_exception(*error)


class _Times(list):
    '''List class used to store delays to be called'''

    def call_delays(self):
        '''Call the delays in the list'''

        # Loop through the delays in the list
        for item in self:

            # Call the delay
            item()


class _TickDelays(dict):
    '''Class used to store delays to be called by a tick listener'''

    def __init__(self):
        '''Called when the class is first instanciated'''

        # Store an ordered list to sort delays
        self._order = list()

    def __missing__(self, item):
        '''Called when first adding a time to the dictionary'''

        # Is the tick listener registered?
        if not self:

            # Register the tick listener
            TickListeners.register_tick_listener(self._tick)

        # Add the item to the dictionary as a _Times instance
        self[item] = _Times()

        # Add the time to the ordered list
        self._order.append(item)

        # Sort the ordered list
        self._order.sort()

        # Return the item's instance
        return self[item]

    def __iter__(self):
        '''Override __iter__ to loop through the ordered list'''

        # Loop through each item in the ordered list
        for item in self._order:

            # Yield the item
            yield item

    def __delitem__(self, item):
        '''Override __delitem__ to call the delays and
            remove the time from the ordered list'''

        # Is the item in the dictionary?
        if not item in self:

            # If not, simply return
            return

        # Call all delays for the given item
        self[item].call_delays()

        # Remove the item from the ordered list
        self._order.remove(item)

        # Remove the item from the dictionary
        super(_TickDelays, self).__delitem__(item)

    def delay(self, seconds, callback, *args, **kw):
        '''Method used to create a delay'''

        # Get the _Delay instance for the given arguments
        delay_object = _Delay(seconds, callback, *args, **kw)

        # Add the _Delay instance to the dictionary using its execution time
        self[delay_object.exec_time].append(delay_object)

        # Return the object
        return delay_object

    def _tick(self):
        '''Called every tick when the listener is registered'''

        # Get the current time
        current_time = time.time()

        # Loop through each item in the ordered list
        for item in self:

            # Should the delays be called?
            if item > current_time:

                # If not, no need to continue looping
                break

            # Remove the item from the dictionary
            del self[item]

        # Is the dictionary now empty?
        if not self:

            # Unregister the tick listener
            TickListeners.unregister_tick_listener(self._tick)

    def cancel_delay(self, delay_object):
        '''Method used to cancel a delay'''

        # Is the given argument a _Delay object?
        if not isinstance(delay_object, _Delay):

            # If not, raise an error
            raise TypeError(
                'TickDelays.cancel_delay requires a _Delay instance.')

        # Is the given _Delay object's time no longer in the dictionary?
        if not delay_object.exec_time in self:

            # If not, raise an error
            raise KeyError('Object is no longer registered.')

        # Remove the delay from its time
        self[delay_object.exec_time].remove(delay_object)

        # Does the delay's time have any remaining objects?
        if not self[delay_object.exec_time]:

            # If not, remove the delay's time from the dictionary
            del self[delay_object.exec_time]

        # Are there any remaining delays?
        if not self:

            # Unregister the listener
            TickListeners.unregister_tick_listener(self._tick)

# Get the _TickDelays instance
TickDelays = _TickDelays()
