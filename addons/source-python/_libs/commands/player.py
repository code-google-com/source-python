# ../_libs/commands/player.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Commands
from commands.manager import _BaseCommandManager
from commands.auth import _AuthCallback


# =============================================================================
# >> ALL DECLARATION
# =============================================================================
# Set all to an empty list
__all__ = []


# =============================================================================
# >> CLASSES
# =============================================================================
class _PlayerCommandManager(_BaseCommandManager):
    '''Base class used to (un)register client/say commands'''

    # Store the base attributes
    _use_args = False
    _callback_manager = _AuthCallback
