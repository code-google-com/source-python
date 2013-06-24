# ../_libs/commands/command.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from core import AutoUnload


# =============================================================================
# >> CLASSES
# =============================================================================
class _BaseCommand(AutoUnload):
    '''Base decorator class used to register commands'''

    def __init__(self, names, *args):
        '''Stores the base values for the decorator'''

        # Store the names
        self.names = names

        # Store the arguments
        self.args = args

    def __call__(self, callback):
        '''Registers the commands to the given callback'''

        # Store the callback
        self.callback = callback

        # Register the commands
        self._ManagerClass.register_commands(
            self.names, self.callback, *self.args)

    def _unload_instance(self):
        '''Unregisters the commands'''
        self._ManagerClass.unregister_commands(self.names, self.callback)
