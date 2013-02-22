# ../_libs/filters/weapons.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Entity
#   Entities
from entities.entities.weapon import WeaponEntity
from entities.helpers import basehandle_from_edict
from entities.helpers import index_from_edict
from entities.helpers import inthandle_from_edict
from entities.helpers import pointer_from_edict
#   Filters
from filters.iterator import _IterObject
from filters.manager import _BaseFilterManager
#   Weapons
from weapons.manager import WeaponManager


# =============================================================================
# >> MAIN WEAPON ITER CLASSES
# =============================================================================
class _WeaponIterManager(_BaseFilterManager):
    '''Filter management class specifically for weapon iterating'''

# Get the _WeaponIterManager instance
WeaponIterManager = _WeaponIterManager()


class WeaponIter(_IterObject):
    '''Weapon iterate class'''

    # Store the manager for the weapon iterator
    manager = WeaponIterManager

    @staticmethod
    def iterator():
        '''Iterates over only weapon entities'''

        # Loop through all entities on the server
        for edict in Entity.Entities():

            # Is the entity a weapon?
            if edict.GetClassName() in WeaponManager:

                # Yield the entity
                yield edict


# =============================================================================
# >> WEAPON TAG CLASSES
# =============================================================================
class _WeaponTags(dict):
    '''Class used to store weapon tags for the current game'''

    def __missing__(self, item):
        '''Called when a new item is added to the dictionary'''

        # Get the _Tag instance for the current item
        instance = self[item] = _Tag(item)

        # Return the instance
        return instance

# Get the _WeaponTags instance
WeaponTags = _WeaponTags()


class _Tag(object):
    '''Class used to store a tag and compare to a given weapon'''

    def __init__(self, tag):
        '''Store the tag for future use'''

        # Store the tag
        self.tag = tag

    def _weapon_contains_tag(self, edict):
        '''Returns whether the weapon contains the tag'''

        # Return whether the weapon contains the tag
        return self.tag in WeaponManager[edict.GetClassName()].tags

# =============================================================================
# >> FILTER REGISTRATION
# =============================================================================
# Loop through all tags for the current game
for tag in WeaponManager.tags:

    # Get the WeaponTags instance for the current tag
    instance = WeaponTags[tag]

    # Register the tag's filter
    WeaponIterManager.register_filter(tag, instance._weapon_contains_tag)


# =============================================================================
# >> RETURN TYPE FUNCTIONS
# =============================================================================
def _return_edict(edict):
    '''Returns the weapon's edict'''
    return edict


def _return_weapon(edict):
    '''Returns the weapon's WeaponEntity instance'''
    return WeaponEntity(index_from_edict(edict))

# Register the return type functions
WeaponIterManager.register_return_type('index', index_from_edict)
WeaponIterManager.register_return_type('basehandle', basehandle_from_edict)
WeaponIterManager.register_return_type('inthandle', inthandle_from_edict)
WeaponIterManager.register_return_type('pointer', pointer_from_edict)
WeaponIterManager.register_return_type('edict', _return_edict)
WeaponIterManager.register_return_type('weapon', _return_weapon)
