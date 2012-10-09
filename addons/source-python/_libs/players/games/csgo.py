# ../_libs/players/games/csgo.py


from weapons.manager import WeaponManager
from Source import Entity


class GameWeapons(object):

    def get_hegrenade_indexes(self):
        return self.get_weapon_index_list('weapon_hegrenade')

    def get_flashbang_indexes(self):
        return self.get_weapon_index_list('weapon_flashbang')

    def get_smoke_grenade_indexes(self):
        return self.get_weapon_index_list('weapon_smokegrenade')

    def get_incendiary_grenade_indexes(self):
        return self.get_weapon_index_list(is_type='incendiary')

    def get_decoy_grenade_indexes(self):
        return self.get_weapon_index_list('weapon_decoy')

    def get_hegrenade_count(self):
        return self._get_weapon_ammo('weapon_hegrenade')

    def get_flashbang_count(self):
        return self._get_weapon_ammo('weapon_flashbang')

    def get_smoke_grenade_count(self):
        return self._get_weapon_ammo('weapon_smokegrenade')

    def get_incendiary_grenade_count(self):
        return self._get_weapon_ammo(is_type='incendiary')

    def get_decoy_grenade_count(self):
        return self._get_weapon_ammo('weapon_decoy')

    def has_c4(self):
        for edict in Entity.Entities('weapon_c4'):
            handle = edict.GetNetworkable().GetEntityHandle().GetRefEHandle()
            if handle.ToInt() == self.handle:
                return True
        return False

    def set_hegrenade_count(self, value):
        self._set_weapon_count('weapon_hegrenade')

    def set_flashbang_count(self, value):
        self._set_weapon_count('weapon_flashbang')

    def set_smoke_grenade_count(self, value):
        self._set_weapon_count('weapon_smokegrenade')

    def set_incendiary_grenade_count(self, value):
        if self.team == 2:
            self._set_weapon_count('weapon_molotov')
        else:
            self._set_weapon_count('weapon_incgrenade')

    def set_decoy_grenade_count(self, value):
        self._set_weapon_count('weapon_decoy')

    def _set_weapon_count(self, classname):
        index = self.get_weapon_index(classname)
        if value < 1 and index is None:
            return
        if index is None:
            index = self.give_weapon(classname)
        weapon = WeaponEntity(index)
        self.SetPropInt(
            WeaponManager.ammoprop + '%03d' % weapon.ammoprop, value)
