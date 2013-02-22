# ../_libs/weapons/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Configobj
from configobj import ConfigObj

# Source.Python Imports
from paths import DATA_PATH
#   Core
from core import GAME_NAME
from core.cvar import ServerVar
#   Weapons
from weapons.default import NoWeaponManager


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the game's ini path
_gamepath = DATA_PATH.joinpath('weapons', GAME_NAME + '.ini')


# =============================================================================
# >> CLASSES
# =============================================================================
class _WeaponManager(dict):
    '''Dictionary class to store basic weapon information'''

    def __init__(self, ini_file):
        '''Loads the ini file into the dictionary'''

        # Get the ConfigObj instance of the file
        ini = ConfigObj(ini_file, unrepr=True)

        # Get the "properties"
        properties = ini['properties']

        # Get the game's weapon prefix
        self.prefix = properties['prefix']

        # Get the game's m_iAmmo property
        self.ammoprop = properties['ammoprop']

        # Get the game's m_hMyWeapons property
        self.myweapons = properties['myweapons']

        # Store any special names
        self.special_names = ini.get('special names', {})

        # Store projectile names
        self.projectiles = ini.get('projectiles', {})

        # Store tags as a set
        self.tags = set()

        # Loop through all weapons
        for basename in ini['weapons']:

            # Get the weapon's full name
            name = self._format_name(basename)

            # Add the weapon to the dictionary
            self[name] = _Weapon(name, basename, ini['weapons'][basename])

            # Add the weapon's tags to the set of tags
            self.tags.update(self[name].tags)

    def __getitem__(self, item):
        '''Override __getitem__ to format the given name'''

        # Format the weapon's name
        name = self._format_name(item)

        # Return the weapon's instance
        return self.get(name, None)

    def __contains__(self, item):
        '''Override __contains__ to format the given name'''

        # Format the weapon's name
        name = self._format_name(item)

        # Return whether the weapon is in the dictionary
        return super(_WeaponManager, self).__contains__(name)

    def _format_name(self, item):
        '''Formats the name to include the game's weapon prefix'''

        # Set the weapon to lower-case
        name = item.lower()

        # Is the item a member of the special names?
        if name in self.special_names:

            # Get the value of the special name
            name = self.special_names[name]

        # Is the item a member of the projectiles?
        if name in self.projectiles:

            # Get the value of the projectile name
            name = self.projectiles[name]

        # Does the weapon start with the prefix?
        if not name.startswith(self.prefix):

            # Add the prefix to the name
            name = self.prefix + name

        # Return the name
        return name


class _Weapon(object):
    '''Class used to store information specific to the given weapon'''

    def __init__(self, name, basename, properties):
        '''Stores the base attributes for the weapon'''

        # Store the weapon's full name
        self.name = name

        # Store the weapon's base name
        self.basename = basename

        # Store the weapon's slot number
        self.slot = properties.get('slot', None)

        # Store the weapon's max ammo amount
        self._maxammo = properties.get('maxammo', None)

        # Store the weapon's ammo property
        self.ammoprop = properties.get('ammoprop', None)

        # Store the weapon's clip amount
        self.clip = properties.get('clip', 0)

        # Store the weapon's tags
        self.tags = properties.get('tags', 'all').split(',')

    @property
    def maxammo(self):
        '''Returns the maxammo amount for the weapon'''

        # Is the stored maxammo an integer?
        if isinstance(self._maxammo, int):

            # Return the value
            return self._maxammo

        # Get the cvar value of the maxammo
        return ServerVar(self._maxammo).GetInt()

# Does the current game have an ini file?
if _gamepath.isfile():

    # Get the _WeaponManager instance
    WeaponManager = _WeaponManager(_gamepath)

# Is there no ini file for the current game?
else:

    # Store WeaponManager as a NoWeaponManager instance
    # to raise an error anytime the manager is utilized
    WeaponManager = NoWeaponManager()
