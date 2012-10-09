# ../_libs/players/entity.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Engine
from Source import Player
#   Core
from core import GameEngine
#   Entities
from entities.entity import BaseEntity
from players.weapons import _PlayerWeapons


# =============================================================================
# >> CLASSES
# =============================================================================
class PlayerEntity(BaseEntity, _PlayerWeapons):
    '''Class used to interact directly with players'''

    def __init__(self, index):
        '''Override the __init__ method to add "player" to the _inis list'''

        # Run the inherited class __init__ method
        super(PlayerEntity, self).__init__(index)

        # Add the player's info to the dictionary
        self['info'] = Player.PlayerOfIndex(index)

        # Add "player" to the _inis list
        self._inis.append('player')

    @property
    def instances(self):
        '''Yields the player's IPlayerInfo and Edict instances'''

        # Yield the instances
        yield self.info
        yield self.edict

    @property
    def userid(self):
        '''Returns the player's userid'''
        return Engine.GetPlayerUserID(self.edict)

    @property
    def steamid(self):
        '''Returns the player's SteamID'''
        return self.info.GetNetworkIDString()

    @property
    def name(self):
        '''Returns the player's name'''
        return self.info.GetName()

    @property
    def isdead(self):
        '''Returns if the player is dead or alive'''
        return self.info.IsDead()

    @property
    def language(self):
        '''Returns the player's language'''
        return GameEngine.GetClientConVarValue(self.info, 'cl_language')

    @property
    def uniqueid(self):
        '''Returns the player's uniqueid'''
        return get_uniqueid_from_player(self.info)

    def get_team(self):
        '''Returns the player's team'''
        return self.info.GetTeamIndex()

    def set_team(self, value):
        '''Sets a players team'''
        self.info.ChangeTeam(value)

    # Set the "team" property methods
    team = property(get_team, set_team)

    def respawn(self):
        '''Respawns the player'''

        # Set the player's PlayerState property
        self.set_property('state', 0)

        # Set the player's LifeState property
        self.set_property('lifestate', 512)

        # Spawn the player
        self.edict.DispatchSpawn()

    @classmethod
    def _is_valid_index_for_entity_type(cls, edict):
        '''Verifies that the given edict is of a player'''

        # Return whether the given edict is one of a player entity
        return edict.GetClassName() == 'player'

    @classmethod
    def get_instance_from_userid(cls, userid):
        '''Returns a class instance for the given userid'''

        # Get the index of the given userid
        index = Player.IndexOfUserid(userid)

        # Return a class instance for the index
        return cls(index)

    @classmethod
    def get_instance_from_playerinfo(cls, playerinfo):
        '''Returns a class instance for the given IPlayerInfo instance'''

        # Get the edict of the IPlayerInfo instance
        edict = Player.EdictOfPlayer(playerinfo)

        # Return a class instance for the edict
        return cls.get_instance_from_edict(edict)

    @classmethod
    def get_instance_from_steamid(cls, steamid):
        '''Returns a class instance for the given SteamID'''

        # Loop through all players on the server
        for player in Player.Players():

            # Get the current player's SteamID
            current = player.GetNetworkIDString()

            # Is this the SteamID we are looking for?
            if current == steamid:

                # Return a class instance
                return cls.get_instance_from_playerinfo(player)

        # If the SteamID is not found, raise an error
        raise ValueError('Invalid SteamID "%s"' % steamid)

    @classmethod
    def get_instance_from_uniqueid(cls, uniqueid):
        '''Returns a class instance for the given UniqueID'''

        # Loop through all players on the server
        for player in Player.Players():

            # Get the current player's UniqueID
            current = get_uniqueid_from_player(player)

            # Is this the UniqueID we are looking for?
            if current == uniqueid:

                # Return a class instance
                return cls.get_instance_from_playerinfo(player)

        # If the UniqueID is not found, raise an error
        raise ValueError('Invalid UniqueID "%s"' % uniqueid)

    @classmethod
    def get_instance_from_name(cls, name):
        '''Returns a class instance for the given name'''

        # Loop through all players on the server
        for player in Player.Players():

            # Get the current player's name
            current = player.GetName()

            # Is this the name we are looking for?
            if current == name:

                # Return a class instance
                return cls.get_instance_from_playerinfo(player)

        # If the name is not found, raise an error
        raise ValueError('Invalid name "%s"' % name)


def get_uniqueid_from_player(player):
    '''Returns the UniqueID for the given player'''

    # Is the player a Bot?
    if player.IsFakeClient():

        # Return the bot's UniqueID
        return 'BOT_%s' % player.GetName()

    # Get the player's SteamID
    steamid = player.GetNetworkIDString()

    # Is this a Lan SteamID?
    if 'LAN' in steamid:

        # Get the player's edict instance
        edict = Player.EdictOfPlayer(player)

        # Get the player's index
        index = Engine.IndexOfEdict(edict)

        # Get the player's NetInfo instance
        netinfo = GameEngine.GetPlayerNetInfo(index)

        # Get the player's IP Address
        address = netinfo.GetAddress()

        # Return the Lan player's ID
        return 'LAN_%s' % '_'.join(address.split(':')[0].split('.'))

    # Return the player's SteamID
    return steamid
