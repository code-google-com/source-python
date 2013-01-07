# ../_libs/commands/base.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import AutoUnload


# =============================================================================
# >> CLASSES
# =============================================================================
class _CommandDecorator(AutoUnload):
    '''Decorator class used to register/unregister commands'''

    def __init__(self, class_instance):
        '''Stores the instanciating class' unregister method'''
        self._command_called = class_instance._command_called
        self._unload_instance = class_instance._unregister_command


class CommandRegistration(object):
    '''Base command registration class'''

    def __call__(self, callback):
        '''Registers the command to the given callback'''

        # Store the callback
        self.callback = callback

        # Register the command
        self._command = self._register_command()

        self._decorator_instance = _CommandDecorator(self)

        # Add the callback to the commands callback list
        self._command.AddToEnd(self._decorator_instance._command_called)

        # Return a decorator instance of this class
        return self._decorator_instance

    def _unregister_command(self):
        '''Unregisters the callback from the command'''
        self._command.Remove(self._decorator_instance._command_called)
