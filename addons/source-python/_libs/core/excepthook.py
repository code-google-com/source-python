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
# >> FUNCTIONS
# =============================================================================
def PrintException(exctype, value, trace_back):
    '''Called when an exception is raised'''

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

sys.excepthook = PrintException
