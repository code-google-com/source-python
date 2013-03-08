# ../_libs/cvars.py

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

    def _get_instance(
            self, name, value, flags, description, min_value, max_value):
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
            cvar = Cvar.ConVar(name, value, flags, description)

        # Was a min or max value given?
        else:

            # Create the ConVar with the given values
            cvar = Cvar.ConVar(
                name, value, flags, description,
                min_value is None, min_value or 0.0,
                max_value is None, max_value or 0.0)

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
            description='', min_value=None, max_value=None):

        '''Called when a server-var is initilized.'''

        # Get the ConVar's instance
        self.cvar = ServerVarDictionary._get_instance(
            name, value, flags, description, min_value, max_value)

    def __getattr__(self, attr):
        '''Gets the value of the given attribute'''

        # Is the attribute a flag?
        if hasattr(Cvar, 'FCVAR_%s' % attr.upper()):

            # Return the value of the cvar's flag
            return self.cvar.IsFlagSet(
                getattr(Cvar, 'FCVAR_%s' % attr.upper()))

        # If not, return the cvar's attribute
        return getattr(self.cvar, attr)

    def __setattr__(self, attr, value):
        '''Sets the value of the given attribute'''

        # Is the attribute a flag?
        if not hasattr(Cvar, 'FCVAR_%s' % attr.upper()):

            # Set the attribute
            super(ServerVar, self).__setattr__(attr, value)

            # No need to go further
            return

        # Get the flag
        flag = getattr(Cvar, 'FCVAR_%s' % attr.upper())

        # Is the value "True"
        if value:

            # Add the flag
            self.cvar.AddFlags(flag)

            # No need to go further
            return

        # Remove the flag
        self.cvar.RemoveFlags(flag)

    def make_public(self):
        '''Sets the notify flag for the cvar.'''
        self.cvar.AddFlags(Cvar.FCVAR_NOTIFY)
