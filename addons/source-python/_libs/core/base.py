# ./_libs/core/base.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   OS
from os import sep

# Source.Python Imports
from Source import Engine
from paths import GAME_PATH


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the specific game for the server
GAME_NAME = GAME_PATH.rsplit(sep, 2)[1]

# Get the Engine's instance
GameEngine = Engine.GetEngine()
