# ../_libs/core/base_command.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Collections
from collections import OrderedDict
#   Configobj
from configobj import ConfigObj

# Source.Python Imports
from paths import DATA_PATH
#   Addons
from addons.info import AddonInfo
from addons.manager import AddonManager
#   Auth
from auth.commands import AuthCommands
#   Core
from core.commands import echo_console


# =============================================================================
# >> CLASSES
# =============================================================================
class _SPCommands(OrderedDict):
    '''Class used for executing "sp" sub-command functionality'''

    def call_command(self, command, args):
        '''Executes the given "sp" sub-command'''

        # Is the command registered?
        if not command in self:

            # Was a command given?
            if command:

                # Send a message about the invalid command
                echo_console('[SP] "%s" is not a valid sub-command.' % command)

            # Was no command given?
            else:

                # Send a message that a sub-command is needed
                echo_console(
                    '[SP] The "sp" command must be followed by a sub-command.')

            # Print the help text
            self._print_help()

            # Go no further
            return

        # Does the given command have required arguments?
        if hasattr(self[command], 'args'):

            # Were the correct number of arguments given?
            if len(args) != len(self[command].args):

                # Send a message about the sub-command's valid arguments
                echo_console(
                    '[SP] Invalid arguments for sub-command "%s' % command +
                    '": sp %s %s' % (command, ' '.join(self[command].args)))

                # Go no further
                return

            # Execute the command with the given arguments
            self[command](*args)

            # Go no further
            return

        # Does the current item have its own call_command method?
        if hasattr(self[command], 'call_command'):

            # Call the instance's call_command method
            self[command].call_command(args)

            # Go no further
            return

        # Execute the command
        self[command]()

    def _print_help(self):
        '''Prints all "sp" sub-commands.'''

        # Send header messages
        echo_console('[Source.Python] Help:')
        echo_console('usage: sp <command> [arguments]')
        echo_console('=' * 76)

        # Loop through all registered sub-commands
        for item in self:

            # Set the text
            text = str(item)

            # Does the current item have its own _print_help method?
            if hasattr(self[item], '_print_help'):

                # Call the instance's _print_help method
                self[item]._print_help()

                # Continue onto the next item
                continue

            # Does the current command have required arguments?
            if hasattr(self[item], 'args'):

                # Add the arguments to the text
                text += ' ' + ' '.join(self[item].args)

            # Send a message for the current command
            echo_console(
                '%s %s' % (text, self[item].__doc__.rjust(75 - len(text))))

        # Send ending message
        echo_console('=' * 76)


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def _load_addon(addon_name):
    '''Loads an addon by name.'''

    # Is the addon already loaded?
    if addon_name in AddonManager:

        # Send message that the addon is loaded
        echo_console('[SP] Addon "%s" is already loaded.' % addon_name)

        # No need to go further
        return

    # Load the addon and get its instance
    addon = AddonManager[addon_name]

    # Was the addon loaded?
    if addon is None:

        # Send message that the addon was not loaded
        echo_console('[SP] Addon "%s" was unable to be loaded.' % addon_name)

        # No need to go further
        return

    # Send message that the addon was loaded
    echo_console('[SP] Successfully loaded "%s"' % addon_name)


def _unload_addon(addon_name):
    '''Unloads an addon by name.'''

    # Is the addon loaded?
    if not addon_name in AddonManager:

        # If not, send a message that the addon is not loaded
        echo_console(
            '[SP] Addon "%s" cannot ' % addon_name +
            'be unloaded.  It is not currently loaded.')

        # No need to go further
        return

    # Unload the addon
    del AddonManager[addon_name]

    # Send message that the addon was unloaded
    echo_console('[SP] Successfully unloaded "%s"' % addon_name)


def _reload_addon(addon_name):
    '''Reloads an addon by name.'''

    # Unload the addon
    _unload_addon(addon_name)

    # Load the addon
    _load_addon(addon_name)


def _print_addons():
    '''Lists all currently loaded addons.'''

    # Send header messages
    echo_console('[SP] Loaded Addons:')
    echo_console('=' * 61 + '\n')

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
            echo_console(addon + ':')

            # Loop through all items in the AddonInfo instance
            for item in info:

                # Print message for the current item and its value
                echo_console('\t%s:' % item)
                echo_console('\t\t%s' % info[item])

        # Was no AddonInfo instance found?
        else:

            # Print message with the current addon's name
            echo_console(addon)

        # Print 1 blank line between each addon
        echo_console('\n')

    # Print the ending message
    echo_console('=' * 61)


def _print_version():
    '''Displays Source.Python version information.'''


def _print_credits():
    '''Lists all credits for Source.Python.'''

    # Print header messages
    print('[SP] Credits:')
    print('=' * 61 + '\n')

    # Get the credits information
    groups = ConfigObj(
        DATA_PATH.joinpath('credits.ini'), encoding='unicode_escape')

    # Loop through all groups in the credits
    for group in groups:

        # Print the current group's name
        print('\t' + group + ':')

        # Loop through all names in the current group
        for name in groups[group].values():

            # Print the current name
            print('\t\t' + name.replace('\\t', '\t'))

        # Print 1 blank line between groups
        print('')

    # Print the ending message
    print('=' * 61 + '\n')

# Get the _SPCommands instance
SPCommands = _SPCommands()

# Add addon loading/unloading commands to the dictionary
SPCommands['load'] = _load_addon
SPCommands['load'].args = ['<addon>']
SPCommands['unload'] = _unload_addon
SPCommands['unload'].args = ['<addon>']
SPCommands['reload'] = _reload_addon
SPCommands['reload'].args = ['<addon>']

# Add the auth command to the dictionary
SPCommands['auth'] = AuthCommands

# Add all printing commands to the dictionary
SPCommands['list'] = _print_addons
SPCommands['version'] = _print_version
SPCommands['credits'] = _print_credits
SPCommands['help'] = SPCommands._print_help
