# ../_libs/addons/info.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Collections
from collections import OrderedDict


# =============================================================================
# >> CLASSES
# =============================================================================
class AddonInfo(OrderedDict):
    '''Stores information for an addon'''

    def __getattr__(self, attribute):
        '''Redirects to __getitem__'''

        # Is the attribute private?
        if attribute.startswith('_'):

            # Raise an error
            # This is done to fix an issue with OrderedDict.__init__
            raise AttributeError('Private attributes not allowed')

        # Redirect to __getitem__
        return self[attribute]

    def __setattr__(self, attribute, value):
        '''Redirects to __setitem__'''

        # Is the attribute private?
        if attribute.startswith('_'):

            # Re-call __setattr__
            # This is done to fix an issue with OrderedDict.__init__
            super(AddonInfo, self).__setattr__(attribute, value)

            # No need to go further
            return

        # Redirect to __setitem__
        self[attribute] = value
