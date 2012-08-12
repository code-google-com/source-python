# ../_libs/filters/players.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Engine
from core import GameEngine
#   Filters
from filters.iterator import _IterObject
from filters.manager import _BaseFilterManager


# =============================================================================
# >> CLASSES
# =============================================================================
class _PlayerIterManager(_BaseFilterManager):
    '''Filter management class specifically for player iterating'''


# Get the _PlayerIterManager instance
PlayerIterManager = _PlayerIterManager()


'''
# =============================================================================
# >> TEMPORARY FUNCTION
# =============================================================================
'''
def IterIndexes():
    for index in range(1, 65):
        entity = Engine.PEntityOfEntIndex(index)
        userid = GameEngine.GetPlayerUserId(entity)
        if userid != -1:
            yield index
'''
# =============================================================================
# >> TEMPORARY FUNCTION
# =============================================================================
'''


class PlayerIter(_IterObject):
    manager = PlayerIterManager
    iterator = staticmethod(IterIndexes)


# =============================================================================
# >> FILTER FUNCTIONS
# =============================================================================
def _IsPlayer(index):
    return True


def _PlayerIsBot(index):
    return True


def _PlayerIsHuman(index):
    return True

# Register the filter functions
PlayerIterManager.RegisterFilter('all', _IsPlayer)
PlayerIterManager.RegisterFilter('bot', _PlayerIsBot)
PlayerIterManager.RegisterFilter('human', _PlayerIsHuman)


# =============================================================================
# >> RETURN TYPE FUNCTIONS
# =============================================================================
def _ReturnIndex(index):
    return index


def _ReturnEntity(index):
    return Engine.PEntityOfEntIndex(index)


def _ReturnUserid(index):
    return GameEngine.GetPlayerUserId(_ReturnEntity(index))

# Register the return type functions
PlayerIterManager.RegisterReturnType('index', _ReturnIndex)
PlayerIterManager.RegisterReturnType('entity', _ReturnEntity)
PlayerIterManager.RegisterReturnType('userid', _ReturnUserid)
