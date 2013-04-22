# ../_libs/events/custom.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Collections
from collections import OrderedDict

# Source.Python Imports
from event_c import CGameEvent


# =============================================================================
# >> CLASSES
# =============================================================================
class _EventMeta(type):
    '''Metaclass used to store class attributes in an ordered dictionary'''

    @classmethod
    def __prepare__(mcl, name, bases):
        '''Return an ordered dictionary'''
        return OrderedDict()

    def __new__(mcl, name, bases, odict):
        '''Called when the class is being created'''

        # Create the instance
        cls = super().__new__(mcl, name, bases, dict(odict))

        # Store an ordered dictionary
        cls._odict = OrderedDict()

        # Loop through all items in the given ordered dictionary
        for item in odict:

            # Is the item not a magic method?
            if not item.startswith('__'):

                # Add the item to the dictionary
                cls._odict[item] = odict[item]

        # Return the class
        return cls


class CustomEvent(metaclass=_EventMeta):
    '''Class inherited to create custom events'''

    def __init__(self, **kwargs):
        '''Called on instantiation'''

        # Loop through the given keyword arguments
        for kwarg in kwargs:

            # Is the current keyword in the event's variables?
            if not kwarg in self._odict:

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
        if not attr.startswith('_') and attr in self._odict:

            # Set the attribute as the private value
            super(CustomEvent, self).__setattr__('_' + attr, value)

            # No need to go further
            return

        # Set the attribute
        super(CustomEvent, self).__setattr__(attr, value)

    def fire(self):
        '''Fires the event with the stored variable values'''

        # Get the event's instance
        event = CGameEvent(self.name, True)

        # Loop through the event's variables
        for variable in self._odict:

            # Set the event variable values
            getattr(event, 'set_' + self._odict[variable]._method)(
                variable, getattr(self, '_' + variable))

        # Fire the event
        event.fire_event()

    def reset(self):
        '''Resets all event variable values to their default values'''

        # Loop through the event's variables
        for variable in self._odict:

            # Set the variable to its default value
            super(CustomEvent, self).__setattr__(
                '_' + variable, getattr(self, variable)._default)

    @property
    def name(self):
        '''Returns the name of the event'''
        return self.__class__.__name__.lower()
