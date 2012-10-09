# ../_libs/entities/weapons/molotov_projectile.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Entities
from entities.weapons.projectile import ProjectileEntity


# =============================================================================
# >> CLASSES
# =============================================================================
class MolotovProjectileEntity(ProjectileEntity):
    '''Class used to interact directly with molotov_projectile entites'''

    def __init__(self, index):
        '''Override the __init__ method to add
            "molotov_projectile" to the _inis list'''

        # Run the inherited class __init__ method
        super(MolotovProjectileEntity, self).__init__(index)

        # Add "molotov_projectile" to the _inis list
        self._inis.append('molotov_projectile')

    @classmethod
    def _is_valid_index_for_entity_type(cls, edict):
        '''Verifies that the given edict is of a molotov_projectile entity'''

        # Return whether the given edict is one of a molotov_projectile entity?
        return edict.GetClassName() == 'molotov_projectile'
