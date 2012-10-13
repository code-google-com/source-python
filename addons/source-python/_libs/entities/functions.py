# ../_libs/entities/functions.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   ConfigObj
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
# Store the base "functions" path
_basepath = DATA_PATH.joinpath('functions')


# =============================================================================
# >> CLASSES
# =============================================================================
class _Functions(dict):
    '''Dictionary that stores all entities with their functions'''

    def __missing__(self, item):
        '''Called the first time an entity is added to the dictionary'''

        # Get all functions for the given entity
        value = self[item] = _get_all_entity_functions(item)

        # Return the functions
        return value

    def get_entity_functions(self, args):
        '''Returns all functions for the given entities'''

        # Create an empty dictionary
        values = dict()

        # Loop through all given entities
        for arg in args:

            # Add the entities to the dictionary
            values.update(self[arg])

        # Return all functions for the given entities
        return values

# Get the _Functions instance
Functions = _Functions()


class _FunctionInstance(Signature):
    '''Class that inherits from Signature to place
       the entity's pointer as the first argument'''

    current_pointer = None

    def _pre_call_function(self, *args):
        '''Adds the entity's pointer as the first
            argument when calling the function'''

        # Call the function with the entity's pointer as the first argument
        self.call_function(*(self.current_pointer, ) + args)

        # Reset the current pointer
        self.current_pointer = None


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def _get_all_entity_functions(entity):
    '''Retrieves all functions for the given entity'''

    # Create an empty dictionary to pass
    game_functions = {}

    # Get the path to the entity's function file
    inifile = _basepath.join(entity, GAME_NAME + '.ini')

    # Does the file exist?
    if not inifile.isfile():

        # Return the empty dictionary
        return game_functions

    # Get the file's contents
    ini = ConfigObj(inifile)

    # Loop through all items in the file
    for key in ini:

        # Add the item to the dictionary
        game_functions[key] = _FunctionInstance(ini[key])

    # Return the dictionary
    return game_functions
