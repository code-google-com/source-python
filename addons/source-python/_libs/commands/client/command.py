# ../_libs/commands/client/command.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Commands
from commands.command import _PlayerCommandRegistration
from commands.client.manager import ClientCommandRegistry


# =============================================================================
# >> CLASSES
# =============================================================================
class ClientCommand(_PlayerCommandRegistration):
    '''Class used to register server commands using a decorator'''

    _RegistrationClass = ClientCommandRegistry
