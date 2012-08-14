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
from core.decorators import BaseDecorator
from core.excepthook import ExceptHooks
#   Events
from events.manager import EventRegistry


# =============================================================================
# >> CLASSES
# =============================================================================
class _AddonManagementDictionary(dict):
    '''Stores addon's and their instances'''

    def __missing__(self, addon_name):
        '''Tries to load an addon that is not loaded'''

        # Try to get the addon's instance
        try:

            # Get the addon's instance
            instance = _LoadedAddon(addon_name)

        # Was the file not found?
        # We use this check because we already printed the error to console
        except FileNotFoundError:

            # Return None as the value to show the addon was not loaded
            return None

        # Was a different error was encountered?
        except:

            # Get the error
            error = sys.exc_info()

            # Is the error due to "No module named '<addon>.<addon>'?
            if (len(error[1].args) and error[1].args[0] ==
              "No module named '%s.%s'" % (addon_name, addon_name)):

                # Print a message about not using built-in module names
                # We already know the path exists, so the only way this error
                # could occur is if it shares its name with a built-in module
                print('[SP] Addon name cannot use name of a built-in module')

            # Otherwise
            else:

                # Print the exception to the console
                ExceptHooks.PrintException(*error)

                # Remove all modules from sys.modules
                self._RemoveModules(addon_name)

            # Return None as the value to show the addon was not loaded
            return None

        # Add the addon to the dictionary with its instance
        self[addon_name] = instance

        # Return the given value
        return instance

    def __delitem__(self, addon_name):
        '''Removes an addon from the manager'''

        # Is the addon in the dictionary?
        if not addon_name in self:

            # Is the addon loaded?
            return

        # Print message about unloading the addon
        print('[SP] Unloading "%s"...' % addon_name)

        # Does the addon have an unload function?
        if 'unload' in self[addon_name].globals:

            # Use a try/except here to still allow the addon to be unloaded
            try:

                # Call the addon's unload function
                self[addon_name].globals['unload']()

            # Was an exception raised?
            except:

                # Get the error
                error = sys.exc_info()

                # Print the error to console, but
                # allow the addon to still be unloaded
                ExceptHooks.PrintException(*error)

        # Remove all modules from sys.modules
        self._RemoveModules(addon_name)

        # Remove the addon from the dictionary
        super(_AddonManagementDictionary, self).__delitem__(addon_name)

    def _RemoveModules(self, addon_name):

        # Get the addon's module
        addon_import = addon_name + '.' + addon_name

        # Is the addon's module loaded?
        if not addon_import in sys.modules:

            # If not, simply return
            return

        # Get the addon's instance
        addon = __import__(addon_import)

        # Remove all events from the addon
        self._RemoveDecorators(addon, addon_name)

        # Loop through all loaded modules
        for module in list(sys.modules):

            # Is the current module part of the given addon?
            if module.startswith(addon_name):

                # Remove the module from memory
                del sys.modules[module]

    def _RemoveDecorators(self, instance, module):
        '''
            Removes all BaseDecorator instances from the registry for the addon
        '''

        # Does the current object have a __dict__?
        if not hasattr(instance, '__dict__'):

            # If not, simply return
            return

        # Loop through all items in the instance's dictionary
        for item in dict(instance.__dict__):

            # Get the new object's instance
            new_instance = instance.__dict__[item]

            # Get the object's module
            new_module = module + '.' + item

            # Is the item an "BaseDecorator" instance?
            if isinstance(new_instance, BaseDecorator):

                # Unregister the Decorator
                new_instance._UnregisterDecorator()

            # Does the module exist in sys.modules?
            elif new_module in sys.modules:

                # Loop through all items in the module
                self._RemoveDecorators(new_instance, new_module)

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

        # Does the addon have a load function?
        if 'load' in self.globals:

            # Call the addon's load function
            self.globals['load']()
