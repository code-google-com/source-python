# ../_libs/commands/server/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from command_c import get_server_command
#   Commands
from commands.manager import _BaseCommandManager


# =============================================================================
# >> CLASSES
# =============================================================================
class _ServerCommandManager(_BaseCommandManager):
    '''Manager class used to register server commands'''

    # Store the base functions
    _get_command = staticmethod(get_server_command)

# Get the _ServerCommandManager instance
ServerCommandManager = _ServerCommandManager()
