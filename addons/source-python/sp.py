# ../sp.py

'''
    ===========================================================================
    Source Python
    Copyright (C) 2012 Source Python Development Team.  All rights reserved.
    ===========================================================================

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License, version 3.0, as
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along
    with this program.  If not, see <http://www.gnu.org/licenses/>.

    As a special exception, the Source.Python Team gives you permission
    to link the code of this program (as well as its derivative works) to
    "Half-Life 2," the "Source Engine," and any Game MODs that run on software
    by the Valve Corporation.  You must obey the GNU General Public License in
    all respects for all other code used.  Additionally, the Source.Python
    Development Team grants this exception to all derivative works.
'''

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Addons
from addons.info import AddonInfo
from addons.manager import AddonManager
#   Events
from events.manager import EventRegistry
#   Listeners
from listeners.tick import TickListeners
#   Game Engine
from core import GameEngine


# =============================================================================
# >> CORE FUNCTIONS
# =============================================================================
def event_fire(GameEvent):
    '''Called when the core catches an event.'''

    # Call the event within the registry
    EventRegistry.CallEventCallbacks(GameEvent)


def tick_listener():
    '''Called every tick'''

    # Call all tick listeners
    TickListeners.CallTickListeners()


# =============================================================================
# >> ADDON RELATED FUNCTIONS
# =============================================================================
def addon_load(addon_name):
    '''Called when a user executes sp load.'''

    # Is the addon already loaded?
    if addon_name in AddonManager:

        # Echo message that the addon is already loaded
        sp_echo('Addon "%s" is already loaded.' % addon_name)

        # No need to go further
        return

    # Get the addon's instance
    addon = AddonManager[addon_name]

    # Is the addon loaded?
    if addon is None:

        # Echo a message that the addon was not able to be loaded
        sp_echo('Addon "%s" was unable to be loaded.' % addon_name)

        # If not, go no further
        return

    # Echo message that the addon successfully loaded
    sp_echo('Successfully loaded "%s"' % addon_name)


def addon_unload(addon_name):
    '''Called when a user executes sp unload.'''

    # Is the loaded?
    if not addon_name in AddonManager:

        # Echo message that the addon is not loaded
        sp_echo('Addon "%s" cannot ' % addon_name +
                'be unloaded.  It is not currently loaded.')

        # No need to go further
        return

    # Get the addon's instance
    addon = AddonManager[addon_name]

    # Remove the addon from the AddonManager
    del AddonManager[addon_name]

    # Echo message that the addon successfully unloaded
    sp_echo('Successfully unloaded "%s"' % addon_name)


def addon_reload(addon_name):
    '''Called when a user executes sp reload.'''

    # Unload the addon
    addon_unload(addon_name)

    # Load the addon
    addon_load(addon_name)


# =============================================================================
# >> SP CONSOLE COMMAND & RELATED FUNCTIONS
# =============================================================================
def sp_command(arg_string):
    '''Called when a user executes sp'''

    # Use try to split, in case there is nothing to split
    try:

        # Get the arguments and the command
        command, arguments = arg_string.split(maxsplit=1)

    # Was an exception raise?
    except:

        # Set the commands as the text, since there
        # are either 1 or 0 arguments in the string
        command = arg_string.strip()

        # Set the arguments to an empty string
        arguments = ''

    # Get the arguments as a list
    arguments = arguments.split()

    # Make the command lower-case for comparison
    command = command.lower()

    # Is the first argument "load"
    if command == 'load':

        # Load addon
        if arguments:
            addon_load(arguments)

        # No arguments supplied
        else:

            # Error message
            sp_echo('Usage: sp load <addon>')
            sp_echo('Please specify a valid ' +
                    'addon name to be loaded, or type "sp help"')

    # Is the first argument "unload"
    elif command == 'unload':

        # Unload addon
        if arguments:
            addon_unload(arguments)

        # No arguments supplied
        else:

            # Error message
            sp_echo('Usage: sp unload <addon>')
            sp_echo('Please specify a valid ' +
                    'addon name to be unloaded, or type "sp help"')

    # Is the first argument "reload"
    elif command == 'reload':

        # Reload addon
        if arguments:
            addon_reload(arguments)

        # No arguments supplied
        else:

            # Error message
            sp_echo('Usage: sp reload <addon>')
            sp_echo('Please specify a valid ' +
                    'addon name to be reloaded, or type "sp help"')

    # Is the first argument "print" or "list"
    elif command in ('list', 'print'):

        # Echo the addon list
        sp_list()

    # Is the first argument "version"
    elif command == 'version':

        # Echo version information
        sp_version()

    elif command == 'credits':

        # Echo credits
        sp_credits()

    # Catch-all (help)
    else:

        # Display error if not help
        if command not in ('help', ''):

            # Echo error
            sp_echo('"%s" is not a valid command.' % command)
            sp_echo('')

        # Echo help
        sp_help()


