# ../_libs/messages/_base.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   OS
from os.path import isfile
from os.path import join
#   ConfigObj
from configobj import ConfigObj

# Source.Python Imports
from core import GAME_NAME
from paths import CFG_PATH


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the current game's message types
_file_path = join(CFG_PATH, '_libs', 'messages', '%s.ini' % GAME_NAME)

# Does the file exist?
if not isfile(_file_path):

    # If not, raise an error that the Messaging libraries are not set for game
    raise NotImplementedError('Source.Python messaging ' +
        'library does not currently support "%s"' % GAME_NAME)

# Get the message types for the current game
MessageTypes = ConfigObj(_file_path, unrepr=True)
