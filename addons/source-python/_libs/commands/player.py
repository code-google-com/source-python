# ../_libs/commands/player.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from excepthooks import ExceptHooks
#   Auth
from auth.manager import AuthManager
#   Commands
from commands.manager import _CommandRegistry


# =============================================================================
# >> CLASSES
# =============================================================================
class _PlayerCommandRegistry(_CommandRegistry):
    '''Base Player command registration class'''

    def register_command(
        self, names, callback, level=None,
            permission=None, flag=None, fail_callback=None):
        '''Registers the given command names to the given callback'''

        # Was only one command given?
        if isinstance(names, str):

            # Set the command to a list
            names = [names]

        # Are the commands given of a proper type?
        if not type(names) in (list, tuple):

            # If not, raise an error
            raise TypeError(
                '%s commands must be passed as a ' % type(self).__name__ +
                'list, tuple, or string, not "%s"' % type(names).__name__)

        # Loop through all given names
        for name in names:

            # Is the current name in the dictionary?
            if not name in self._commands:

                # Add the command name to the dictionary
                self._commands[name] = self._CommandListClass(name)

            # Get the callback for authorization checking
            auth_instance = self._AuthCallbackClass(
                callback, level, permission, flag, fail_callback)

            # Add the authorization callback to the command's list
            self._commands[name].append(auth_instance)

    def unregister_command(self, names, callback):
        '''Unregisters the given command names from the given callback'''

        # Was only one command given?
        if isinstance(names, str):

            # Set the command to a list
            names = [names]

        # Are the commands given of a proper type?
        if not type(names) in (list, tuple):

            # If not, raise an error
            raise TypeError(
                '%s commands must be passed as a ' % type(self).__name__ +
                'list, tuple, or string, not "%s"' % type(names).__name__)

        # Loop through all given names
        for name in names:

            # Is the current command in the dictionary?
            if not name in self._commands:

                # If not, no need to unregister
                continue

            # Loop through each authorization instance in the list
            for auth_instance in self._commands[name]:

                # Is the current callback the given callback?
                if auth_instance.callback == callback:

                    # Remove the callback from the list
                    self._commands[name].remove(auth_instance)

                    # No need to keep looping for this command name
                    break

    def register_filter(self, callback):
        '''Registers a filter'''
        self._filters.AddToEnd(callback)

    def unregister_filter(self, callback):
        '''Unregisters a filter'''
        self._filters.Remove(callback)


class _AuthCallback(object):
    '''Authorization class used to check if a player is
        authorized to use a command before calling the callback'''

    def __init__(self, callback, level, permission, flag, fail_callback):
        '''Stores all the given arguments'''
        self.callback = callback
        self.level = level
        self.permission = permission
        self.flag = flag
        self.check_auth = not all(
            [item is None for item in [level, permission, flag]])
        self.fail_callback = fail_callback

    def __call__(self, *args):
        '''Checks to see if the player is
            authorized before calling the callback'''

        # Does the player's authorization need to be checked?
        if self.check_auth:

            # Get the player's IPlayerInfo instance
            playerinfo = self._get_playerinfo(args[0])

            # Is the player authorized?
            if not AuthManager.is_player_authorized(
                    playerinfo, self.level, self.permission, self.flag):

                # Is there fail callback?
                if not self.fail_callback is None:

                    # Use try/except in case the fail
                    # callback encounters an error
                    try:

                        # Call the fail callback
                        self.fail_callback(*args)

                    # Was an error encountered?
                    except:

                        # Print the exception to the console
                        ExceptHooks.print_exception()

                # Return a False value, since the player is not authorized
                return False

        # Call the callback and return its value
        return self.callback(*args)
