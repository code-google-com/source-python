# ../_libs/config/cvar.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core.cvar import ServerVar


# =============================================================================
# >> CLASSES
# =============================================================================
class CvarManager(dict):
    '''Class used to store a cvar instance'''

    def __init__(
            self, name, default, flags, description, min_value, max_value):
        '''Called on instanciation'''

        # Store the base attributes for the cvar
        self.name = name
        self.default = default
        self.description = description

        # Get the Cvar instance
        self.cvar = ServerVar(
            name, default, flags, description, min_value, max_value)

        # Store a list to iterate over description fields and text
        self._order = list()

    def __getattr__(self, attr):
        '''Define __getattr__ to return Cvar
            attributes or items in the instance'''

        # Does the Cvar instance have the given attribute?
        if hasattr(self.cvar, attr):

            # Return the attribute for the Cvar instance
            return getattr(self.cvar, attr)

        # Return the item
        return self.__getitem__(attr)

    def __missing__(self, item):
        '''Define __missing__ to create the item as a _ListManager instance'''

        # Get the _ListManager instance for the given item
        value = self[item] = _ListManager(item)

        # Add the _ListManager instance to the ordered list
        self._order.append(value)

        # Return the _ListManager instance
        return value

    def __iter__(self):
        '''Override __iter__ to iterate over items in the ordered list'''

        # Loop through items in the ordered list
        for item in self._order:

            # Is the current item a _ListManager instance?
            if isinstance(item, _ListManager):

                # Yield the item's name
                yield item.name, 0

                # Loop through each line in the _ListManager instance
                for line in item:

                    # Yield the line
                    yield item.start + line, item.indent

            # Is the current item not a _ListManager instance?
            else:

                # Yield the item
                yield item, 0

    def text(self, text):
        '''Adds simple text or a TranslationStrings
            instance to the ordered list'''
        self._order.append(text)


class _ListManager(list):
    '''List class used to store text for a specific descriptor of a Cvar'''

    def __init__(self, name):
        '''Called on instanciation'''

        # Store the base attributes for the list
        self.name = name
        self.start = ''
        self.indent = 0
