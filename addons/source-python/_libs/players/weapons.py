# ../_libs/players/weapons.py

from Source import Engine
from Source import Entity
from path import path
from core import GAME_NAME
from entities.weapons.weapon import WeaponEntity
from filters.weapontags import WeaponTagIter
from weapons.manager import WeaponManager

_gamefile = path(__file__).parent.joinpath('games', GAME_NAME + '.py')

if _gamefile.isfile():
    _game_instance = __import__('players.games.%s' % GAME_NAME, fromlist=[''])
    GameWeapons = _game_instance.GameWeapons
else:
    GameWeapons = object


class _PlayerWeapons(GameWeapons):

    def get_primary(self):
        return self.get_weapon_index(is_filters='primary')

    def get_secondary(self):
        return self.get_weapon_index(is_filters='secondary')

    def get_ammo(self, weapon):
        classname = WeaponManager[weapon].classname
        return self._get_weapon_ammo(classname)

    def get_primary_ammo(self):
        return self._get_weapon_ammo(is_filters='primary')

    def get_secondary_ammo(self):
        return self._get_weapon_ammo(is_filters='secondary')

    def _get_weapon_ammo(self, classname=None, is_filters=[], not_filters=[]):
        index = self.get_weapon_index(classname, is_filters, not_filters)
        if index is None:
            return 0
        weapon = WeaponEntity(index)
        return self.GetPropInt(
            WeaponManager.ammoprop + '%03d' % weapon.ammoprop)

    def get_clip(self, weapon):
        classname = WeaponManager[weapon].name
        return self._get_weapon_clip(classname)

    def get_primary_clip(self):
        return self._get_weapon_clip(is_filters='primary')

    def get_secondary_clip(self):
        return self._get_weapon_clip(is_filters='secondary')

    def _get_weapon_clip(self, classname=None, is_filters=[], not_filters=[]):
        index = self.get_weapon_index(classname, is_filters, not_filters)
        if index is None:
            return 0
        weapon = WeaponEntity(index)
        return weapon.clip

    def get_weapon_index(self, classname=None, is_filters=[], not_filters=[]):
        '''Returns the first instance of the given weapon classname/type'''

        for index in self.weapon_indexes(classname, is_filters, not_filters):
            return index
        return None

    def get_weapon_index_list(
            self, classname=None, is_filters=[], not_filters=[]):
        '''Returns a list of weapon indexes for the player'''
        return list(self.weapon_indexes(classname, is_filters, not_filters))

    def weapon_indexes(self, classname=None, is_filters=[], not_filters=[]):
        '''
            Iterates over all currently held weapons, and yields their indexes
        '''

        # Loop through the length of m_hMyWeapons
        for offset in range(64):

            # Get the player's current weapon at this offset
            handle = self.GetPropInt(WeaponManager.myweapons + '%03i' % offset)

            # Is this an invalid handle?
            if handle == -1:

                # Move on to the next offset
                continue

            # Get the handles CBaseHandle instance
            bhandle = get_base_handle(handle)

            if bhandle is None:
                continue

            # Get the weapon's index
            index = bhandle.GetEntryIndex()

            # Get the weapon's edict
            edict = Engine.PEntityOfEntIndex(index)

            # Get the weapon's classname
            weapon_class = edict.GetClassName()

            # Was a classname given and the current
            # weapon is not of that classname?
            if not classname is None and weapon_class != classname:

                # Do not yield this index
                continue

            # Was a weapon type given and the
            # current weapon is not of that type?
            if ((is_filters or not_filters) and not weapon_class in
                    list(WeaponTagIter(is_filters, not_filters, 'classname'))):

                # Do not yield this index
                continue

            # Yield the index
            yield index

    def give_weapon(self, classname):
        edict = Entity.CreateEntity(classname)
        if edict is None:
            raise ValueError(
                'Could not create entity of type "%s"' % classname)
        weapon = WeaponEntity.get_instance_from_edict(edict)
        weapon.location = self.location
        return weapon.index

    def set_ammo(self, weapon, value):
        classname = WeaponManager[weapon].classname
        self._set_weapon_ammo(value, classname)

    def set_primary_ammo(self, value):
        self._set_weapon_ammo(value, is_filters='primary')

    def set_secondary_ammo(self, value):
        self._set_weapon_ammo(value, is_filters='secondary')

    def _set_weapon_ammo(
            self, value, classname=None, is_filters=[], not_filters=[]):
        index = self.get_weapon_index(classname, is_filters, not_filters)
        if index is None:
            raise
        weapon = WeaponEntity(index)
        self.SetPropInt(
            WeaponManager.ammoprop + '%03d' % weapon.ammoprop, value)

    def set_clip(self, weapon, value):
        classname = WeaponManager[weapon].classname
        self._set_weapon_clip(value, classname)

    def set_primary_clip(self, value):
        self._set_weapon_clip(value, is_filters='primary')

    def set_secondary_clip(self, value):
        self._set_weapon_clip(value, is_filters='secondary')

    def _set_weapon_clip(
            self, value, classname=None, is_filters=[], not_filters=[]):
        index = self.get_weapon_index(classname, is_filters, not_filters)
        if index is None:
            raise
        weapon = WeaponEntity(index)
        weapon.clip = value

    def add_ammo(self, weapon, value):
        classname = WeaponManager[weapon].classname
        self._add_weapon_ammo(value, classname)

    def add_primary_ammo(self, value):
        self._add_weapon_ammo(value, is_filters='primary')

    def add_secondary_ammo(self, value):
        self._add_weapon_ammo(value, is_filters='secondary')

    def _add_weapon_ammo(
            self, value, classname=None, is_filters=[], not_filters=[]):
        index = self.get_weapon_index(classname, is_filters, not_filters)
        if index is None:
            raise
        weapon = WeaponEntity(index)
        current = self.GetPropInt(
            WeaponManager.ammoprop + '%03d' % weapon.ammoprop)
        self.SetPropInt(
            WeaponManager.ammoprop + '%03d' % weapon.ammoprop, current + value)

    def add_clip(self, weapon, value):
        classname = WeaponManager[weapon].classname
        self._add_weapon_clip(value, classname)

    def add_primary_clip(self, value):
        self._add_weapon_clip(value, is_filters='primary')

    def add_secondary_clip(self, value):
        self._add_weapon_clip(value, is_filters='secondary')

    def _add_weapon_clip(
            self, value, classname=None, is_filters=[], not_filters=[]):
        index = self.get_weapon_index(classname, is_filters, not_filters)
        if index is None:
            raise
        weapon = WeaponEntity(index)
        weapon.clip += value

    def set_weapon_color(self, red, green, blue, alpha=None):
        handle = self.active_weapon
        bhandle = get_base_handle(handle)
        if bhandle is None:
            return
        index = bhandle.GetEntryIndex()
        WeaponEntity(index).set_color(red, green, blue, alpha)


def get_base_handle(handle):
    for edict in Entity.Entities():
        try:
            network = edict.GetNetworkable()
            if network is None:
                continue
            current = network.GetEntityHandle().GetRefEHandle()
            if current.ToInt() == handle:
                return current
        except:
            continue
    return None
