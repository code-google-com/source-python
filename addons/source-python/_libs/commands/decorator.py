# ../_libs/commands/decorator.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core.decorators import BaseDecorator
#   Commands
from commands.manager import ClientCommandRegistry
from commands.manager import SayCommandRegistry
from commands.manager import ServerCommandRegistry


# =============================================================================
# >> BASE CLASSES
# =============================================================================
class _CommandDecorator(BaseDecorator):
    '''Command decorator class'''

    def __init__(self, class_instance):
        '''Stores the instanciating _BaseCommand class instance'''

        # Store the instanciating instance
        self.class_instance = class_instance

    def __call__(self, *args, **kw):
        '''Calls the _BaseCommand instance callback with the given arguments'''

        # Call the callback with the given arguments
        return self.class_instance.callback(*args, **kw)

    def _UnregisterDecorator(self):
        '''Unregisters the command'''

        # Unregister the command
        self.class_instance._UnregisterCommand()


class _BaseCommand(object):
    '''Class used to create commands using a decorator'''

    def __init__(self, name, description):
        '''Stores the given name and description'''

        # Store the base attributes
        self.name = name
        self.description = description

        # Store args a an empty tuple for Server Commands
        self.args = ()

    def __call__(self, callback):
        '''Registers the command with the given callback
            and returns a _CommandDecorator instance'''

        # Store the given callback
        self.callback = callback

        # Register the command with the given
        # callback and the stored description
        self.RegistryClass.RegisterCommand(
            self.name, self.callback, self.description, *args)

        # Return a _CommandDecorator instance for the current class instance
        return _CommandDecorator(self)

    def _UnregisterCommand(self):
        '''Unregisters the command'''

        # Unregister the command
        self.RegistryClass.UnregisterCommand(self.name, self.callback)


class _BasePlayerCommand(_BaseCommand):
    '''Class used to create commands using a decorator that
        allows Authorization information to be passed'''

    def __init__(self, name, description, *args):
        '''Stores the given name, description, and Authorization arguments'''

        # Store the base attributes
        self.name = name
        self.description = description
        self.args = args


# =============================================================================
# >> COMMAND CLASSES
# =============================================================================
class ClientCommand(_BasePlayerCommand):
    '''Decorator class used to create Client commands'''

    # Set the class to register/unregister as ClientCommandRegistry
    RegistryClass = ClientCommandRegistry


class SayCommand(_BasePlayerCommand):
    '''Decorator class used to create Say commands'''

    # Set the class to register/unregister as SayCommandRegistry
    RegistryClass = SayCommandRegistry


class ServerCommand(_BaseCommand):
    '''Decorator class used to create Server commands'''

    # Set the class to register/unregister as ServerCommandRegistry
    RegistryClass = ServerCommandRegistry
