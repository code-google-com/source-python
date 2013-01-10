# ../_libs/commands/client.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import ClientCmd
#   Commands
from commands.base import CommandRegistration


# =============================================================================
# >> CLASSES
# =============================================================================
class ClientCommand(CommandRegistration):
    '''Class used to register server commands using a decorator'''

    def __init__(self, *names):
        '''Stores the name of the command'''
        self.names = names

    def _register_command(self, name):
        '''Registers the command with the instance's
            callback and returns its instance'''

        return ClientCmd.GetClientCommand(name)

    def _command_called(self, edict, CCommand):
        '''Called when a client calls the command'''

        # Call the callback and get the return type
        return_type = self.callback(edict, CCommand)

        # Was a False value returned?
        if return_type is None or return_type:

            # If not, allow the command to continue
            return ClientCmd.ClientCommandReturn.CONTINUE

        # Block the command from executing
        return ClientCmd.ClientCommandReturn.BLOCK
