# ../_libs/commands/client/filter.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Commands
from commands.filter import _BaseFilter
from commands.client.manager import ClientCommandManager


# =============================================================================
# >> CLASSES
# =============================================================================
class ClientCommandFilter(_BaseFilter):
    '''Class used to register a client command filter'''

    # Store the class used to (un)register client command filters
    _ManagerClass = ClientCommandManager
