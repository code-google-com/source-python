# ../_libs/core/excepthook.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   OS
from os import sep
#   Sys
import sys
#   Traceback
from traceback import format_exception

# Source.Python Imports
from paths import GAME_PATH
#   Core
from core.commands import EchoConsole


# =============================================================================
# >> CLASSES
# =============================================================================
class _ExceptHooks(list):
    '''List class that stores callbacks to be called on an exception'''

    def append(self, callback):
        '''Hook the append method to verify the given callback is callable'''

        # Is the given callback callable?
        if callable(callback):

            # Add the callback to the list
            super(_ExceptHooks, self).append(callback)

    def PrintException(self, exctype, value, trace_back, callbacks=True):
        '''Called when an exception is raised'''

        # Do all of the callbacks need looped through?
        if callbacks:

            # Loop through all callbacks in the list
            for callback in self:

                # Try to call the callback
                # Without this try/except, if a callback encounters
                # an error, it could cause an infinite loop.
                try:

                    # Call the callback with the exception arguments
                    callback(exctype, value, trace_back)

                # Was an exception raised?
                except:

                    # Get the new exception
                    error = sys.exc_info()

                    # Re-call PrintException with the new error.
                    # Pass False for callbacks, so that
                    # it does not cause an infinite loop.
                    self.PrintException(*error, callbacks=False)

        # Format the exception
        format_error = format_exception(exctype, value, trace_back)

        # Add a blank line before the actual exception
        format_error.insert(-1, '')

        # Print the leading line of the exception
        EchoConsole('\n[SP] caught an exception:')

        # Loop through each line in the exception
        for line in format_error:

            # Remove any lines pertaining to importlib in the exception
            if 'importlib' in line:
                continue

            # Strip the ending \n from the exception
            line = line.rstrip()

            # Strip the GAME_PATH to make the exception shorter
            line = line.replace(GAME_PATH, '..%s' % sep)

            # Print the current line
            EchoConsole(line)

        # Print a blank line to separate the console
        EchoConsole('')

# Get the _ExceptHooks instance
ExceptHooks = _ExceptHooks()

# Set sys.excepthook to the PrintException method
sys.excepthook = ExceptHooks.PrintException
