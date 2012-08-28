# ../_libs/paths.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Path
from path import path


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the game's base path
GAME_PATH = path(path(__file__).rsplit('addons', 1)[0])

# Get the addon's base path
ADDON_PATH = GAME_PATH.join('addons', 'source-python')

# Get the cfg's base path
CFG_PATH = GAME_PATH.join('cfg', 'source-python')

# Get the log's base path
LOG_PATH = GAME_PATH.join('logs', 'source-python')

# Get the data's base path
DATA_PATH = ADDON_PATH.join('_libs', '_data')
