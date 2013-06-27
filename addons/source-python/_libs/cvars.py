# ../_libs/cvars.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
import cvar_c


# =============================================================================
# >> CLASSES
# =============================================================================
class ServerVar(cvar_c.CConVar):
    '''ConVar wrapper to provide easy access to cvars.'''

    def __init__(
            self, name, value='0', flags=0,
            description='', min_value=None, max_value=None):

        '''Called when a server-var is initilized.'''
        super(ServerVar, self).__init__(
            name, value, flags, description,
            not min_value is None, min_value or 0.0,
            not max_value is None, min_value or 0.0)

    def __getattr__(self, attr):
        '''Gets the value of the given attribute'''

        # Is the attribute a flag?
        if hasattr(cvar_c, 'FCVAR_%s' % attr.upper()):

            # Return the value of the cvar's flag
            return self.is_flag_set(
                getattr(cvar_c, 'FCVAR_%s' % attr.upper()))

        # If not, raise an error
        raise AttributeError('"ServerVar" object has no attribute "%s"' % attr)

    def __setattr__(self, attr, value):
        '''Sets the value of the given attribute'''

        # Is the attribute a flag?
        if not hasattr(cvar_c, 'FCVAR_%s' % attr.upper()):

            # Does the instance itself have the attribute?
            if not hasattr(self, attr):

                # If not, raise an error
                raise AttributeError(
                    '"ServerVar" object has no attribute "%s"' % attr)

            # Set the attribute
            super(ServerVar, self).__setattr__(attr, value)

            # No need to go further
            return

        # Get the flag
        flag = getattr(cvar_c, 'FCVAR_%s' % attr.upper())

        # Is the value "True"
        if value:

            # Add the flag
            self.add_flags(flag)

            # No need to go further
            return

        # Remove the flag
        self.remove_flags(flag)

    def make_public(self):
        '''Sets the notify flag for the cvar.'''
        self.add_flags(cvar_c.FCVAR_NOTIFY)
