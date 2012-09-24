# ../_libs/filters/registry.py


# =============================================================================
# >> CLASSES
# =============================================================================
class _BaseRegistry(dict):
    '''Class that stores a registry of items'''

    def __init__(self, name, error, class_name):
        '''Stores the name and error type on initialization'''

        # Store the name, error type, and registering class' name
        self._name = name
        self._error = error
        self._class_name = class_name

    def Register(self, item, function):
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

    def Unregister(self, item):
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

    def __getitem__(self, item):
        '''Override __getitem__ to call the correct
            error when an invalid item is used'''

        # Is the given item valid?
        if not item in self:

            # Raise an error
            raise self._error('Invalid %s "%s"' % (self._name, item))

        # Return the callable
        return super(_BaseRegistry, self).__getitem__(item)
