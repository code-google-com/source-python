# ../_libs/dyncall/__init__.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Configobj
from configobj import ConfigObj

# Source.Python Imports
from paths import DATA_PATH
#   Core
from core import GAME_NAME
#   DynCall
from dyncall.signature import Signature


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Store the game's ini file's path
_inipath = DATA_PATH.joinpath('dyncall', GAME_NAME + '.ini')


# =============================================================================
# >> CLASSES
# =============================================================================
class _SignatureDictionary(dict):
    '''Dictionary to store Signature instances by name'''

    def __setitem__(self, item, value):
        '''Override __setitem__ to store as a Signature instance'''

        # Set the item to its Signature instance
        super(_SignatureDictionary, self).__setitem__(item, Signature(value))

# Get the main _SignatureDictionary instance
SigDictionary = _SignatureDictionary()

# Does the game's ini file exist?
if _inipath.isfile():

    # Get the ConfigObj instance of the file
    _ini = ConfigObj(_inipath)

    # Loop through all functions
    for function in _ini:

        # Add the function to the dictionary
        SigDictionary[function] = _ini[function]
