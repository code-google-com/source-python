# ../_libs/dyncall/modules.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Binutils


# =============================================================================
# >> CLASSES
# =============================================================================
class _ModuleData(dict):
    '''Dictionary used to store module data for dyncalls'''

    def __missing__(self, item):
        '''Add the module to the dictionary'''

        # Add the missing module to the dictionary
        self[item] = Binutils.FindModuleData(item)

        # Return the module's instance
        return self[item]

# Get the _ModuleData instance
ModuleData = _ModuleData()
