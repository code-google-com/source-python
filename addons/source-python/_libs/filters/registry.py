# ../_libs/filters/registry.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Filters
from filters.errors import FilterError
from filters.errors import ReturnTypeError


# =============================================================================
# >> ALL DECLARATION
# =============================================================================
# Set all to an empty list
__all__ = []


# =============================================================================
# >> BASE REGISTRY CLASS
# =============================================================================
class _BaseRegistry(dict):
    '''Class that stores a registry of items'''

    def __init__(self, class_name):
        '''Stores the name and error type on initialization'''

        # Store the registering class' name
        self._class_name = class_name

    def register(self, item, function):
        '''Registers an item'''

        # Has the item already been added to the dictionary?
        if item in self:

            # Raise an error, since the item cannot be added twice
            raise NameError(
                '%s cannot register %s' % (self._class_name, self._name) +
                ' "%s", it has already been registered.' % item)

        # Is the given function callable?
        if not callable(function):

            # Raise an error, since the object needs to be callable
            raise TypeError(
                '%s cannot register %s' % (self._class_name, self._name) +
                ' "%s", given function not callable.' % item)

        # Add the item to the dictionary
        self[item] = function

    def unregister(self, item):
        '''Unregisters a item'''

        # Has the item been registered?
        if not item in self:

            # Raise an error, since the item cannot be
            # unregistered if it has not been registered
            raise NameError(
                '%s cannot register %s' % (self._class_name, self._name) +
                ' "%s", it has not been registered.' % item)

        # Remove the item from the dictionary
        del self[item]


# =============================================================================
# >> REGISTRATION CLASSES
# =============================================================================
class _FilterRegistry(_BaseRegistry):
    '''Class used to register filters'''

    # Set the _name attribute for filter registry
    _name = 'filter'

    def __getitem__(self, item):
        '''Override __getitem__ to call the correct
            error when an invalid item is used'''

        # Is the given item valid?
        if not item in self:

            # Raise an error
            raise FilterError('Invalid %s "%s"' % (self._name, item))

        # Return the callable
        return super(_FilterRegistry, self).__getitem__(item)


class _ReturnTypeRegistry(_BaseRegistry):
    '''Class used to register return types'''

    # Set the _name attribute for return type registry
    _name = 'return type'

    def __getitem__(self, item):
        '''Override __getitem__ to call the correct
            error when an invalid item is used'''

        # Is the given item valid?
        if not item in self:

            # Raise an error
            raise ReturnTypeError('Invalid %s "%s"' % (self._name, item))

        # Return the callable
        return super(_ReturnTypeRegistry, self).__getitem__(item)
