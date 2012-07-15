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


# =============================================================================
# >> CORE FUNCTIONS
# =============================================================================
def addon_load(addon_name):
    '''Called when a user executes sp_load.'''

    # Is an addon being loaded?
    if not addon_name:

        # Print start message for loaded addons
        print('[SP] Loaded Addons:')
        print('======================================\n')

        # Loop through all loaded addons
        for addon in AddonManager:

            # Print a message about the loaded addon
            print(addon + ':')

            # Loop through the addon's globals
            for object_name in AddonManager[addon].globals:

                # Get the object's instance
                instance = AddonManager[addon].globals[object_name]

                # Is the current instance an AddonInfo instance?
                if not isinstance(instance, AddonInfo):

                    # If not, continue the loop
                    continue

                # Loop through all items in the AddonInfo instance
                for item in instance:

                    # Print the item's name
                    print('\t%s:' % item)

                    # Print the item's value
                    print('\t\t%s' % instance[item])

            # Print a blank line between addons
            print('\n')

        # Print closing message for loaded addons
        print('======================================')

        # No need to go further
        return

    # Is the addon already loaded?
    if addon_name in AddonManager:

        # Print message that the addon is already loaded
        print('[SP] Addon "%s" is already loaded.' % addon_name)

        # No need to go further
        return

    # Get the addon's instance
    addon = AddonManager[addon_name]

    # Is the addon loaded?
    if addon is None:

        # If not, go no further
        return

    # Does the addon have a load function?
    if 'load' in addon.globals:

        # Call the addon's load function
        addon.globals['load']()


def addon_unload(addon_name):
    '''Called when a user executes sp_unload.'''

    # Is the loaded?
    if not addon_name in AddonManager:

        # Print message that the addon is not loaded
        print('[SP] Addon "%s" cannot ' % addon_name +
            'be unloaded.  It is not currently loaded.')

        # No need to go further
        return

    # Get the addon's instance
    addon = AddonManager[addon_name]

    # Does the addon have an unload function?
    if 'unload' in addon.globals:

        # Call the addon's unload function
        addon.globals['unload']()

    # Remove the addon from the AddonManager
    del AddonManager[addon_name]


def addon_reload(addon_name):
    '''Called when a user executes sp_reload.'''

    # Unload the addon
    addon_unload(addon_name)

    # Load the addon
    addon_load(addon_name)


def event_fire(game_event):
    '''Called when the core catches an event.'''

    # Call the event within the registry
    EventRegistry.call_event_callbacks(game_event)
