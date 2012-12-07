# ../_libs/auth/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python imports
#   Auth
from auth.paths import AUTH_PROVIDER_PATH
#   Core
from core.commands import echo_console
#   Players
from players.helpers import uniqueid_from_playerinfo


# =============================================================================
# >> CLASSES
# =============================================================================
class _AuthManager(dict):
    '''Class used to store loaded auth providers
        and check if a player is authorized'''

    def load_auth(self, provider):
        '''Loads the given provider'''

        # Send a message that the auth provider is being loaded
        echo_console('SP Auth] Attempting to load provider "%s"' % provider)

        # Is the provider loaded?
        if provider in self:

            # If so, send a message that the provider is already loaded
            echo_console(
                '[SP Auth] Unable to load provider "' +
                '%s", provider is already loaded.' % provider)

            # No need to go further
            return

        # Does the provider's file exist?
        if not AUTH_PROVIDER_PATH.joinpath(provider + '.py').isfile():

            # Send a message that the file does not exist
            echo_console(
                '[SP Auth] Unable to load provider "%s", ' % provider +
                'missing file ../addons/source-python/auth/%s.py' % provider)

            # No need to go further
            return

        # Attempt to load the provider
        self[provider] = __import__(
            'auth.providers.%s' % provider, fromlist=[''])

        # Call the provider's load function
        self[provider].load()

        # Send a message that the provider was loaded
        echo_console('[SP Auth] Successfully loaded provider "%s"' % provider)

    def unload_auth(self, provider):
        '''Unloads the given provider'''

        # Send a message that the auth provider is being unloaded
        echo_console('SP Auth] Attempting to unload provider "%s"' % provider)

        # Is the provider loaded?
        if not provider in self:

            # If not, send a message that the provider is not loaded
            echo_console(
                '[SP Auth] Unable to unload provider ' +
                '"%s", provider not loaded.' % provider)

        # Call the providers unload method
        self[provider].unload()

        # Remove the provider
        del self[provider]

        # Send a message that the provider was unloaded
        echo_console(
            '[SP Auth] Successfully unloaded provider "%s"' % provider)

    def reload_auth(self, provider):
        '''Reloads the given provider'''

        # Unload the provider
        self.unload_auth(provider)

        # Load the provider
        self.load_auth(provider)

    def is_player_authorized(
            self, playerinfo, level=None, permission=None, flag=None):
        '''Checks to see if the player is authorized'''

        # Get the player's uniqueid
        uniqueid = uniqueid_from_playerinfo(playerinfo)

        # Loop through all loaded auth providers
        for provider in self:

            # Is the player authorized?
            if self[provider].is_player_authorized(
                    uniqueid, level, permission, flag):

                # If the player is authorized, return true
                return True

        # If the player is not found authorized for any provider, return false
        return False

# Get the _AuthManager instance
AuthManager = _AuthManager()
