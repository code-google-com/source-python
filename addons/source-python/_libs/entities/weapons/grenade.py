# ../_libs/entities/weapons/grenade.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Entities
from entities.weapons.weapon import WeaponEntity
#   Filters
from filters.weapontags import WeaponTagIter


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Store a list of grenade weapons
grenades = [weapon.name for weapon in WeaponTagIter('grenade')]


# =============================================================================
# >> CLASSES
# =============================================================================
class GrenadeEntity(WeaponEntity):
    '''Class used to interact directly with grenade entites'''

    def __init__(self, index):
        '''Override the __init__ method to add "grenade" to the _inis list'''

        # Run the inherited class __init__ method
        super(GrenadeEntity, self).__init__(index)

        # Add "grenade" to the _inis list
        self._inis.append('grenade')

    @classmethod
    def _is_valid_index_for_entity_type(cls, edict):
        '''Verifies that the given edict is of a grenade entity'''

        # Return whether the given edict is one of a grenade entity?
        return edict.GetClassName() in grenades
