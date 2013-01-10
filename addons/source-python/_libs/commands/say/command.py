# ../_libs/commands/say/command.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Commands
from commands.base import _CommandDecorator


# =============================================================================
# >> CLASSES
# =============================================================================
class _SayCommandDecorator(_CommandDecorator):
    '''Decorator class used to register/unregister say commands'''

    def __call__(self, index, teamonly, CCommand):
        '''Calls the registered callback'''
        return self._command_called(index, teamonly, CCommand)

class SayCommand(object):
    '''Class used to register say commands using a decorator'''

    def __init__(self, names):
        '''Stores the name of the command'''

        # Was only one command given?
        if isinstance(names, str):

            # Make the names a list
            names = [names]

        # Are the names an iterable?
        if not isinstance(names, list):

            # Raise an error
            raise TypeError('SayCommand commands must be passed ' +
                'as a list or string, not %s' % type(names).__name__)

        # Store the list of command names
        self.names = names

    def __call__(self, callback):
        '''Registers the command to the given callback'''

        # Store the callback
        self.callback = callback

        # Get the decorator instance so it auto unloads
        self._decorator_instance = _SayCommandDecorator(self)

        # Loop through all command names
        for name in self.names:

            # Add the decorator instance to the stored command's list
            SayCommandDictionary[name].append(self._decorator_instance)

        # Return the decorator instance of this class
        return self._decorator_instance

    def _command_called(self, index, teamonly, CCommand):
        '''Call the stored callback with the given arguments'''
        return self.callback(index, teamonly, CCommand)

    def _unregister_command(self):
        '''Unregister the instance from the commands'''

        # Loop through all command names
        for name in self.names:

            # Remove the instance from the command's callbacks
            SayCommandDictionary[name].remove(self._decorator_instance)


class _SayCommandList(list):
    '''List object that deletes items from the
        dictionary once their list is empty'''

    def __init__(self, item):
        '''Stores the name of the command in order
            to delete it from the dictionary'''
        self.item = item

    def remove(self, instance):
        '''Removes the given instance from the list and delete
            its command from the dictionary if necessary'''

        # Remove the instance from the list
        super(_SayCommandList, self).remove(instance)

        # Are there any instances still in the list?
        if not self:

            # Delete the command from the dictionary
            del SayCommandDictionary[self.item]


class _SayCommandDictionary(dict):
    '''Dictionary that stores say commands with a list of callbacks'''

    def __missing__(self, item):
        '''Sets the given item's value to a list'''

        # Set the item to a list
        value = self[item] = _SayCommandList(item)

        # Return the list
        return value

# Get the _SayCommandDictionary instance
SayCommandDictionary = _SayCommandDictionary()
