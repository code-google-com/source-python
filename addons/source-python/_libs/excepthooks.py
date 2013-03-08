# ../_libs/excepthooks.py

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
from core import echo_console
from paths import GAME_PATH
#   Translations
from translations.strings import LangStrings


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
_excepthook_strings = LangStrings('_core/excepthooks_strings')


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

    def print_exception(self, exctype, value, trace_back, callbacks=True):
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

                    # Re-call print_exception with the new error.
                    # Pass False for callbacks, so that
                    # it does not cause an infinite loop.
                    self.print_exception(*error, callbacks=False)

        # Format the exception
        format_error = format_exception(exctype, value, trace_back)

        # Add a blank line before the actual exception
        format_error.insert(-1, '')

        # Print the leading line of the exception
        echo_console('\n[SP] ' + _excepthook_strings['Exception'].get_string())

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
            echo_console(line)

        # Print a blank line to separate the console
        echo_console('')

# Get the _ExceptHooks instance
ExceptHooks = _ExceptHooks()

# Set sys.excepthook to the print_exception method
sys.excepthook = ExceptHooks.print_exception
