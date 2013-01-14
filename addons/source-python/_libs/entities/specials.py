# ../_libs/entities/specials.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Binutils
#   DynCall
from dyncall.dictionary import SignatureDictionary
#   Entities
from entities.entity import BaseEntity
from entities.helpers import index_from_inthandle
from entities.weapons.weapon import WeaponEntity
#   Filters
from filters.weapontags import WeaponTagIter
#   Players
from weapons.errors import WeaponIndexError


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
_projectile_weapons = list(WeaponTagIter('grenade', return_types='classname'))


# =============================================================================
# >> CLASSES
# =============================================================================
class _EntitySpecials(object):
    '''Base class used to hold special functionality'''

    def damage(self, victim_index, damage=0, damage_type=0, weapon_index=None):
        '''Method used to hurt another entity with the given arguments'''

        # Is the game supported?
        if not 'TakeDamage' in SignatureDictionary:

            # Raise an error if not supported
            raise NotImplementedError(
                'damage is not implemented for %s' % GAME_NAME)

        # Get the victim's BaseEntity instance.
        victim = BaseEntity(victim_index)

        # Was no weapon index given?
        if weapon_index is None and self.classname == 'player':

            # Get the player's active weapon
            weapon_index = index_from_inthandle(self.active_weapon)

        # Use try/except in case of an invalid weapon index
        try:

            # Get the weapon's WeaponEntity instance
            weapon = WeaponEntity(weapon_index)

        # Was an error encountered?
        except:

            # Raise an error
            raise WeaponIndexError(
                'Invalid index "%s" for weapon' % weapon_index)

        # Get a memory address for CTakeDamageInfo
        take_damage_info = Binutils.AllocateMemory(96)

        # Is the weapon a projectile?
        if weapon.classname in _projectile_weapons:

            # Set the hInflictor to the weapon's handle
            Binutils.SetLocInt(take_damage_info + 36, weapon.handle.ToInt())

        # Is the weapon not a projectile?
        else:

            # Set the hInflictor to the entity's handle
            Binutils.SetLocInt(take_damage_info + 36, self.handle.ToInt())

        # Set the hAttacker to the entity's handle
        Binutils.SetLocInt(take_damage_info + 40, self.handle.ToInt())

        # Set the hWeapon to the weapon's handle
        Binutils.SetLocInt(take_damage_info + 44, weapon.handle.ToInt())

        # Set the flDamage amount
        Binutils.SetLocFloat(take_damage_info + 48, float(damage))

        # Set the iDamageType value
        Binutils.SetLocInt(take_damage_info + 60, damage_type)

        # Call the function with the victim's pointer and the CTakeDamageInfo
        SignatureDictionary['TakeDamage'].call_function(
            victim.pointer, take_damage_info)

        # Deallocate the memory used for CTakeDamageInfo
        Binutils.DeallocatePointer(take_damage_info)
