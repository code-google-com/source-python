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
#   Core
from _core.commands import SPCommands
from _core.settings import CoreSettings
#   Translations
from translations.manager import LanguageManager
#   Tick
from tick.listeners import TickListeners


# =============================================================================
# >> CORE FUNCTIONS
# =============================================================================
def plugin_load():
    '''Called when the plugin is finished loading'''

    # Get the auth providers that should be loaded
    auth_providers = CoreSettings['AUTH_SETTINGS']['providers'].split()

    # Should any providers be loaded?
    if auth_providers:

        # Load the auth providers
        SPCommands.call_command('auth', ['load'] + auth_providers)

    # Set the default language
    LanguageManager._register_default_language(
        CoreSettings['BASE_SETTINGS']['language'])


def tick_listener():
    '''Called every tick'''

    # Call all tick listeners
    TickListeners.call_tick_listeners()


# =============================================================================
# >> SP CONSOLE COMMAND FUNCTIONS
# =============================================================================
def sp_command(arg_string):
    '''Called when a user executes sp'''

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
