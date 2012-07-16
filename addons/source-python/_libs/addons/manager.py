# ../_libs/addons/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   OS
from os.path import isfile
#   Sys
import sys
from traceback import format_exception

# Source.Python Imports
from paths import ADDON_PATH
#   Core
from core.excepthook import ExceptHooks
#   Events
from events.decorator import event


# =============================================================================
# >> CLASSES
# =============================================================================
class _AddonManagementDictionary(dict):
    '''Stores addon's and their instances'''

    def __getitem__(self, addon):
        '''Returns an addon's instance and tries to
            load it if it is not already loaded'''

        # Does the addon already exist in the dictionary?
        if addon in self:

            # Return the addon's instance
            return super(_AddonManagementDictionary, self).__getitem__(addon)

        # Try to get the addon's instance
        try:

            # Get the addon's instance
            value = _LoadedAddon(addon)

        # Was the file not found?
        # We use this check because we already printed the error to console
        except FileNotFoundError:

            # Return None as the value to show the addon was not loaded
            return None

        # Was a different error was encountered?
        except:

            # Get the error
            error = sys.exc_info()

            # Print the exception to the console
            ExceptHooks.PrintException(*error)

            # Return None as the value to show the addon was not loaded
            return None

        # Add the addon to the dictionary with its instance
        self[addon] = value

        # Return the given value
        return value

    def __delitem__(self, addon_name):
        '''Removes an addon from the manager'''

        # Is the addon in the dictionary?
        if not addon_name in self:

            # Is the addon loaded?
            return

        # Print message about unloading the addon
        print('[SP] Unloading "%s"...' % addon_name)

        # Get the addon's module
        addon_import = addon_name + '.' + addon_name

        # Is the addon's module loaded?
        if addon_import in sys.modules:

            # Get the addon's instance
            addon = __import__(addon_import)

            # Remove all events from the addon
            self[addon_name]._RemoveEvents(addon, addon_name)

            # Loop through all loaded modules
            for module in list(sys.modules):

                # Is the current module part of the given addon?
                if module.startswith(addon_name):

                    # Remove the module from memory
                    del sys.modules[module]

        # Remove the addon from the dictionary
        super(_AddonManagementDictionary, self).__delitem__(addon_name)

# Get the _AddonManagementDictionary instance
AddonManager = _AddonManagementDictionary()


class _LoadedAddon(object):
    '''Stores an addon's instance'''

    def __init__(self, addon_name):
        '''Called when an addon's instance is initialized'''

        # Print message that the addon is going to be loaded
        print('[SP] Loading "%s"...' % addon_name)

        # Get the addon's main file
        file_path = '%s/%s/%s.py' % (ADDON_PATH, addon_name, addon_name)

        # Does the addon's main file exist?
        if not isfile(file_path):

            # Print a message that the addon's main file was not found
            print(
                '[SP] Unable to load "%s", missing file ' % addon_name +
                '../addons/source-python/%s/%s.py' % (addon_name, addon_name))

            # Raise an error, so that the addon
            # is not added to the AddonManager
            raise FileNotFoundError

        # Import the addon
        addon = __import__(addon_name + '.' + addon_name)

        # Store the globals for the addon
        self.globals = addon.__dict__[addon_name].__dict__

    def _RemoveEvents(self, instance, module):
        '''Removes all events from the registry for the addon'''

        # Does the current object have a __dict__?
        if not hasattr(instance, '__dict__'):

            # If not, simply return
            return

        # Loop through all items in the instance's dictionary
        for item in dict(instance.__dict__):

            # Get the object's module
            new_module = module + '.' + item

            # Does the module exist in sys.modules?
            if new_module in sys.modules:

                # Loop through all items in the module
                self._RemoveEvents(instance.__dict__[item], new_module)

            # Is the item's instance an "event" instance?
            elif isinstance(instance.__dict__[item], event):

                # Remove the object from memory
                # This will also remove the object from the EventRegistry
                del instance.__dict__[item]
