# ../_libs/commands/__init__.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Cvar
#   Core
from core.decorators import BaseDecorator


# =============================================================================
# >> CLASSES
# =============================================================================
class _ServerCommandDecorator(BaseDecorator):
    '''Decorator class used to register server commands'''

    def __init__(self, class_instance):
        '''Stores the instanciating class' unregister method'''
        self._unregister_decorator = class_instance._unregister_server_command


class ServerCommand(object):
    '''Class used to register server commands using a decorator'''

    def __init__(self, name, description, flags=0):
        '''Stores the name and description of the command'''
        self.name = name
        self.description = description
        self.flags = flags

    def __call__(self, callback):
        '''Registers the command with the given callback'''

        # Store the callback
        self.callback = callback

        # Register the command
        self._command = Cvar.GetCommand(
            self.name, self.description, self.flags)

        # Add the callback to the commands callback list
        self._command.AddToEnd(self.callback)

        # Return a decorator instance of this class
        return _ServerCommandDecorator(self)

    def _unregister_server_command(self):
        '''Unregisters the callback from the command'''
        self._command.Remove(self.callback)
