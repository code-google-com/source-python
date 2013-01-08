# ../_libs/commands/__init__.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Shared
#   Commands
from commands.server import ServerCommand
from commands.say.command import SayCommandDictionary
from commands.say.command import SayCommand
from commands.say.filter import SayFilterList
from commands.say.filter import SayFilter


# =============================================================================
# >> FUNCTIONS
# =============================================================================
# Register the "say" command
@ServerCommand('say', 'Say Command Registration')
def _say_command(CCommand):
    '''Called when someone uses the "say" command'''
    return _say_commands(CCommand)


# Register the "say_team" command
@ServerCommand('say_team', 'SayTeam Command Registration')
def _say_team_command(CCommand):
    '''Called when someone uses the "say_team" command'''
    return _say_commands(CCommand)


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
    if not (name in SayCommandDictionary or SayFilterList):

        # If not, returt True
        return True

    # Get the index of the player that issued the command
    index = Shared.GetCommandIndex()

    # Get a bool value for whether the command was team-only
    teamonly = CCommand[0] == 'say_team'

    # Was a registered command used?
    if name in SayCommandDictionary:

        # Loop through each callback for the given command
        for instance in SayCommandDictionary[name]:

            # Call the callback
            return_type = instance(index, teamonly, CCommand)

            # Does the command now need blocked?
            if not return_type is None and not return_type:

                # Block the rest of the callbacks
                return False

    # Loop through all say filters
    for callback in SayFilterList:

        # Call the say filter
        return_type = callback(index, teamonly, CCommand)

        # Does the command now need blocked?
        if not return_type is None and not return_type:

            # Block the rest of the say filters
            return False

    # Allow the text to print in chat
    return True
