# ../_libs/entities/specials.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Binutils
#   Core
from core import GAME_NAME
#   DynCall
from dyncall.dictionary import SignatureDictionary
#   Entities
from entities.constants import DamageOffsets
from entities.helpers import index_from_inthandle
#   Filters
from filters.weapons import WeaponClassIter
#   Weapons
from weapons.errors import WeaponIndexError


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get a list of projectiles for the game
_projectile_weapons = list(
    WeaponClassIter('grenade', return_types='classname'))


# =============================================================================
# >> CLASSES
# =============================================================================
class _EntitySpecials(object):
    '''Base class used to hold special functionality'''

    def damage(
            self, victim_index, damage=0, damage_type=0,
            weapon_index=None, hitgroup=0, **keywords):
        '''Method used to hurt another entity with the given arguments'''

        # Import BaseEntity classes
        # Doing this in the global scope causes cross import errors
        from entities.entity import BaseEntity
        from entities.weapons.weapon import WeaponEntity
        from players.entity import PlayerEntity

        # Is the game supported?
        if not 'TakeDamage' in SignatureDictionary:

            # Raise an error if not supported
            raise NotImplementedError(
                'damage is not implemented for %s' % GAME_NAME)

        # Was no weapon index given?
        if weapon_index is None and hasattr(self, 'active_weapon'):

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

        # Get the victim's BaseEntity instance.
        victim = BaseEntity(victim_index)

        # Is the victim a player?
        if victim.classname == 'player':

            # Get the victim's PlayerEntity instance instead
            victim = PlayerEntity(victim_index)

            # Is hitgroup a valid attribute?
            if hasattr(victim, 'hitgroup'):

                # Set the victim's hitgroup
                victim.hitgroup = hitgroup

        # Get a memory address for CTakeDamageInfo
        take_damage_info = Binutils.AllocateMemory(96)

        # Is the weapon a projectile?
        if weapon.classname in _projectile_weapons:

            # Set the hInflictor to the weapon's handle
            Binutils.SetLocInt(
                take_damage_info + DamageOffsets.hInflictor,
                weapon.handle.ToInt())

        # Is the weapon not a projectile?
        else:

            # Set the hInflictor to the entity's handle
            Binutils.SetLocInt(
                take_damage_info + DamageOffsets.hInflictor,
                self.handle.ToInt())

        # Set the hAttacker to the entity's handle
        Binutils.SetLocInt(
            take_damage_info + DamageOffsets.hAttacker, self.handle.ToInt())

        # Set the hWeapon to the weapon's handle
        Binutils.SetLocInt(
            take_damage_info + DamageOffsets.hWeapon, weapon.handle.ToInt())

        # Set the flDamage amount
        Binutils.SetLocFloat(
            take_damage_info + DamageOffsets.flDamage, float(damage))

        # Set the bitsDamageType value
        Binutils.SetLocInt(
            take_damage_info + DamageOffsets.bitsDamageType, damage_type)

        # Loop through the given keywords
        for item in keywords:

            # Is the keyword supported?
            if item in DamageOffsets:

                # Set the offset's value
                getattr(Binutils, 'SetLoc%s' % DamageOffsets[item]['type'])(
                    take_damage_info + DamageOffsets[item]['offset'],
                    keywords[item])

        # Call the function with the victim's pointer and the CTakeDamageInfo
        SignatureDictionary['TakeDamage'].call_function(
            victim.pointer, take_damage_info)

        # Deallocate the memory used for CTakeDamageInfo
        Binutils.DeallocatePointer(take_damage_info)
