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

        # Get the decorator instance
        self._decorator_instance = _CommandDecorator(self)

        # Create an empty list to store Cvar instances
        self.instances = list()

        # Loop through all command names
        for name in self.names:

            # Register the command
            instance = self._register_command(name)

            # Add the callback to the command's callback list
            instance.AddToEnd(self._decorator_instance._command_called)

            # Add the instance to the list of instances
            self.instances.append(instance)

        # Return the decorator instance of this class
        return self._decorator_instance

    def _unregister_command(self):
        '''Unregisters the instance from the commands'''

        # Loop through all command instances
        for instance in self.instances:

            # Remove the instance from the command's callbacks
            instance.Remove(self._decorator_instance._command_called)
