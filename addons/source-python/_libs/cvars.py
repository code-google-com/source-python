# ../_libs/cvars.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
import cvar_c


# =============================================================================
# >> CLASSES
# =============================================================================
class ServerVar(object):
    '''ConVar wrapper to provide easy access to cvars.'''

    def __init__(
            self, name, value='0', flags=0,
            description='', min_value=None, max_value=None):

        '''Called when a server-var is initilized.'''

        # Get the ConVar's instance
        self.cvar = cvar_c.CConVar(name, value, flags, description,
            min_value is None, min_value or 0.0,
            max_value is None, max_value or 0.0)

    def __getattr__(self, attr):
        '''Gets the value of the given attribute'''

        # Is the attribute a flag?
        if hasattr(cvar_c, 'FCVAR_%s' % attr.upper()):

            # Return the value of the cvar's flag
            return self.cvar.is_flag_set(
                getattr(cvar_c, 'FCVAR_%s' % attr.upper()))

        # If not, return the cvar's attribute
        return getattr(self.cvar, attr)

    def __setattr__(self, attr, value):
        '''Sets the value of the given attribute'''

        # Is the attribute a flag?
        if not hasattr(cvar_c, 'FCVAR_%s' % attr.upper()):

            # Set the attribute
            super(ServerVar, self).__setattr__(attr, value)

            # No need to go further
            return

        # Get the flag
        flag = getattr(cvar_c, 'FCVAR_%s' % attr.upper())

        # Is the value "True"
        if value:

            # Add the flag
            self.cvar.add_flags(flag)

            # No need to go further
            return

        # Remove the flag
        self.cvar.remove_flags(flag)

    def make_public(self):
        '''Sets the notify flag for the cvar.'''
        self.cvar.add_flags(cvar_c.FCVAR_NOTIFY)
