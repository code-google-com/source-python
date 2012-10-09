# ../_libs/entities/entities/hostage.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Entities
from entities.entity import BaseEntity


# =============================================================================
# >> CLASSES
# =============================================================================
class HostageEntity(BaseEntity):
    '''Class used to interact directly with hostage entites'''

    def __init__(self, index):
        '''Override the __init__ method to add "hostage" to the _inis list'''

        # Run the inherited class __init__ method
        super(HostageEntity, self).__init__(index)

        # Add "hostage" to the _inis list
        self._inis.append('hostage')

    @classmethod
    def _is_valid_index_for_entity_type(cls, edict):
        '''Verifies that the given edict is of a hostage entity'''

        # Return whether the given edict is one of a hostage entity?
        return edict.GetClassName() == 'hostage_entity'
