# ../_libs/addons/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Sys
import sys
from traceback import format_exception

# Source.Python Imports
from paths import ADDON_PATH
#   Addons
from addons.errors import AddonFileNotFoundError
#   Core
from core import AutoUnload
from core.commands import echo_console
from core.excepthook import ExceptHooks
#   Events
from events.manager import EventRegistry


# =============================================================================
# >> MAIN CLASSES
# =============================================================================
class _AddonManagementDictionary(dict):
    '''Stores addon's and their instances'''

    _order = list()

    def __missing__(self, addon_name):
        '''Tries to load an addon that is not loaded'''

        # Try to get the addon's instance
        try:

            # Get the addon's instance
            instance = _LoadedAddon(addon_name)

        # Was the file not found?
        # We use this check because we already printed the error to console
        except AddonFileNotFoundError:

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
                echo_console(
                    '[SP] Addon name cannot use name of a built-in module')

            # Otherwise
            else:

                # Print the exception to the console
                ExceptHooks.print_exception(*error)

                # Remove all modules from sys.modules
                self._remove_modules(addon_name)

            # Return None as the value to show the addon was not loaded
            return None

        # Add the addon to the dictionary with its instance
        self[addon_name] = instance

        # Add the addon's name to the ordered list
        self._order.append(addon_name)

        # Return the given value
        return instance

    def __delitem__(self, addon_name):
        '''Removes an addon from the manager'''

        # Is the addon in the dictionary?
        if not addon_name in self:

            # Is the addon loaded?
            return

        # Print message about unloading the addon
        echo_console('[SP] Unloading "%s"...' % addon_name)

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
                ExceptHooks.print_exception(*error)

        # Remove all modules from sys.modules
        self._remove_modules(addon_name)

        # Remove the addon from the ordered list
        self._order.remove(addon_name)

        # Remove the addon from the dictionary
        super(_AddonManagementDictionary, self).__delitem__(addon_name)

    def __iter__(self):
        '''Override the __iter__ method to return
            items in the order they were loaded'''

        # Loop through all items in the ordered list
        for addon in self._order:

            # Yield the current item
            yield addon

    def _remove_modules(self, addon_name):

        # Get the addon's module
        addon_import = addon_name + '.' + addon_name

        # Is the addon's module loaded?
        if not addon_import in sys.modules:

            # If not, simply return
            return

        # Get the addon's instance
        addon = __import__(addon_import)

        # Remove all instances of AutoUnload classes from the addon
        self._unload_instances(addon, addon_name)

        # Loop through all loaded modules
        for module in list(sys.modules):

            # Is the current module part of the given addon?
            if module.startswith(addon_name):

                # Remove the module from memory
                del sys.modules[module]

    def _unload_instances(self, instance, module):
        '''Removes all AutoUnload instances from the registry for the addon'''

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

            # Is the item an "AutoUnload" instance?
            if isinstance(new_instance, AutoUnload):

                # Unregister the instance
                new_instance._unload_instance()

            # Does the module exist in sys.modules?
            elif new_module in sys.modules:

                # Loop through all items in the module
                self._unload_instances(new_instance, new_module)

# Get the _AddonManagementDictionary instance
AddonManager = _AddonManagementDictionary()


class _LoadedAddon(object):
    '''Stores an addon's instance'''

    def __init__(self, addon_name):
        '''Called when an addon's instance is initialized'''

        # Print message that the addon is going to be loaded
        echo_console('[SP] Loading "%s"...' % addon_name)

        # Get the addon's main file
        file_path = ADDON_PATH.join(addon_name, addon_name + '.py')

        # Does the addon's main file exist?
        if not file_path.isfile():

            # Print a message that the addon's main file was not found
            echo_console(
                '[SP] Unable to load "%s", missing file ' % addon_name +
                '../addons/source-python/%s/%s.py' % (addon_name, addon_name))

            # Raise an error, so that the addon
            # is not added to the AddonManager
            raise AddonFileNotFoundError

        # Import the addon
        addon = __import__(addon_name + '.' + addon_name)

        # Store the globals for the addon
        self.globals = addon.__dict__[addon_name].__dict__

        # Does the addon have a load function?
        if 'load' in self.globals:

            # Call the addon's load function
            self.globals['load']()
