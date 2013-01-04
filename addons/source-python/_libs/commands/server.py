# ../_libs/commands/server.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Cvar
#   Commands
from commands.base import CommandRegistration


# =============================================================================
# >> CLASSES
# =============================================================================
class ServerCommand(CommandRegistration):
    '''Class used to register server commands using a decorator'''

    def __init__(self, name, description, flags=0):
        '''Stores the name, description, and flags of the command'''
        self.name = name
        self.description = description
        self.flags = flags

    def _register_command(self):
        '''Registers the command with the instance's
            callback and returns its instance'''

        return Cvar.GetCommand(self.name, self.description, self.flags)

    def _command_called(self, CCommand):
        '''Called when the command is called on the server'''

        # Call the callback and get the return type
        return_type = self.callback(CCommand)

        # Was a False value returned?
        if return_type is None or return_type:

            # If not, allow the command to continue
            return Cvar.CommandReturn.CONTINUE

        # Block the command from executing
        return Cvar.CommandReturn.BLOCK
