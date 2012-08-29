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
from players import EasyPlayer


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

    def _PlayerIsOnTeam(self, IPlayerInfo):
        '''Returns whether the player is on the team'''

        # Return whether the player is on the team
        return IPlayerInfo.GetTeamIndex() == self.team


# =============================================================================
# >> FILTER FUNCTIONS
# =============================================================================
def _IsPlayer(IPlayerInfo):
    '''Always returns True, since this is a player'''
    return True


def _PlayerIsBot(IPlayerInfo):
    '''Returns whether a player is a bot'''
    return IPlayerInfo.IsFakeClient()


def _PlayerIsHuman(IPlayerInfo):
    '''Returns whether the player is a human'''
    return IPlayerInfo.IsPlayer()


def _PlayerIsAlive(IPlayerInfo):
    '''Returns whether the player is alive'''
    return not IPlayerInfo.IsDead()


def _PlayerIsDead(IPlayerInfo):
    '''Returns whether the player is dead'''
    return IPlayerInfo.IsDead()

# Register the filter functions
PlayerIterManager.RegisterFilter('all', _IsPlayer)
PlayerIterManager.RegisterFilter('bot', _PlayerIsBot)
PlayerIterManager.RegisterFilter('human', _PlayerIsHuman)
PlayerIterManager.RegisterFilter('alive', _PlayerIsAlive)
PlayerIterManager.RegisterFilter('dead', _PlayerIsDead)

# Loop through all teams in the game's team file
for team in _game_teams:

    # Add the team to the PlayerTeams dictionary
    PlayerTeams[team] = _game_teams[team]

    # Register the filter
    PlayerIterManager.RegisterFilter(team, PlayerTeams[team]._PlayerIsOnTeam)

# Loop through all base team names
for number, team in enumerate(('un', 'spec', 't', 'ct')):

    # Has the team already been added to the PlayerTeams dictionary
    if team in PlayerTeams:

        # If it has been added, do not re-add it
        continue

    # Add the team to the PlayerTeams dictionary
    PlayerTeams[team] = number

    # Register the filter
    PlayerIterManager.RegisterFilter(team, PlayerTeams[team]._PlayerIsOnTeam)


# =============================================================================
# >> RETURN TYPE FUNCTIONS
# =============================================================================
def _ReturnIndex(IPlayerInfo):
    '''Returns the player's index'''
    return Engine.IndexOfEdict(Player.EdictOfPlayer(IPlayerInfo))


def _ReturnEntity(IPlayerInfo):
    '''Returns the player's edict'''
    return Player.EdictOfPlayer(IPlayerInfo)


def _ReturnPlayerInfo(IPlayerInfo):
    '''Returns the player's IPlayerInfo instance'''
    return IPlayerInfo


def _ReturnUserid(IPlayerInfo):
    '''Returns the player's userid'''
    return IPlayerInfo.GetUserID()


def _ReturnPlayer(IPlayerInfo):
    '''Returns the player's EasyPlayer instance'''
    return EasyPlayer(**{'player': IPlayerInfo})


def _ReturnName(IPlayerInfo):
    '''Returns the player's name'''
    return IPlayerInfo.GetName()


def _ReturnSteamID(IPlayerInfo):
    '''Returns the player's SteamID'''
    return IPlayerInfo.GetNetworkIDString()


def _ReturnHandle(IPlayerInfo):
    '''Returns the player's handle'''
    return Player.EdictOfPlayer(
        IPlayerInfo).GetNetworkable().GetEntityHandle().GetRefEHandle().ToInt()


def _ReturnLocation(IPlayerInfo):
    '''Returns the player's location Vector'''
    return IPlayerInfo.GetAbsOrigin()


def _ReturnKills(IPlayerInfo):
    '''Returns the player's kill count'''
    return IPlayerInfo.GetFragCount()


def _ReturnDeaths(IPlayerInfo):
    '''Returns the player's death count'''
    return IPlayerInfo.GetDeathCount()


def _ReturnModel(IPlayerInfo):
    '''Returns the player's model'''
    return IPlayerInfo.GetModelName()


def _ReturnHealth(IPlayerInfo):
    '''Returns the player's health value'''
    return IPlayerInfo.GetHealth()


def _ReturnArmor(IPlayerInfo):
    '''Returns the player's armov value'''
    return IPlayerInfo.GetArmorValue()


def _ReturnWeapon(IPlayerInfo):
    '''Returns the player's currently held weapon'''
    return IPlayerInfo.GetWeaponName()


#def _ReturnLanguage(IPlayerInfo):
#    '''Returns the player's language'''
#    return 


def _ReturnTeam(IPlayerInfo):
    '''Returns the player's team'''
    return IPlayerInfo.GetTeamIndex()

# Register the return type functions
PlayerIterManager.RegisterReturnType('index', _ReturnIndex)
PlayerIterManager.RegisterReturnType('entity', _ReturnEntity)
PlayerIterManager.RegisterReturnType('info', _ReturnPlayerInfo)
PlayerIterManager.RegisterReturnType('userid', _ReturnUserid)
PlayerIterManager.RegisterReturnType('player', _ReturnPlayer)
PlayerIterManager.RegisterReturnType('name', _ReturnName)
PlayerIterManager.RegisterReturnType('steamid', _ReturnSteamID)
PlayerIterManager.RegisterReturnType('handle', _ReturnHandle)
PlayerIterManager.RegisterReturnType('location', _ReturnLocation)
PlayerIterManager.RegisterReturnType('kills', _ReturnKills)
PlayerIterManager.RegisterReturnType('deaths', _ReturnDeaths)
PlayerIterManager.RegisterReturnType('model', _ReturnModel)
PlayerIterManager.RegisterReturnType('health', _ReturnHealth)
PlayerIterManager.RegisterReturnType('armor', _ReturnArmor)
PlayerIterManager.RegisterReturnType('weapon', _ReturnWeapon)
#PlayerIterManager.RegisterReturnType('language', _ReturnLanguage)
PlayerIterManager.RegisterReturnType('team', _ReturnTeam)
