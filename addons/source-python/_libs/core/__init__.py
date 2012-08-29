# ../_libs/core/__init__.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   OS
from os import sep

# Source.Python Imports
from Source import Engine
from Source import Shared
from Source import Cvar
from paths import GAME_PATH


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the specific game for the server
GAME_NAME = GAME_PATH.rsplit(sep, 2)[1]

# Get the Engine's instance
GameEngine = Engine.GetEngine()

# Get the Cvar instance
_ServerCvar = Cvar.GetCvar()


# =============================================================================
# >> CLASSES
# =============================================================================
class ServerVar(object):
    '''ConVar wrapper to provide easy access to cvars.'''

    def __init__(self, *args):
        '''Called when a server-var is initilized.'''

        # Only one argument?
        if len(args) == 1:

            # Make sure first argument is a string
            name = str(args[0])

            # Try to find an existing instance of the cvar
            self.ConVar = _ServerCvar.FindVar(name)

            # Does the ConVar exist?
            if not self.ConVar:

                # Create the ConVar instance
                self.ConVar = Cvar.ConVar(name, '0', 0, name)

        # Multiple arguments
        else:

            # Default types taken by the ConVar constructor
            default_types = (str, str, int, str, bool, float, bool, float)

            # Convert argument tuple into a list
            args = list(args)

            # Loop through each argument
            for i in range(len(args)):

                # Convert the argument to its appropriate type
                args[i] = default_types[i](args[i])

            # Create the new ConVar using the constructor
            self.ConVar = Cvar.ConVar(*args)             

    def __getattr__(self, name):
        '''Runs missing attributes and methods against ConVar instance'''
        return getattr(self.ConVar, name)       

    def __str__(self):
        '''Returns string value of ConVar instance.'''
        return self.ConVar.GetString()

    def __float__(self):
        '''Returns float value of ConVar instance.'''
        return self.ConVar.GetFloat()

    def __int__(self):
        '''Returns int value of ConVar instance.'''
        return self.ConVar.GetInt()

    def __bool__(self):
        '''Returns bool value of ConVar instance.'''
        return self.ConVar.GetBool()

    def __repr__(self):
        '''Returns string value of ConVar instance.'''
        return self.ConVar.GetString()

    def Set(self, value):
        '''Sets the value of the ConVar instance based on the input type.'''

        # Is the given value an integer?
        if type(value) == int:

            # Set the value as an integer
            self.ConVar.SetInt(value)

        # Is the given value a float?
        elif type(value) == float:

            # Set the value as a float
            self.ConVar.SetFloat(value)

        # Is the given value a bool?
        elif type(value) == bool:

            # Set the value as a bool
            self.ConVar.SetInt(int(value))

        # All other cases
        else:

            # Set value as a string
            self.ConVar.SetString(value)

    def MakePublic(self):
        '''Sets the notify flag for the cvar.'''
        self.ConVar.AddFlags(Cvar.FCVAR_NOTIFY)

    def _get_notify(self):
        '''Returns whether the Notify flag is set'''
        return self.ConVar.IsFlagSet(Cvar.FCVAR_NOTIFY)

    def _set_notify(self, value):
        '''Sets the Notify flag'''

        # Make sure the value is a boolean
        value = bool(value)

        # Is the value True?
        if value:

            # Add the Notify flag
            self.ConVar.AddFlags(Cvar.FCVAR_NOTIFY)

        # Is the value False?
        else:

            # Remove the Notify flag
            self.ConVar.RemoveFlags(Cvar.FCVAR_NOTIFY)

    # Create the notify property
    notify = property(_get_notify, _set_notify)

    def _get_cheat(self):
        '''Returns whether the Cheat flag is set'''
        return self.ConVar.IsFlagSet(Cvar.FCVAR_CHEAT)

    def _set_cheat(self, value):
        '''Sets the Cheat flag'''

        # Make sure the value is a boolean
        value = bool(value)

        # Is the value True?
        if value:

            # Add the Cheat flag
            self.ConVar.AddFlags(Cvar.FCVAR_CHEAT)

        # Is the value False?
        else:

            # Remove the Cheat flag
            self.ConVar.RemoveFlags(Cvar.FCVAR_CHEAT)

    # Create the cheat property
    cheat = property(_get_cheat, _set_cheat)

    def _get_replicated(self):
        '''Returns whether the Replicated flag is set'''
        return self.ConVar.IsFlagSet(Cvar.FCVAR_REPLICATED)

    def _set_replicated(self, value):
        '''Sets the Replicated flag'''

        # Make sure the value is a boolean
        value = bool(value)

        # Is the value True?
        if value:

            # Add the Replicated flag
            self.ConVar.AddFlags(Cvar.FCVAR_REPLICATED)

        # Is the value False?
        else:

            # Remove the Replicated flag
            self.ConVar.RemoveFlags(Cvar.FCVAR_REPLICATED)

    # Create the replicated property
    replicated = property(_get_replicated, _set_replicated)

    def _get_hidden(self):
        '''Returns whether the Hidden flag is set'''
        return self.ConVar.IsFlagSet(Cvar.FCVAR_HIDDEN)

    def _set_hidden(self, value):
        '''Sets the Hidden flag'''

        # Make sure the value is a boolean
        value = bool(value)

        # Is the value True?
        if value:

            # Add the Hidden flag
            self.ConVar.AddFlags(Cvar.FCVAR_HIDDEN)

        # Is the value False?
        else:

            # Remove the Hidden flag
            self.ConVar.RemoveFlags(Cvar.FCVAR_HIDDEN)

    # Create the hidden property
    hidden = property(_get_hidden, _set_hidden)
