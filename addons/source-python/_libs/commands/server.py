# ../_libs/commands/server.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Sys
import sys

# Source.Python Imports
from Source import Cvar
#   Commands
from commands.base import CommandRegistration
#   Core
from core.excepthook import ExceptHooks


# =============================================================================
# >> CLASSES
# =============================================================================
class ServerCommand(CommandRegistration):
    '''Class used to register server commands using a decorator'''

    def __init__(self, names, description='', flags=0):
        '''Stores the name, description, and flags of the command'''

        # Was only one command given?
        if isinstance(names, str):

            # Make the names a list
            names = [names]

        # Are the names a list or tuple?
        if not type(names) in (list, tuple):

            # Raise an error
            raise TypeError('ServerCommand commands must be passed ' +
                'as a list, tuple, or string, not "%s"' % type(names).__name__)

        # Store the list of command names
        self.names = names

        # Store the description and flags
        self.description = description
        self.flags = flags

    def _register_command(self, name):
        '''Registers the commands with the instance's
            callback and returns its instance'''

        return Cvar.GetCommand(name, self.description, self.flags)

    def _command_called(self, CCommand):
        '''Called when the command is called on the server'''

        # Use try/except in case an error is encountered
        try:

            # Call the callback and get the return type
            return_type = self.callback(CCommand)

        # Was an error encountered?
        except:

            # Get the error
            error = sys.exc_info()

            # Print the exception to the console
            ExceptHooks.print_exception(*error)

            # No need to go further
            return Cvar.CommandReturn.CONTINUE

        # Was a False value returned?
        if return_type is None or return_type:

            # If not, allow the command to continue
            return Cvar.CommandReturn.CONTINUE

        # Block the command from executing
        return Cvar.CommandReturn.BLOCK
