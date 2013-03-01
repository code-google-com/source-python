# ../_libs/core/__init__.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   OS
from os import sep

# Source.Python Imports
from Source import engine_c
from paths import GAME_PATH


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the specific game for the server
GAME_NAME = GAME_PATH.rsplit(sep, 2)[1]

# Get the Engine's instance
GameEngine = engine_c.get_engine_interface()


# =============================================================================
# >> CLASSES
# =============================================================================
class AutoUnload(object):
    '''
        Class used to auto unload specific instances.

        Each class which inherits this one
        should have a _unload_instance method.
    '''
