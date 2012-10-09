# ../_libs/entities/weapons/projectile.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Entities
from entities.weapons.weapon import WeaponEntity


# =============================================================================
# >> CLASSES
# =============================================================================
class ProjectileEntity(WeaponEntity):
    '''Class used to interact directly with projectile entites'''

    def __init__(self, index):
        '''
            Override the __init__ method to add "projectile" to the _inis list
        '''

        # Run the inherited class __init__ method
        super(ProjectileEntity, self).__init__(index)

        # Add "projectile" to the _inis list
        self._inis.append('projectile')

    @classmethod
    def _is_valid_index_for_entity_type(cls, edict):
        '''Verifies that the given edict is of a projectile entity'''

        # Return whether the given edict is one of a projectile entity?
        return edict.GetClassName().endswith('_projectile')
