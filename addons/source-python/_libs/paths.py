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
game_path = dirname(__file__).rsplit('addons', 1)[0]

# Get the addon's base path
addon_path = join(game_path, 'addons', 'source-python')

# Get the cfg's base path
cfg_path = join(game_path, 'cfg', 'source-python')