def sp_credits():
    '''Display SP project contribors'''

    # Header
    sp_echo_header('Source.Python Credits')

    # Project Leaders
    sp_echo('Project Leaders:')
    sp_echo('\tAshley Muncaster\t[ashbash1987]')
    sp_echo('\tDeniz Sezen\t[your-name-here]')
    sp_echo('\tLuke Robinson\t[Monday]')
    sp_echo('\tStephen Toon\t[satoon101]')

    # Contributors
    sp_echo('Contributors:')
    sp_echo('\tComming soon...')

    # Special thanks
    sp_echo('Special Thanks:')
    sp_echo('\tComming soon...')


def sp_version():
    '''Display version information'''

    # Header
    sp_echo_header('Source.Python')

    # Base version
    sp_echo('Version: %s' % 'Someday, important information will be here.')

    # Core version
    sp_echo('\tSP Core Version: %s' % 'A billion internets.')

    # Library version
    sp_echo('\tSP Library Version: %s' % "We're bringing sexy back.")


def sp_help():
    '''Displays sp commands, and offers help on each command'''

    # Echo header
    sp_echo_header('Source.Python Command Help')

    # Echo help body
    sp_echo('sp load <addon> \t"Loads an addon by name."')
    sp_echo('sp unload <addon> \t"Unloads an addon by name."')
    sp_echo('sp reload <addon> \t"Reloads an addon by name."')
    sp_echo('sp list \t\t"Lists all currently loaded addons."')
    sp_echo('sp credits \t\t"Lists the names of the developers."')
    sp_echo('sp version \t\t"Displays Source.Python version information."')
    sp_echo('sp help \t\t"Looks like you figured this one out."')
    sp_echo('\n\n')


def sp_echo(string):
    '''Calls the server command "echo" with a SP prefix'''
    GameEngine.ServerCommand('echo "# [SP] >>  %s"\n' % string)


def sp_echo_header(string):
    '''Calls the server command "echo" with a SP prefix'''

    # Print line
    GameEngine.ServerCommand('echo "# [SP] >> ' + '=' * 40 + '"\n')

    # Print header title
    GameEngine.ServerCommand('echo "# [SP] >> \t%s"\n' % string)

    # Print line
    GameEngine.ServerCommand('echo "# [SP] >> ' + '=' * 40 + '"\n')

    # Print blank line
    GameEngine.ServerCommand('echo "# [SP] >>"\n')


def sp_list():
    '''Displays a list of currently loaded addons'''

    # Display header
    sp_echo_header('Source.Python Running Addons')

    # No addons are loaded?
    if len(AddonManager) == 0:

        # Echo no addons message
        sp_echo('No addons are currently loaded!')
        sp_echo('')
        return

    # Loop through all loaded addons
    for addon in AddonManager:

        # Set info as None in case no AddonInfo instance is found
        info = None

        # Loop through the addon's globals
        for object_name in AddonManager[addon].globals:

            # Get the object's instance
            instance = AddonManager[addon].globals[object_name]

            # Is the current instance an AddonInfo instance?
            if isinstance(instance, AddonInfo):

                # Set info to the instance
                info = instance

                # Break the loop
                break

        # Does the addon have an AddonInfo instance?
        if not info is None:

            # Echo the addon's name
            sp_echo(addon + ':')

            # Loop through all items in the AddonInfo instance
            for item in info:

                # Echo the item's name
                sp_echo('\t%s:' % item)

                # Echo the item's value
                sp_echo('\t\t%s' % info[item])

        # Does the addon not have an AddonInfo instance?
        else:

            # Echo the addon's name
            sp_echo(addon)

        # Echo a blank line between addons
        sp_echo('')

    # Echo closing message for loaded addons
    sp_echo('=' * 40)
