# ../_libs/events/custom.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import event_c


# =============================================================================
# >> CLASSES
# =============================================================================
class CustomEvent(object):
    '''Class inherited to create custom events'''

    def __init__(self, **kwargs):
        '''Called on instantiation'''

        # Loop through the given keyword arguments
        for kwarg in kwargs:

            # Is the current keyword in the event's variables?
            if not kwarg in self._variables:

                # If not, raise an error
                raise KeyError(
                    'Given keyword "%s" is not a ' % kwarg +
                    'variable for the event "%s"' % self.name)

            # Store the variable's value as a private attribute
            super(CustomEvent, self).__setattr__('_' + kwarg, kwargs[kwarg])

    def __setattr__(self, attr, value):
        '''
            Override __setattr__ to store variable values as private attributes
        '''

        # Is the given attribute for a variable?
        if not attr.startswith('_') and attr in self._variables:

            # Set the attribute as the private value
            super(CustomEvent, self).__setattr__('_' + attr, value)

            # No need to go further
            return

        # Set the attribute
        super(CustomEvent, self).__setattr__(attr, value)

    def fire(self):
        '''Fires the event with the stored variable values'''

        # Get the event's instance
        event = event_c.CGameEvent(self.name, True)

        # Loop through the event's variables
        for variable in self._variables:

            # Set the event variable values
            getattr(event, 'set_' + self._variables[variable]._method)(
                variable, getattr(self, '_' + variable))

        # Fire the event
        event.fire_event()

    def reset(self):
        '''Resets all event variable values to their default values'''

        # Loop through the event's variables
        for variable in self._variables:

            # Set the variable to its default value
            super(CustomEvent, self).__setattr__(
                '_' + variable, getattr(self, variable).default)

    @property
    def name(self):
        '''Returns the name of the event'''
        return self.__class__.__name__.lower()
