# ../_libs/core/base_command.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Configobj
from configobj import ConfigObj

# Source.Python Imports
from paths import DATA_PATH
#   Addons
from addons.info import AddonInfo
from addons.manager import AddonManager
#   Core
from core.commands import EchoConsole

# =============================================================================
# >> CLASSES
# =============================================================================
class _SPCommands(dict):
    '''Class used for executing "sp" sub-command functionality'''

    def __init__(self):
        '''Called on instanciation'''

        # Create a list to keep the items in order for iteration
        self._order = []

    def __setitem__(self, item, value):
        '''
            Override the __setitem__ method to add the item to the ordered list
        '''

        # Add the item to the ordered list
        self._order.append(item)

        # Add the item to the dictionary
        super(_SPCommands, self).__setitem__(item, value)

    def __iter__(self):
        '''Override the __iter__ method to make sure to use the ordered list'''

        # Loop through the ordered list
        for item in self._order:

            # Yield the current item
            yield item

    def CallCommand(self, command, args):
        '''Executes the given "sp" sub-command'''

        # Is the command registered?
        if not command in self:

            # Was a command given?
            if command:

                # Send a message about the invalid command
                EchoConsole('[SP] "%s" is not a valid sub-command.' % command)

            # Was no command given?
            else:

                # Send a message that a sub-command is needed
                EchoConsole(
                    '[SP] The "sp" command must be followed by a sub-command.')

            # Print the help text
            self._PrintHelp()

            # Go no further
            return

        # Does the given command have required arguments?
        if hasattr(self[command], 'args'):

            # Were the correct number of arguments given?
            if len(args) != len(self[command].args):

                # 
                EchoConsole('[SP] Invalid arguments for sub-command "%s' % command +
                    '": sp %s %s' % (command, ' '.join(self[command].args)))

                # Go no further
                return

            # Execute the command with the given arguments
            self[command](*args)

            # Go no further
            return

        # Execute the command
        self[command]()

    def _PrintHelp(self):
        '''Prints all "sp" sub-commands.'''

        # Send header messages
        EchoConsole('[Source.Python] Help:')
        EchoConsole('usage: sp <command> <arguments>')
        EchoConsole('=' * 61)

        # Loop through all registered sub-commands
        for item in self:

            # Set the text
            text = str(item)

            # Does the current command have required arguments?
            if hasattr(self[item], 'args'):

                # Add the arguments to the text
                text += ' ' + ' '.join(self[item].args)

            # Send a message for the current command
            EchoConsole('%s %s' % (text,
                self[item].__doc__.rjust(60 - len(text))))

        # Send ending message
        EchoConsole('=' * 61)


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def _LoadAddon(addon_name):
    '''Loads an addon by name.'''

    # Is the addon already loaded?
    if addon_name in AddonManager:

        # Send message that the addon is loaded
        EchoConsole('[SP] Addon "%s" is already loaded.' % addon_name)

        # No need to go further
        return

    # Load the addon and get its instance
    addon = AddonManager[addon_name]

    # Was the addon loaded?
    if addon is None:

        # Send message that the addon was not loaded
        EchoConsole('[SP] Addon "%s" was unable to be loaded.' % addon_name)

        # No need to go further
        return

    # Send message that the addon was loaded
    EchoConsole('[SP] Successfully loaded "%s"' % addon_name)


def _UnloadAddon(addon_name):
    '''Unloads an addon by name.'''

    # Is the addon loaded?
    if not addon_name in AddonManager:

        # If not, send a message that the addon is not loaded
        EchoConsole('[SP] Addon "%s" cannot ' % addon_name +
            'be unloaded.  It is not currently loaded.')

    # Unload the addon
    del AddonManager[addon_name]

    # Send message that the addon was unloaded
    EchoConsole('[SP] Successfully unloaded "%s"' % addon_name)


def _ReloadAddon(addon_name):
    '''Reloads an addon by name.'''

    # Unload the addon
    _UnloadAddon(addon_name)

    # Load the addon
    _LoadAddon(addon_name)


def _PrintAddons():
    '''Lists all currently loaded addons.'''

    # Send header messages
    EchoConsole('[SP] Loaded Addons:')
    EchoConsole('=' * 61 + '\n')

    # Loop through all loaded addons
    for addon in AddonManager:

        # Set info to None before retrieving it
        info = None

        # Loop through all global objects in the addon
        for object_name in AddonManager[addon].globals:

            # Get the current object's instance
            instance = AddonManager[addon].globals[object_name]

            # Is the current object an AddonInfo instance?
            if isinstance(instance, AddonInfo):

                # Set info to the current instance
                info = instance

                # No need to continue the loop
                break

        # Was an AddonInfo instance found?
        if not info is None:

            # Print message with the current addon's name
            EchoConsole(addon + ':')

            # Loop through all items in the AddonInfo instance
            for item in info:

                # Print message for the current item and its value
                EchoConsole('\t%s:' % item)
                EchoConsole('\t\t%s' % info[item])

        # Was no AddonInfo instance found?
        else:

            # Print message with the current addon's name
            EchoConsole(addon)

        # Print 1 blank line between each addon
        EchoConsole('\n')

    # Print the ending message
    EchoConsole('=' * 61)


def _PrintVersion():
    '''Displays Source.Python version information.'''


def _PrintCredits():
    '''Lists all credits for Source.Python.'''

    # Print header messages
    EchoConsole('[SP] Credits:')
    EchoConsole('=' * 61 + '\n')

    # Get the credits information
    groups = ConfigObj(DATA_PATH.join('credits.ini'))

    # Loop through all groups in the credits
    for group in groups:

        # Print the current group's name
        EchoConsole('\t' + group + ':')

        # Loop through all names in the current group
        for name in groups[group].values():

            # Print the current name
            EchoConsole('\t\t' + name.replace('\\t', '\t'))

        # Print 1 blank line between groups
        EchoConsole('')

    # Print the ending message
    EchoConsole('=' * 61 + '\n')

# Get the _SPCommands instance
SPCommands = _SPCommands()

# Add addon loading/unloading commands to the dictionary
SPCommands['load'] = _LoadAddon
SPCommands['load'].args = ['<addon>']
SPCommands['unload'] = _UnloadAddon
SPCommands['unload'].args = ['<addon>']
SPCommands['reload'] = _ReloadAddon
SPCommands['reload'].args = ['<addon>']

# Add all printing commands to the dictionary
SPCommands['list'] = _PrintAddons
SPCommands['version'] = _PrintVersion
SPCommands['credits'] = _PrintCredits
SPCommands['help'] = SPCommands._PrintHelp
