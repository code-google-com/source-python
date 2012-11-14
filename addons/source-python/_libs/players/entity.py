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
#   Players
from players.helpers import address_of_playerinfo
from players.helpers import uniqueid_of_playerinfo
from players.weapons import _PlayerWeapons


# =============================================================================
# >> CLASSES
# =============================================================================
class PlayerEntity(BaseEntity, _PlayerWeapons):
    '''Class used to interact directly with players'''

    info = None

    def __init__(self, index):
        '''
            Override the __init__ method to add "player" to the
            _game_inis list and set the player's info attribute
        '''

        # Run the inherited class __init__ method
        super(PlayerEntity, self).__init__(index)

        # Add "player" to the _game_inis list
        self._game_inis.append('player')

        # Set the player's info attribute
        self.info = Player.PlayerOfIndex(index)

    def __setattr__(self, attr, value):
        '''Override __setattr__ to determine if PlayerEntity
            has the attribute instead of BaseEntity'''

        # Does the class have the given attribute?
        if hasattr(PlayerEntity, attr):

            # Set the attribute
            object.__setattr__(self, attr, value)

        # Otherwise
        else:

            # Set the attribute's value, if it can be found
            super(PlayerEntity, self).__setattr__(attr, value)

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
        return uniqueid_of_playerinfo(self.info)

    @property
    def address(self):
        '''Returns the player's IP address'''
        return address_of_playerinfo(self.info)

    def get_team(self):
        '''Returns the player's team'''
        return self.info.GetTeamIndex()

    def set_team(self, value):
        '''Sets a players team'''
        self.info.ChangeTeam(value)

    # Set the "team" property methods
    team = property(get_team, set_team)

    @classmethod
    def _is_valid_index_for_entity_type(cls, edict):
        '''Verifies that the given edict is of a player'''

        # Return whether the given edict is one of a player entity
        return edict.GetClassName() == 'player'
