# ../_libs/players/entity.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Player
from core import GameEngine
#   Entities
from entities.entity import BaseEntity
#   Players
from players.helpers import address_from_playerinfo
from players.helpers import uniqueid_from_playerinfo
from players.weapons import _PlayerWeapons


# =============================================================================
# >> CLASSES
# =============================================================================
class PlayerEntity(BaseEntity, _PlayerWeapons):
    '''Class used to interact directly with players'''

    info = None

    def __init__(self, index):
        '''Override the __init__ method to set the
            "entities" attribute and set the PlayerInfo'''

        # Set the player's info attribute
        self.info = Player.PlayerOfIndex(index)

        # Is the IPlayerInfo instance valid?
        if self.info is None:

            raise ValueError(
                'Invalid IPlayerInfo instance for index "%s"' % index)

        # Set the entities attribute
        self.entities = frozenset(['entity', 'player'])

    @property
    def instances(self):
        '''Yields the player's IPlayerInfo and Edict instances'''

        # Yield the instances
        yield self.info
        yield self.edict

    @property
    def userid(self):
        '''Returns the player's userid'''
        return GameEngine.GetPlayerUserId(self.edict)

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
        return GameEngine.GetClientConVarValue(self.index, 'cl_language')

    @property
    def uniqueid(self):
        '''Returns the player's uniqueid'''
        return uniqueid_from_playerinfo(self.info)

    @property
    def address(self):
        '''Returns the player's IP address'''
        return address_from_playerinfo(self.info)

    def get_team(self):
        '''Returns the player's team'''
        return self.info.GetTeamIndex()

    def set_team(self, value):
        '''Sets a players team'''
        self.info.ChangeTeam(value)

    # Set the "team" property methods
    team = property(get_team, set_team)
