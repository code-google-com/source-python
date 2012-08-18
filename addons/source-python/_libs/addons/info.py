# ../_libs/addons/info.py


# =============================================================================
# >> CLASSES
# =============================================================================
class AddonInfo(dict):
    '''Stores information for an addon'''

    def __init__(self):
        '''Creates an empty keylist to be used for ordered iteration'''

        # Create an empty keylist
        self._keylist = []

    def __getattr__(self, attribute):
        '''Gets an item (if it exists) within the dictionary'''

        # Return the item
        return self[attribute]

    def __setattr__(self, attribute, value):
        '''Redirects to __setitem__ for valid attributes'''

        # Is the attribute private?
        if attribute.startswith('_'):

            # Set the attribute
            super(AddonInfo, self).__setattr__(attribute, value)

        # Is the attribute not private?
        else:

            # Add the item to the dictionary with its value
            self[attribute] = value

    def __setitem__(self, item, value):
        '''Sets an item and adds it to the keylist'''

        # Has the item been added to the keylist?
        if not item in self._keylist:

            # Add the item to the keylist
            self._keylist.append(item)

        # Add the item to the dictionary
        super(AddonInfo, self).__setitem__(item, value)

    def __iter__(self):
        '''Loops through all the items in the keylist'''

        # Loop through all items in the keylist
        for item in self._keylist:

            # Yield the current item
            yield item
