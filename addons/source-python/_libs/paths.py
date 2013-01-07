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
ADDON_PATH = GAME_PATH.joinpath('addons', 'source-python')

# Get the cfg's base path
CFG_PATH = GAME_PATH.joinpath('cfg', 'source-python')

# Get the log's base path
LOG_PATH = GAME_PATH.joinpath('logs', 'source-python')

# Get the translation's base path
TRANSLATION_PATH = GAME_PATH.joinpath(
    'resource', 'source-python', 'translations')

# Get the custom event's base path
EVENT_PATH = GAME_PATH.joinpath('resource', 'source-python', 'events')

# Get the sound's base path
SOUND_PATH = GAME_PATH.joinpath('sound', 'source-python')

# Get the data's base path
DATA_PATH = ADDON_PATH.joinpath('_libs', '_data')
