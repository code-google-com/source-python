# ../_libs/commands/say/command.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Commands
from commands.base import CommandRegistration


# =============================================================================
# >> CLASSES
# =============================================================================
class SayCommand(CommandRegistration):
    '''Class used to register say commands using a decorator'''

    def __init__(self, *names):
        '''Stores the name of the command'''

        # Store the list of command names
        self.names = names

    def _register_command(self, name):
        '''Registers the commands with the instance's
            callback and returns its instance'''

        return SayCommandDictionary[name]

    def _command_called(self, index, teamonly, CCommand):
        '''Call the stored callback with the given arguments'''
        return self.callback(index, teamonly, CCommand)


class _SayCommandList(list):
    '''List object that deletes items from the
        dictionary once their list is empty'''

    def __init__(self, item):
        '''Stores the name of the command in order
            to delete it from the dictionary'''
        self.item = item

    def AddToEnd(self, item):
        '''Appends the given item to the end of the list'''
        self.append(item)

    def Remove(self, item):
        '''Removes the item from the list'''
        self.remove(item)

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
