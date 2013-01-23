# ../_libs/players/helpers.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Player
#   Core
from core import GameEngine
#   Entities
from entities.helpers import *


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get an instance of the PlayerInfoManager
_player_info_manager = Player.GetPlayerInfoManager()

# =============================================================================
# >> HELPER FUNCTIONS
# =============================================================================
def index_from_userid(userid):
    '''Returns an index from the given userid'''
    return Player.IndexOfUserid(userid)


def index_from_playerinfo(playerinfo):
    '''Returns an index from the given IPlayerInfo instance'''
    return index_from_edict(edict_from_playerinfo(playerinfo))


def edict_from_userid(userid):
    '''Returns an edict from the given userid'''
    return Player.EdictOfUserid(userid)


def edict_from_playerinfo(playerinfo):
    '''Returns an edict from the given IPlayerInfo instance'''
    return Player.EdictOfPlayer(playerinfo)


def basehandle_from_userid(userid):
    '''Returns a BaseHandle instance from the given userid'''
    return basehandle_from_edict(edict_from_userid(userid))


def basehandle_from_playerinfo(playerinfo):
    '''Returns a BaseHandle instance from the given IPlayerInfo instance'''
    return basehandle_from_edict(edict_from_playerinfo(playerinfo))


def inthandle_from_userid(userid):
    '''Returns a handle in int form from the given userid'''
    return inthandle_from_basehandle(basehandle_from_userid(userid))


def inthandle_from_playerinfo(playerinfo):
    '''Returns a handle in int form from the given IPlayerInfo instance'''
    return inthandle_from_basehandle(basehandle_from_playerinfo(playerinfo))


def pointer_from_userid(userid):
    '''Returns a BaseEntity pointer from the given userid'''
    return pointer_from_edict(edict_from_userid(userid))


def pointer_from_playerinfo(playerinfo):
    '''Returns a BaseEntity pointer from the given IPlayerInfo instance'''
    return pointer_from_edict(edict_from_playerinfo(playerinfo))


def userid_from_index(index):
    '''Returns a userid from the given index'''
    return userid_from_edict(edict_from_index(index))


def userid_from_edict(edict):
    '''Returns a userid from the given edict'''
    return GameEngine.GetPlayerUserId(edict)


def userid_from_basehandle(bhandle):
    '''Returns a userid from the given BaseHandle instance'''
    return userid_from_index(index_from_basehandle(bhandle))


def userid_from_inthandle(ihandle):
    '''Returns a userid from the given handle in int form'''
    return userid_from_index(index_from_inthandle(ihandle))


def userid_from_pointer(pointer):
    '''Returns a userid from the given BaseEntity pointer'''
    return userid_from_index(index_from_pointer(pointer))


def userid_from_playerinfo(playerinfo):
    '''Returns a userid from the given IPlayerInfo instance'''
    return playerinfo.GetUserID()


def playerinfo_from_index(index):
    '''Returns an IPlayerInfo instance from the given index'''
    return Player.PlayerOfIndex(index)


def playerinfo_from_edict(edict):
    '''Returns an IPlayerInfo instance from the given edict'''
    return _player_info_manager.GetPlayerInfo(edict)


def playerinfo_from_basehandle(bhandle):
    '''Returns an IPlayerInfo instance from the given BaseHandle instance'''
    return playerinfo_from_index(index_from_basehandle(bhandle))


def playerinfo_from_inthandle(ihandle):
    '''Returns an IPlayerInfo instance from the given handle in int form'''
    return playerinfo_from_index(index_from_inthandle(ihandle))


def playerinfo_from_pointer(pointer):
    '''Returns an IPlayerInfo instance from the given BaseEntity pointer'''
    return playerinfo_from_index(index_from_pointer(pointer))


def playerinfo_from_userid(userid):
    '''Returns an IPlayerInfo instance from the given userid'''
    return Player.PlayerOfUserid(userid)


# =============================================================================
# >> OTHER HELPER FUNCTIONS
# =============================================================================
def index_from_steamid(steamid):
    '''Returns an index from the given SteamID'''

    # Loop through all players on the server
    for player in Player.Players():

        # Is the current player's SteamID the same as the one given?
        if player.GetNetworkIDString() == steamid:

            # Return the index of the current player
            return index_from_playerinfo(player)

    # If no player found with a matching SteamID, raise an error
    raise ValueError('Invalid SteamID "%s"' % steamid)


def index_from_uniqueid(uniqueid):
    '''Returns an index from the given UniqueID'''

    # Loop through all players on the server
    for player in Player.Players():

        # Is the current player's UniqueID the same as the one given?
        if uniqueid_from_playerinfo(player) == uniqueid:

            # Return the index of the current player
            return index_from_playerinfo(player)

    # If no player found with a matching UniqueID, raise an error
    raise ValueError('Invalid UniqueID "%s"' % uniqueid)


def index_from_name(name):
    '''Returns an index from the given player name'''

    # Loop through all players on the server
    for player in Player.Players():

        # Is the current player's name the same as the one given?
        if player.GetName() == name:

            # Return the index of the current player
            return index_from_playerinfo(player)

    # If no player found with a matching name, raise an error
    raise ValueError('Invalid name "%s"' % name)


def uniqueid_from_playerinfo(player):
    '''Returns the UniqueID for the given player'''

    # Is the player a Bot?
    if player.IsFakeClient():

        # Return the bot's UniqueID
        return 'BOT_%s' % player.GetName()

    # Get the player's SteamID
    steamid = player.GetNetworkIDString()

    # Is this a Lan SteamID?
    if 'LAN' in steamid:

        # Get the player's IP address
        address = address_from_player(player)

        # Return the Lan player's ID
        return 'LAN_%s' % '_'.join(address.split(':')[0].split('.'))

    # Return the player's SteamID
    return steamid


def address_from_playerinfo(player):
    '''Returns the IP address for the given player'''

    # Get the player's index
    index = index_from_playerinfo(player)

    # Get the player's NetInfo instance
    netinfo = GameEngine.GetPlayerNetInfo(index)

    # Return the player's IP Address
    return netinfo.GetAddress()
