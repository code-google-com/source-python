# ../_libs/commands/server/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Cvar
#   Commands
from commands.manager import _CommandList
from commands.manager import _CommandRegistry


# =============================================================================
# >> CLASSES
# =============================================================================
class _ServerCommandList(_CommandList):
    '''Class used to store callbacks for a server command'''

    _ContinueValue = Cvar.CommandReturn.CONTINUE
    _BlockValue = Cvar.CommandReturn.BLOCK

    def __init__(self, *args):
        '''Get the command's instance'''
        self._command = Cvar.GetCommand(*args)

    '''
        This section has been added until we can fix
        crashing issues with instance method callbacks
    '''
    @staticmethod
    def _command_called(CCommand):
        command = CCommand[0]
        return ServerCommandRegistry._commands[
            command]._call_command(CCommand)

    def _call_command(self, *args):
        return_val = True
        for callback in self:
            return_type = callback(*args)
            return_val = return_val and (
                return_type is None or bool(return_type))
        if return_val:
            return self._ContinueValue
        return self._BlockValue

    '''
        End of added section
    '''


class _ServerCommandRegistry(_CommandRegistry):
    '''Class used to store server commands and their callbacks'''

    def register_command(self, names, callback, description='', flags=0):
        '''Registers the given command names to the given callback'''

        # Was only one command given?
        if isinstance(names, str):

            # Set the command to a list
            names = [names]

        # Are the commands given of a proper type?
        if not type(names) in (list, tuple):

            # If not, raise an error
            raise TypeError(
                '%s commands must be passed as a ' % type(self).__name__ +
                'list, tuple, or string, not "%s"' % type(names).__name__)

        # Loop through all given names
        for name in names:

            # Is the current name in the dictionary?
            if not name in self._commands:

                # Add the command name to the dictionary
                self._commands[name] = _ServerCommandList(
                                    name, description, flags)

            # Add the callback to the command's list
            self._commands[name].append(callback)

    def unregister_command(self, names, callback):
        '''Unregisters the given command names from the given callback'''

        # Was only one command given?
        if isinstance(names, str):

            # Set the command to a list
            names = [names]

        # Are the commands given of a proper type?
        if not type(names) in (list, tuple):

            # If not, raise an error
            raise TypeError(
                '%s commands must be passed as a ' % type(self).__name__ +
                'list, tuple, or string, not "%s"' % type(names).__name__)

        # Loop through all given names
        for name in names:

            # Is the current command in the dictionary?
            if not name in self._commands:

                # If not, no need to unregister
                continue

            # Is the callback in the command's list?
            if callback in self._commands[name]:

                # Remove the callback from the list
                self._commands[name].remove(callback)

# Get the _ServerCommandRegistry instance
ServerCommandRegistry = _ServerCommandRegistry()
