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

# Store flags
_cvar_flags = {
    'notify': Cvar.FCVAR_NOTIFY,
    'cheat': Cvar.FCVAR_CHEAT,
    'replicated': Cvar.FCVAR_REPLICATED,
    'hidden': Cvar.FCVAR_HIDDEN,
}


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

    def __getattr__(self, attr):
        '''Gets the value of the given attribute'''

        # Is the attribute a flag?
        if attr in _cvar_flags:

            # Return the value of the cvar's flag
            return self.cvar.IsFlagSet(_cvar_flags[attr])

        # If not, return the cvar's attribute
        return getattr(self.cvar, attr)

    def __setattr__(self, attr, value):
        '''Sets the value of the given attribute'''

        # Is the attribute a flag?
        if not attr in _cvar_flags:

            # Set the attribute
            super(ServerVar, self).__setattr__(attr, value)

            # No need to go further
            return

        # Is the value "True"
        if value:

            # Add the flag
            self.cvar.AddFlags(_cvar_flags[attr])

            # No need to go further
            return

        # Remove the flag
        self.cvar.RemoveFlags(_cvar_flags[attr])

    def __str__(self):
        '''Returns string value of ConVar instance.'''
        return self.cvar.GetString()

    def __float__(self):
        '''Returns float value of ConVar instance.'''
        return self.cvar.GetFloat()

    def __int__(self):
        '''Returns int value of ConVar instance.'''
        return self.cvar.GetInt()

    def __bool__(self):
        '''Returns bool value of ConVar instance.'''
        return self.cvar.GetBool()

    def __repr__(self):
        '''Returns string value of ConVar instance.'''
        return self.cvar.GetString()

    def set_value(self, value):
        '''Sets the value of the ConVar instance based on the input type.'''

        # Is the given value an integer?
        if type(value) == int:

            # Set the value as an integer
            self.cvar.SetInt(value)

        # Is the given value a float?
        elif type(value) == float:

            # Set the value as a float
            self.cvar.SetFloat(value)

        # Is the given value a bool?
        elif type(value) == bool:

            # Set the value as a bool
            self.cvar.SetInt(int(value))

        # All other cases
        else:

            # Set value as a string
            self.cvar.SetString(value)

    def make_public(self):
        '''Sets the notify flag for the cvar.'''
        self.cvar.AddFlags(Cvar.FCVAR_NOTIFY)
