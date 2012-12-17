# ../_libs/filters/players.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   ConfigObj
from configobj import ConfigObj

# Source.Python Imports
from Source import Engine
from Source import Player
from core import GameEngine
from core import GAME_NAME
from paths import DATA_PATH
#   Filters
from filters.iterator import _IterObject
from filters.manager import _BaseFilterManager
#   Players
from players.entity import PlayerEntity
from players.helpers import address_from_playerinfo
from players.helpers import basehandle_from_playerinfo
from players.helpers import edict_from_playerinfo
from players.helpers import index_from_playerinfo
from players.helpers import inthandle_from_playerinfo
from players.helpers import pointer_from_playerinfo
from players.helpers import uniqueid_from_playerinfo
from players.helpers import userid_from_playerinfo


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the team's file for the current game
_game_teams = ConfigObj(
    DATA_PATH.join('players', 'teams', GAME_NAME + '.ini'), unrepr=True)


# =============================================================================
# >> MAIN PLAYER ITER CLASSES
# =============================================================================
class _PlayerIterManager(_BaseFilterManager):
    '''Filter management class specifically for player iterating'''

# Get the _PlayerIterManager instance
PlayerIterManager = _PlayerIterManager()


class PlayerIter(_IterObject):
    '''Player iterate class'''

    # Store the manager for the player iterator
    manager = PlayerIterManager

    # Store the base iterator
    iterator = staticmethod(Player.Players)


# =============================================================================
# PLAYER TEAM CLASSES
# =============================================================================
class _PlayerTeams(dict):
    '''Class used to store team names for the current game'''

    def __setitem__(self, item, value):
        '''Adds a _Team instance for the given team name'''

        # Get the _Team instance
        instance = _Team(value)

        # Add the _Team instance for the given team name
        super(_PlayerTeams, self).__setitem__(item, instance)

# Get the _PlayerTeams instance
PlayerTeams = _PlayerTeams()


class _Team(object):
    '''Class used to store a team number and compare to a given player'''

    def __init__(self, team):
        '''Store the team number for future use'''

        # Store the team number
        self.team = team

    def _player_is_on_team(self, IPlayerInfo):
        '''Returns whether the player is on the team'''

        # Return whether the player is on the team
        return IPlayerInfo.GetTeamIndex() == self.team


# =============================================================================
# >> FILTER FUNCTIONS
# =============================================================================
def _is_player(IPlayerInfo):
    '''Always returns True, since this is a player'''
    return True


def _player_is_bot(IPlayerInfo):
    '''Returns whether a player is a bot'''
    return IPlayerInfo.IsFakeClient()


def _player_is_human(IPlayerInfo):
    '''Returns whether the player is a human'''
    return IPlayerInfo.IsPlayer()


def _player_is_alive(IPlayerInfo):
    '''Returns whether the player is alive'''
    return not IPlayerInfo.IsDead()


def _player_is_dead(IPlayerInfo):
    '''Returns whether the player is dead'''
    return IPlayerInfo.IsDead()

# Register the filter functions
PlayerIterManager.register_filter('all', _is_player)
PlayerIterManager.register_filter('bot', _player_is_bot)
PlayerIterManager.register_filter('human', _player_is_human)
PlayerIterManager.register_filter('alive', _player_is_alive)
PlayerIterManager.register_filter('dead', _player_is_dead)

# Loop through all teams in the game's team file
for team in _game_teams:

    # Add the team to the PlayerTeams dictionary
    PlayerTeams[team] = _game_teams[team]

    # Register the filter
    PlayerIterManager.register_filter(
        team, PlayerTeams[team]._player_is_on_team)

# Loop through all base team names
for number, team in enumerate(('un', 'spec', 't', 'ct')):

    # Has the team already been added to the PlayerTeams dictionary
    if team in PlayerTeams:

        # If it has been added, do not re-add it
        continue

    # Add the team to the PlayerTeams dictionary
    PlayerTeams[team] = number

    # Register the filter
    PlayerIterManager.register_filter(
        team, PlayerTeams[team]._player_is_on_team)


# =============================================================================
# >> RETURN TYPE FUNCTIONS
# =============================================================================
def _return_playerinfo(IPlayerInfo):
    '''Returns the player's IPlayerInfo instance'''
    return IPlayerInfo


def _return_player(IPlayerInfo):
    '''Returns the player's PlayerEntity instance'''
    return PlayerEntity(index_from_playerinfo(IPlayerInfo))


def _return_name(IPlayerInfo):
    '''Returns the player's name'''
    return IPlayerInfo.GetName()


def _return_steamid(IPlayerInfo):
    '''Returns the player's SteamID'''
    return IPlayerInfo.GetNetworkIDString()


def _return_location(IPlayerInfo):
    '''Returns the player's location Vector'''
    return IPlayerInfo.GetAbsOrigin()


def _return_kills(IPlayerInfo):
    '''Returns the player's kill count'''
    return IPlayerInfo.GetFragCount()


def _return_deaths(IPlayerInfo):
    '''Returns the player's death count'''
    return IPlayerInfo.GetDeathCount()


def _return_model(IPlayerInfo):
    '''Returns the player's model'''
    return IPlayerInfo.GetModelName()


def _return_health(IPlayerInfo):
    '''Returns the player's health value'''
    return IPlayerInfo.GetHealth()


def _return_armor(IPlayerInfo):
    '''Returns the player's armov value'''
    return IPlayerInfo.GetArmorValue()


def _return_weapon(IPlayerInfo):
    '''Returns the player's currently held weapon'''
    return IPlayerInfo.GetWeaponName()


def _return_language(IPlayerInfo):
    '''Returns the player's language'''
    return GameEngine.GetClientConVarValue(
        _return_index(IPlayerInfo), 'cl_language')


def _return_team(IPlayerInfo):
    '''Returns the player's team'''
    return IPlayerInfo.GetTeamIndex()

# Register the return type functions
PlayerIterManager.register_return_type('index', index_from_playerinfo)
PlayerIterManager.register_return_type('edict', edict_from_playerinfo)
PlayerIterManager.register_return_type(
    'basehandle', basehandle_from_playerinfo)
PlayerIterManager.register_return_type('inthandle', inthandle_from_playerinfo)
PlayerIterManager.register_return_type('pointer', pointer_from_playerinfo)
PlayerIterManager.register_return_type('userid', userid_from_playerinfo)
PlayerIterManager.register_return_type('uniqueid', uniqueid_from_playerinfo)
PlayerIterManager.register_return_type('address', address_from_playerinfo)
PlayerIterManager.register_return_type('info', _return_playerinfo)
PlayerIterManager.register_return_type('player', _return_player)
PlayerIterManager.register_return_type('name', _return_name)
PlayerIterManager.register_return_type('steamid', _return_steamid)
PlayerIterManager.register_return_type('location', _return_location)
PlayerIterManager.register_return_type('kills', _return_kills)
PlayerIterManager.register_return_type('deaths', _return_deaths)
PlayerIterManager.register_return_type('model', _return_model)
PlayerIterManager.register_return_type('health', _return_health)
PlayerIterManager.register_return_type('armor', _return_armor)
PlayerIterManager.register_return_type('weapon', _return_weapon)
PlayerIterManager.register_return_type('language', _return_language)
PlayerIterManager.register_return_type('team', _return_team)
