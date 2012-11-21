# ../_libs/messages/_base.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   ConfigObj
from configobj import ConfigObj

# Source.Python Imports
from core import GAME_NAME
from paths import DATA_PATH


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the current game's message types
_file_path = DATA_PATH.join('messages', GAME_NAME + '.ini')

# Does the file exist?
if not _file_path.isfile():

    # If not, raise an error that the Messaging libraries are not set for game
    raise NotImplementedError(
        'Source.Python messaging library does ' +
        'not currently support "%s"' % GAME_NAME)

# Get the message types for the current game
MessageTypes = ConfigObj(_file_path, unrepr=True)
