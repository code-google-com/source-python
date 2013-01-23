# ../_libs/commands/say/command.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Commands
from commands.command import _PlayerCommandRegistration
from commands.say.manager import SayCommandRegistry


# =============================================================================
# >> CLASSES
# =============================================================================
class SayCommand(_PlayerCommandRegistration):
    '''Class used to register say commands using a decorator'''

    _RegistrationClass = SayCommandRegistry
