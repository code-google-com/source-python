# ../_libs/commands/say/__init__.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Sys
import sys

# Source.Python Imports
from Source import Shared
#   Commands
from commands.say.command import SayCommand
from commands.say.filter import SayFilter
from commands.say.manager import SayCommandRegistry
from commands.server.command import ServerCommand as _ServerCommand
#   Core
from core.excepthook import ExceptHooks


# =============================================================================
# >> FUNCTIONS
# =============================================================================
@_ServerCommand(('say', 'say_team'))
def _say_commands(CCommand):
    '''Called when someone uses either the "say" or "say_team" command'''

    # Use try/except in case no arguments are given
    try:

        # Get the first word in case it is a command
        name = CCommand[1].split()[0]

    # Was an IndexError encountered
    except IndexError:

        # If so, simply return True
        return True

    # Is the first word a command or are there any say filters?
    if (not name in SayCommandRegistry._commands
            and not SayCommandRegistry._filters):

        # If not, return True
        return True

    # Get the index of the player that issued the command
    index = Shared.GetCommandIndex()

    # Get a bool value for whether the command was team-only
    teamonly = CCommand[0] == 'say_team'

    # Was a registered command used?
    if name in SayCommandRegistry._commands:

        return_val =  SayCommandRegistry._commands[
            name]._command_called(index, teamonly, CCommand)

    # Loop through all say filters
    for callback in SayCommandRegistry._filters:

        # Use try/except in case an error is encountered during a callback
        try:

            # Call the say filter
            return_type = callback(index, teamonly, CCommand)

            # Does the command now need blocked?
            if not return_type is None and not return_type:

                # Block the rest of the say filters
                return False

        # Was an error encountered?
        except:

            # Get the error
            error = sys.exc_info()

            # Print the exception to the console
            ExceptHooks.print_exception(*error)

    # Return the return value set by Say Commands
    return return_val
