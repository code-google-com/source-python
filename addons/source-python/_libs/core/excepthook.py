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

    def PrintException(self, exctype, value, trace_back):
        '''Called when an exception is raised'''

        # Loop through all callbacks in the list
        for callback in self:

            # Call the callback with the exception arguments
            callback(exctype, value, trace_back)

        # Format the exception
        format_error = format_exception(exctype, value, trace_back)

        # Add a blank line before the actual exception
        format_error.insert(-1, '')

        # Print the leading line of the exception
        print('\n[SP] caught an exception:')

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
            print(line)

        # Print a blank line to separate the console
        print('')

# Get the _ExceptHooks instance
ExceptHooks = _ExceptHooks()

# Set sys.excepthook to the PrintException method
sys.excepthook = ExceptHooks.PrintException
