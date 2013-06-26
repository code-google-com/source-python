# ../_libs/commands/auth.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from player_c import CPlayerInfo
from excepthooks import ExceptHooks
#   Auth
from auth.manager import AuthManager


# =============================================================================
# >> CLASSES
# =============================================================================
class _AuthCallback(object):
    '''Authorization class used to check if a player is
        authorized to use a command before calling the callback'''

    def __init__(self, callback, level=None,
            permission=None, flag=None, fail_callback=None):
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

            # Is the player authorized?
            if not AuthManager.is_player_authorized(
                    args[0], self.level, self.permission, self.flag):

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
