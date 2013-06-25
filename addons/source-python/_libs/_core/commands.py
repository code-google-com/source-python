# ../_libs/_core/commands.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Collections
from collections import OrderedDict

# Site Package Imports
#   Configobj
from configobj import ConfigObj

# Source.Python Imports
from _core import _CoreLogger
from command_c import get_server_command
from paths import DATA_PATH
#   Addons
from addons.info import AddonInfo
from addons.manager import AddonManager
from addons.manager import AddonManagerLogger
#   Auth
from auth.commands import AuthCommands
#   Translations
from translations.strings import LangStrings


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the core commands language strings
_command_strings = LangStrings('_core/core_commands_strings')

SPCommandsLogger = _CoreLogger.commands


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

                # Get a message about the invalid command
                message = '[SP] ' + _command_strings[
                    'Invalid Command'].get_string(command=command)

            # Was no command given?
            else:

                # Get a message that a sub-command is needed
                message = '[SP] ' + _command_strings[
                    'No Command'].get_string()

            # Print the help text
            self._print_help(message)

            # Go no further
            return

        # Does the given command have required arguments?
        if hasattr(self[command], 'args'):

            # Were the correct number of arguments given?
            if len(args) != len(self[command].args):

                # Send a message about the sub-command's valid arguments
                SPCommandsLogger.message(
                    '[SP] ' + _command_strings['Invalid Arguments'].get_string(
                        command=command) + ' '.join(self[command].args))

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

    def _print_help(self, message=''):
        '''Prints all "sp" sub-commands.'''

        # Add header messages
        message += '\n[SP] ' + _command_strings[
            'Help'].get_string() + 'sp <command> [arguments]\n' + '=' * 76

        # Loop through all registered sub-commands
        for item in self:

            # Set the text
            text = str(item)

            # Does the current item have its own _print_help method?
            if hasattr(self[item], '_print_help'):

                # Get the instance's help text
                message += '\n' + self[item]._get_help_text()

                # Continue onto the next item
                continue

            # Does the current command have required arguments?
            if hasattr(self[item], 'args'):

                # Add the arguments to the text
                text += ' ' + ' '.join(self[item].args)

            # Add a message for the current command
            message += '\n' + text + self[
                item].__doc__.rjust(76 - len(text))

        # Send ending message
        SPCommandsLogger.message(message + '\n' + '=' * 76)

# Get the _SPCommands instance
SPCommands = _SPCommands()


# =============================================================================
# >> MAIN FUNCTION
# =============================================================================
def _sp_command_callback(CICommand):
    '''Called when the sp command is executed on the server'''

    # Get the argument string
    arg_string = CICommand.get_arg_string()

    # Use try to split, in case there is nothing to split
    try:

        # Get the arguments and the command
        command, args = arg_string.split(maxsplit=1)

    # Was an exception raised?
    except:

        # Set the command as the text, since there
        # are either 1 or 0 arguments in the string
        command = arg_string.strip()

        # Set the arguments to an empty string
        args = ''

    # Get the arguments as a list
    args = args.split()

    # Make the command lower-case for comparison
    command = command.lower()

    # execute the called command
    SPCommands.call_command(command, args)

# Register the "sp" command
_sp_command = get_server_command('sp', 'Source.Python base command.', 0)
_sp_command.add_callback(_sp_command_callback)


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def _load_addon(addon_name):
    '''Loads an addon by name.'''

    # Is the addon already loaded?
    if addon_name in AddonManager:

        # Send message that the addon is loaded
        AddonManagerLogger.message('[SP] ' + _command_strings[
            'Already Loaded'].get_string(addon=addon_name))

        # No need to go further
        return

    # Load the addon and get its instance
    addon = AddonManager[addon_name]

    # Was the addon loaded?
    if addon is None:

        # Send message that the addon was not loaded
        AddonManagerLogger.message('[SP] ' + _command_strings[
            'Unable to Load'].get_string(addon=addon_name))

        # No need to go further
        return

    # Send message that the addon was loaded
    AddonManagerLogger.message('[SP] ' + _command_strings[
        'Successful Load'].get_string(addon=addon_name))


def _unload_addon(addon_name):
    '''Unloads an addon by name.'''

    # Is the addon loaded?
    if not addon_name in AddonManager:

        # If not, send a message that the addon is not loaded
        AddonManagerLogger.message('[SP] ' + _command_strings[
            'Not Loaded'].get_string(addon=addon_name))

        # No need to go further
        return

    # Unload the addon
    del AddonManager[addon_name]

    # Send message that the addon was unloaded
    AddonManagerLogger.message('[SP] ' + _command_strings[
        'Successful Unload'].get_string(addon=addon_name))


def _reload_addon(addon_name):
    '''Reloads an addon by name.'''

    # Unload the addon
    _unload_addon(addon_name)

    # Load the addon
    _load_addon(addon_name)


def _print_addons():
    '''Lists all currently loaded addons.'''

    # Get header messages
    message = '[SP] ' + _command_strings[
        'Addons'].get_string() + '=' * 61 + '\n\n'

    # Loop through all loaded addons
    for addon in AddonManager:

        # Set info to None before retrieving it
        info = None

        # Loop through all global objects in the addon
        for object_name in AddonManager[addon]._globals:

            # Get the current object's instance
            instance = AddonManager[addon]._globals[object_name]

            # Is the current object an AddonInfo instance?
            if isinstance(instance, AddonInfo):

                # Set info to the current instance
                info = instance

                # No need to continue the loop
                break

        # Was an AddonInfo instance found?
        if not info is None:

            # Add message with the current addon's name
            message += addon + ':\n'

            # Loop through all items in the AddonInfo instance
            for item in info:

                # Add message for the current item and its value
                message += '\t%s\n\t\t%s\n' % (item, info[item])

        # Was no AddonInfo instance found?
        else:

            # Add message with the current addon's name
            message += addon + '\n'

        # Add 1 blank line between each addon
        message += '\n'

    # Print the message
    SPCommandsLogger.message(message + '=' * 61)


def _print_version():
    '''Displays Source.Python version information.'''


def _print_credits():
    '''Lists all credits for Source.Python.'''

    # Get header messages
    message = '[SP] ' + _command_strings[
        'Credits'].get_string() + '=' * 61 + '\n\n'

    # Get the credits information
    groups = ConfigObj(
        DATA_PATH.joinpath('credits.ini'), encoding='unicode_escape')

    # Loop through all groups in the credits
    for group in groups:

        # Add the current group's name
        message += '\t' + group + ':\n'

        # Loop through all names in the current group
        for name in groups[group]:

            # Add the current name
            message += '\t\t' + name + ' ' * (
                20 - len(name)) + groups[group][name] + '\n'

        # Add 1 blank line between groups
        message += '\n'

    # Print the ending message
    SPCommandsLogger.message(message + '=' * 61 + '\n\n')

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
