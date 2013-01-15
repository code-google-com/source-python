# ../_libs/commands/say/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Commands
from commands.manager import _CommandList
from commands.player import _AuthCallback
from commands.player import _PlayerCommandRegistry
#   Players
from players.helpers import playerinfo_from_index


# =============================================================================
# >> CLASSES
# =============================================================================
class _SayLists(list):
    '''Class used to store a list of say filters'''

    def append(self, callback):
        '''Override append to verify the callback is not already in the list'''

        # Is the callback already in the list?
        if not callback in self:

            # Add the callback to the list
            super(_SayLists, self).append(callback)

    def remove(self, callback):
        '''Override remove to verify the callback is in the list'''

        # Is the callback in the list?
        if callback in self:

            # Remove the callback from the list
            super(_SayLists, self).remove(callback)

    def AddToEnd(self, callback):
        '''Method used to redirect to append'''
        self.append(callback)

    def Remove(self, callback):
        '''Method used to redirect to remove'''
        self.remove(callback)

# Get the _SayLists instance
_SayFiltersList = _SayLists()


class _SayCommands(_SayLists):
    '''Class used to store a list of say command callbacks'''

    def __init__(self, name):
        self._name = name


class _SayCommandList(_CommandList):
    '''Class used to store callbacks for a say command'''

    _ContinueValue = True
    _BlockValue = False

    @staticmethod
    def _get_command_instance(name):
        '''Returns the say command list instance'''
        return _SayCommands(name)


class _SayAuthCallback(_AuthCallback):
    '''Class used to check authorization on say commands'''

    @staticmethod
    def _get_playerinfo(index):
        '''Returns the player's IPlayerInfo instance from the given index'''
        return playerinfo_from_index(index)


class _SayCommandRegistry(_PlayerCommandRegistry):
    '''Class used to store say commands and say filters with their callbacks'''

    _filters = _SayFiltersList
    _CommandListClass = _SayCommandList
    _AuthCallbackClass = _SayAuthCallback

# Get the _SayCommandRegistry instance
SayCommandRegistry = _SayCommandRegistry()
