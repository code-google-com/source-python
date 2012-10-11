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
from core.base_command import SPCommands
#   Events
from events.manager import EventRegistry
#   Listeners
from listeners.tick import TickListeners


# =============================================================================
# >> CORE FUNCTIONS
# =============================================================================
def event_fire(GameEvent):
    '''Called when the core catches an event.'''

    # Call the event within the registry
    EventRegistry.call_event_callbacks(GameEvent)


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
