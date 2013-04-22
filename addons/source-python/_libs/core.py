# ../_libs/core.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   OS
from os import sep

# Source.Python Imports
from engine_c import get_engine_interface
from paths import GAME_PATH


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the specific game for the server
GAME_NAME = GAME_PATH.rsplit(sep, 2)[1]

# Get the Engine's instance
GameEngine = get_engine_interface()


# =============================================================================
# >> CLASSES
# =============================================================================
class AutoUnload(object):
    '''
        Class used to auto unload specific instances.

        Each class which inherits this one
        should have a _unload_instance method.
    '''


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def echo_console(text):
    '''echos a message to the server's console'''

    # Loop through each line in the text
    for line in text.split('\n'):

        # Echo the message
        GameEngine.server_command('echo "%s"\n' % line.replace('"', "'"))
