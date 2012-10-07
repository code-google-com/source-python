# ../_libs/filters/weapons.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Engine
from Source import Entity
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

    def _WeaponContainsTag(self, edict):
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
    WeaponIterManager.RegisterFilter(tag, instance._WeaponContainsTag)


# =============================================================================
# >> RETURN TYPE FUNCTIONS
# =============================================================================
def _ReturnIndex(edict):
    '''Returns the weapon's index'''
    return Engine.IndexOfEdict(edict)


def _ReturnEdict(edict):
    '''Returns the weapon's edict'''
    return edict

# Register the return type functions
WeaponIterManager.RegisterReturnType('index', _ReturnIndex)
WeaponIterManager.RegisterReturnType('edict', _ReturnEdict)
