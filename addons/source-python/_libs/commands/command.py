# ../_libs/commands/command.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import AutoUnload


# =============================================================================
# >> CLASSES
# =============================================================================
class _CommandAutoUnload(AutoUnload):
    '''Class used to auto-unregister commands on script unload'''

    def __init__(self, class_instance):
        '''Stores the instantiating class' unregister method'''
        self._unload_instance = class_instance._unregister_command


class _CommandRegistration(object):
    '''Base command registration class'''

    def __call__(self, callback):
        '''Registers the command to the given callback'''

        # Store the callback
        self.callback = callback

        # Get the auto unload instance
        self._autounload_instance = _CommandAutoUnload(self)

        self._RegistrationClass.register_command(
            self.names, self.callback, *self.args)

        # Return the decorator instance of this class
        return self._autounload_instance

    def _unregister_command(self):
        '''Unregisters the instance from the commands'''
        self._RegistrationClass.unregister_command(self.names, self.callback)


class _PlayerCommandRegistration(_CommandRegistration):
    '''Base Player command registration class'''

    def __init__(
        self, names, level=None, permission=None,
            flag=None, fail_callback=None):
        '''Stores the given arguments'''
        self.names = names
        self.args = (level, permission, flag, fail_callback)
