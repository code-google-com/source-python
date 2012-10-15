# ../_libs/dyncall/dictionary.py

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

    def parse_signature_ini(self, inifile):
        '''Parse an ini file and add its signatures to the dictionary'''

        # Get the ConfigObj instance of the file
        sigs = ConfigObj(_inipath)

        # Loop through all functions
        for function in sigs:

            # Add the function to the dictionary
            self[sigs[function]['shortname']] = Signature(sigs[function])

# Get the main _SignatureDictionary instance
SignatureDictionary = _SignatureDictionary()

# Does the game's ini file exist?
if _inipath.isfile():

    # Parse the ini file
    SignatureDictionary.parse_signature_ini(_inipath)
