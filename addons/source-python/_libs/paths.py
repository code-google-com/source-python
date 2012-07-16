# ../_libs/paths.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   OS
from os.path import dirname
from os.path import join


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the game's base path
GAME_PATH = dirname(__file__).rsplit('addons', 1)[0]

# Get the addon's base path
ADDON_PATH = join(GAME_PATH, 'addons', 'source-python')

# Get the cfg's base path
CFG_PATH = join(GAME_PATH, 'cfg', 'source-python')
