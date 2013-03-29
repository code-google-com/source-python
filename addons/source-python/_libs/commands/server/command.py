# ../_libs/commands/server/command.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Commands
from commands.command import _CommandRegistration
from commands.server.manager import ServerCommandRegistry


# =============================================================================
# >> CLASSES
# =============================================================================
class ServerCommand(_CommandRegistration):
    '''Class used to register server commands using a decorator'''

    _RegistrationClass = ServerCommandRegistry

    def __init__(self, names, description='', flags=0):
        '''Stores the given arguments'''
        self.names = names
        self.args = (description, flags)
