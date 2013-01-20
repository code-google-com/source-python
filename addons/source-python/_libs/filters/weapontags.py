# ../_libs/filters/weapontags.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Filters
from filters.iterator import _IterObject
from filters.manager import _BaseFilterManager
#   Weapons
from weapons.manager import WeaponManager


# =============================================================================
# >> MAIN WEAPON ITER CLASSES
# =============================================================================
class _WeaponTagIterManager(_BaseFilterManager):
    '''Filter management class specifically for weapon tag iterating'''

# Get the _WeaponTagIterManager instance
WeaponTagIterManager = _WeaponTagIterManager()


class WeaponTagIter(_IterObject):
    '''Weapon tag iterate class'''

    # Store the manager for the weapon tag iterator
    manager = WeaponTagIterManager

    def __init__(self, is_filters=[], not_filters=[], return_types='weapon'):
        '''Overwrite the __init__ method to re-call main __init__
            method with "weapon" as the default return_types'''

        # Re-call __init__ in case no return_types were actually passed
        # since "weapon" is the default value for this iter class
        super(WeaponTagIter, self).__init__(
            is_filters, not_filters, return_types)

    @staticmethod
    def iterator():
        '''Iterates over all possible weapon types'''

        # Loop through all weapons for the current game
        for weapon in WeaponManager:

            # Yield the weapon
            yield WeaponManager[weapon]


# =============================================================================
# >> WEAPON TAG STORAGE CLASSES
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

    def _weapon_contains_tag(self, weapon):
        '''Returns whether the weapon type contains the tag'''

        # Return whether the weapon type contains the tag
        return self.tag in WeaponManager[weapon].tags

# =============================================================================
# >> FILTER REGISTRATION
# =============================================================================
# Loop through all tags for the current game
for tag in WeaponManager.tags:

    # Get the WeaponTags instance for the current tag
    instance = WeaponTags[tag]

    # Register the tag's filter
    WeaponTagIterManager.register_filter(tag, instance._weapon_contains_tag)


# =============================================================================
# >> RETURN TYPE FUNCTIONS
# =============================================================================
def _return_weapon(weapon):
    '''Returns the weapon type's WeaponManager item'''
    return weapon


def _return_classname(weapon):
    '''Returns the weapon type's classname'''
    return weapon.name


def _return_basename(weapon):
    '''Returns the weapon type's basename'''
    return weapon.basename


def _return_slot(weapon):
    '''Returns the weapon type's slot'''
    return weapon.slot


def _return_maxammo(weapon):
    '''Returns the weapon type's maxammo'''
    return weapon.maxammo


def _return_ammoprop(weapon):
    '''Returns the weapon type's ammoprop'''
    return weapon.ammoprop


def _return_clip(weapon):
    '''Returns the weapon type's clip'''
    return weapon.clip


def _return_tags(weapon):
    '''Returns the weapon type's tags'''
    return weapon.tags

# Register the return type functions
WeaponTagIterManager.register_return_type('weapon', _return_weapon)
WeaponTagIterManager.register_return_type('classname', _return_classname)
WeaponTagIterManager.register_return_type('basename', _return_basename)
WeaponTagIterManager.register_return_type('slot', _return_slot)
WeaponTagIterManager.register_return_type('maxammo', _return_maxammo)
WeaponTagIterManager.register_return_type('ammoprop', _return_ammoprop)
WeaponTagIterManager.register_return_type('clip', _return_clip)
WeaponTagIterManager.register_return_type('tags', _return_tags)
