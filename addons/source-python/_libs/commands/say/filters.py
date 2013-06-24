# ../_libs/commands/say/filters.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
# Commands
from commands.filters import _BaseFilter
from commands.say.manager import SayCommandManager


# =============================================================================
# >> CLASSES
# =============================================================================
class SayFilter(_BaseFilter):
    '''Class used to register a say filter'''

    # Store the class used to (un)register say filters
    _ManagerClass = SayCommandManager
