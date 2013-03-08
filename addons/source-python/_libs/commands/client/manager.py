# ../_libs/commands/client/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Sys
import sys

# Source.Python Imports
from Source import ClientCmd
from excepthooks import ExceptHooks
#   Commands
from commands.manager import _CommandList
from commands.player import _AuthCallback
from commands.player import _PlayerCommandRegistry
#   Players
from players.helpers import playerinfo_from_edict


# =============================================================================
# >> CLASSES
# =============================================================================
class _ClientCommandList(_CommandList):
    '''Class used to store callbacks for a client command'''

    _ContinueValue = ClientCmd.ClientCommandReturn.CONTINUE
    _BlockValue = ClientCmd.ClientCommandReturn.BLOCK

    '''
        This section has been added until we can fix
        crashing issues with instance method callbacks
    '''
    @staticmethod
    def _command_called(edict, CCommand):
        command = CCommand[0]
        return ClientCommandRegistry._commands[
            command]._call_command(edict, CCommand)

    def _call_command(self, *args):
        return_val = True
        for callback in self:
            try:
                return_type = callback(*args)
                return_val = return_val and (
                    return_type is None or bool(return_type))
            except:
                error = sys.exc_info()
                ExceptHooks.print_exception(*error)
        if return_val:
            return self._ContinueValue
        return self._BlockValue

    '''
        End of added section
    '''

    @staticmethod
    def _get_command_instance(name):
        '''Returns the client command list instance'''
        return ClientCmd.GetClientCommand(name)


class _ClientAuthCallback(_AuthCallback):
    '''Class used to check authorization on client commands'''

    @staticmethod
    def _get_playerinfo(edict):
        '''Returns the player's IPlayerInfo instance from the given edict'''
        return playerinfo_from_edict(edict)


class _ClientCommandRegistry(_PlayerCommandRegistry):
    '''Class used to store client commands and
        client command filters with their callbacks'''

    # _filters = ClientCmd.ClientCommandFilters
    _CommandListClass = _ClientCommandList
    _AuthCallbackClass = _ClientAuthCallback

# Get the _ClientCommandRegistry instance
ClientCommandRegistry = _ClientCommandRegistry()
