# ../_libs/auth/commands.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python imports
#   Auth
from auth.manager import AuthManager
#   Core
from core.commands import echo_console


# =============================================================================
# >> CLASSES
# =============================================================================
class _AuthCommands(dict):
    '''Class used for executing "sp auth" sub-command functionality'''

    def __init__(self):
        '''Called on instanciation'''

        # Create a list to keep the items in order for iteration
        self._order = list()

    def __setitem__(self, item, value):
        '''
            Override the __setitem__ method to add the item to the ordered list
        '''

        # Add the item to the ordered list
        self._order.append(item)

        # Add the item to the dictionary
        super(_AuthCommands, self).__setitem__(item, value)

    def __iter__(self):
        '''Override the __iter__ method to make sure to use the ordered list'''

        # Loop through the ordered list
        for item in self._order:

            # Yield the current item
            yield item

    def call_command(self, args):
        '''Executes the given "sp auth" sub-command'''

        # Was a command given?
        if not args:

            # Send a message that a sub-command is needed
            echo_console('[SP Auth] The "sp auth"' +
                'command must be followed by a sub-command.')

            # Print the auth help text
            self._print_auth_help()

            # No need to go further
            return

        # Get the command
        command = args[0]

        # Is the command registered?
        if not command in self:

            # Send a message about the invalid command
            echo_console(
                '[SP Auth] "%s" is not a valid sub-command.' % command)

            # Print the auth help text
            self._print_auth_help()

            # No need to go further
            return

        # Does the given command use arguments?
        if hasattr(self[command], 'args'):

            # Execute the command with the given arguments
            self[command](args[1:])

            # Go no further
            return

        # Execute the command
        self[command]()

    def _print_auth_help(self):
        '''Prints all "sp auth" sub-commands.'''

        # Send header messages
        echo_console('[Source.Python Auth] Help:')
        echo_console('usage: sp auth <command> [arguments]')
        echo_console('=' * 76)

        # Print all "sp auth" sub-commands
        self._print_help()

        # Send ending message
        echo_console('=' * 76)

    def _print_help(self):
        '''Prints all "sp auth" sub-commands'''

        # Loop through all registered sub-commands
        for item in self:

            # Set the text
            text = 'auth %s' % item

            # Does the current item use arguments?
            if hasattr(self[item], 'args'):

                # Add the arguments to the text
                text += ' ' + ' '.join(self[item].args)

            # Send a message for the current command
            echo_console(
                '%s %s' % (text, self[item].__doc__.rjust(75 - len(text))))


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def _load_auth_providers(providers):
    '''Loads the given auth providers.'''

    # Were any providers given?
    if not providers:

        # Send a message about the required argument
        echo_console('[SP Auth] The "sp auth load"' +
            'command requires at least one auth provider argument.')

        # No need to go further
        return

    # Loop through all of the given providers
    for provider in providers:

        # Load the current provider
        AuthManager.load_auth(provider)


def _unload_auth_providers(providers):
    '''Unloads the given auth providers.'''

    # Were any providers given?
    if not providers:

        # Send a message about the required argument
        echo_console('[SP Auth] The "sp auth unload"' +
            'command requires at least one auth provider argument.')

        # No need to go further
        return

    # Loop through all of the given providers
    for provider in providers:

        # Unload the current provider
        AuthManager.unload_auth(provider)


def _reload_auth_providers(providers=None):
    '''Reloads the given auth providers.'''

    # Were any providers given?
    if not providers:

        # Set providers to all currently loaded providers
        providers = list(AuthManager)

    # Loop through the providers
    for provider in providers:

        # Reload the given provider
        AuthManager.reload_auth(provider)


def _print_auth_providers():
    '''Lists all currently loaded auth providers.'''

    # Send header messages
    echo_console('[SP Auth] Loaded Auth Providers:')
    echo_console('=' * 61)

    # Loop through all loaded auth providers
    for provider in AuthManager:

        # Print message for the current provider
        echo_console(provider)

    # Print ending messages
    echo_console('=' * 61 + '\n')

# Get the _AuthCommands instance
AuthCommands = _AuthCommands()

# Add all auth loading/unloading commands to the dictionary
AuthCommands['load'] = _load_auth_providers
AuthCommands['load'].args = ['<provider>', '[provider]',  '...']
AuthCommands['unload'] = _unload_auth_providers
AuthCommands['unload'].args = ['<provider>', '[provider]',  '...']
AuthCommands['reload'] = _reload_auth_providers
AuthCommands['reload'].args = ['[provider]', '[provider]',  '...']

# Add all printing commands to the dictionary
AuthCommands['list'] = _print_auth_providers
AuthCommands['help'] = AuthCommands._print_auth_help
