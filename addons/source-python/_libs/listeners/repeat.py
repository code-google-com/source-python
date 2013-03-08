# ../_libs/listeners/repeat.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Time
import time

# Source.Python Imports
from core import AutoUnload
#   Listeners
from listeners.delays import TickDelays


# =============================================================================
# >> CLASSES
# =============================================================================
class Status(object):
    '''Class used to store Status values'''
    STOPPED, RUNNING, PAUSED = range(1, 4)


class Repeat(AutoUnload):
    '''Class used to create and call repeats'''

    def __init__(self, callback, *args, **kw):
        '''Stores all attributes'''

        # Store the base attributes
        self.callback = callback
        self.args = args
        self.kw = kw

        # Set up private attributes
        self._interval = 0
        self._limit = 0
        self._count = 0
        self._adjusted = 0
        self._status = Status.STOPPED

    def start(self, interval, limit):
        '''Starts the repeat loop'''

        # Is the repeat already running?
        if self._status == Status.RUNNING:

            # Do not start the repeat
            return

        # Set the status to running
        self._status = Status.RUNNING

        # Set the given attributes
        self._interval = interval
        self._limit = limit

        # Reset base counting attributes
        self._count = 0
        self._adjusted = 0

        # Start the delay
        self._delay = TickDelays.delay(self._interval, self._execute)

    def stop(self):
        '''Stops the repeat loop'''

        # Is the repeat running?
        if self._status != Status.RUNNING:

            # No need to stop it
            return

        # Set the status to stopped
        self._status = Status.STOPPED

        # Cancel the delay
        TickDelays.cancel_delay(self._delay)

    def restart(self):
        '''Restarts the repeat'''

        # Stop the repeat
        self.stop()

        # Start the repeat
        self.start(self._interval, self._limit)

    def pause(self):
        '''Pauses the repeat.  Pausing allows the repeat to be resumed'''

        # Is the repeat running?
        if self._status != Status.RUNNING:

            # No need to pause
            return

        # Set the status to paused
        self._status = Status.PAUSED

        # Set the remaining time in the current loop
        self._loop_time = self._delay.exec_time - time.time()

        # Cancel the delay
        TickDelays.cancel_delay(self._delay)

    def resume(self):
        '''Resume the repeat.  Can only resume if in paused status'''

        # Is the repeat paused?
        if self._status != Status.PAUSED:

            # Do not resume
            return

        # Start the delay
        self._delay = TickDelays.delay(self._loop_time, self._execute)

    def extend(self, adjustment):
        '''Adds to the number of loops to be made'''

        # Was a positive integer given?
        if adjustment < 1 or not isinstance(adjustment, int):

            # Raise an error
            raise ValueError('Adjusted value must be a positive integer')

        # Add to the adjusted number
        self._adjusted += adjustment

    def reduce(self, adjustment):
        '''Reduces the number of loops to be made'''

        # Was a positive integer given?
        if adjustment < 1 or not isinstance(adjustment, int):

            # Raise an error
            raise ValueError('Adjusted value must be a positive integer')

        # Subtract from the adjusted number
        self._adjusted -= adjustment

        # Are no more loops to be made?
        if self.remaining and self._limit and self.status == Status.RUNNING:

            # Stop the repeat
            self.stop()

    def _execute(self):
        '''Executes the repeat's callback with its arguments and keywords'''

        # Add one to the current count
        self._count += 1

        # Are any more loops to be made?
        if self.remaining or not self._limit:

            # Call the delay again
            self._delay = TickDelays.delay(self._interval, self._execute)

        # Are no more loops to be made?
        else:

            # Set the status to stopped
            self._status = Status.STOPPED

        # Call the repeat's callback
        self.callback(*self.args, **self.kw)

    @property
    def remaining(self):
        '''Returns the remaining number of loops in the repeat'''

        # Is there no limit?
        if not self._limit:

            # Return the limit
            return self._limit

        # Return the remaining number of loops
        return self.limit - self._count

    @property
    def count(self):
        '''Returns the current number of loops made in the repeat'''
        return self._count

    @property
    def limit(self):
        '''Returns the total number of loops to be made'''

        # Is there no limit?
        if not self._limit:

            # Return the limit
            return self._limit

        # Return the adjusted limit
        return self._limit + self._adjusted

    @property
    def timeleft(self):
        '''Returns the remaining time till the end of the repeat'''
        return self.remaining * self._interval

    @property
    def elapsed(self):
        '''Returns the elapsed time since the repeat started'''
        return self._count * self._interval

    @property
    def total_time(self):
        '''Returns the total time it will take to complete the repeat'''
        return self.limit * self._interval

    @property
    def status(self):
        '''Returns the status of the repeat'''
        return self._status

    def _unload_instance(self):
        '''Stops the repeat'''
        self.stop()
