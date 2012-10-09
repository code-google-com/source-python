# ../_libs/core/cvar.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Cvar


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the Cvar instance
_ServerCvar = Cvar.GetCvar()


# =============================================================================
# >> CLASSES
# =============================================================================
class _ServerVarDictionary(dict):
    '''Dictionary class that holds Cvar.ConVar instances'''

    def _get_instance(self, name, value, flags, desc, min_value, max_value):
        '''Retrieves a Cvar.ConVar instance for the given name'''

        # Has the name already been added to the dictionary?
        if name in self:

            # Return the instance
            return self[name]

        # Find the ConVar if it already exists
        cvar = _ServerCvar.FindVar(name)

        # Does the ConVar already exist?
        if cvar:

            # Add the ConVar to the dictionary
            self[name] = cvar

            # Return the ConVar
            return self[name]

        # Was no min nor max value given?
        if min_value is None and max_value is None:

            # Create the ConVar with the given values
            cvar = Cvar.ConVar(name, value, flags, desc)

        # Was a min or max value given?
        else:

            # Create the ConVar with the given values
            cvar = Cvar.ConVar(
                name, value, flags, desc,
                min_value is None,
                min_value if not min_value is None else 0.0,
                max_value is None,
                max_value if not max_value is None else 0.0)

        # Add the ConVar to the dictionary
        self[name] = cvar

        # Return the ConVar
        return self[name]

# Get the _ServerVarDictionary instance
ServerVarDictionary = _ServerVarDictionary()


class ServerVar(object):
    '''ConVar wrapper to provide easy access to cvars.'''

    def __init__(
            self, name, value='0', flags=0,
            desc='', min_value=None, max_value=None):

        '''Called when a server-var is initilized.'''

        # Get the ConVar's instance
        self.cvar = ServerVarDictionary._get_instance(
            name, value, flags, desc, min_value, max_value)

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

    def set_value(self, value):
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

    def make_public(self):
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
