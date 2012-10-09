# ../_libs/entities/weapons/weapon.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Entities
from entities.entity import BaseEntity
#   Weapons
from weapons.manager import WeaponManager


# =============================================================================
# >> CLASSES
# =============================================================================
class WeaponEntity(BaseEntity):
    '''Class used to interact directly with weapon entites'''

    def __init__(self, index):
        '''Override the __init__ method to add "weapon" to the _inis list'''

        # Run the inherited class __init__ method
        super(WeaponEntity, self).__init__(index)

        # Add "weapon" to the _inis list
        self._inis.append('weapon')

    @classmethod
    def _is_valid_index_for_entity_type(cls, edict):
        '''Verifies that the given edict is of a weapon entity'''

        # Return whether the given edict is one of a weapon entity?
        return edict.GetClassName() in WeaponManager
