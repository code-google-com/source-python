# ../_libs/filters/iterator.py


# =============================================================================
# >> CLASSES
# =============================================================================
class _IterObject(object):
    '''Base iterator class used to yield filtered items'''

    def __init__(self, is_filters=[], not_filters=[], return_types='index'):
        '''Stores filters and return types for the instance'''

        # Are the "is" filters a string?
        if isinstance(is_filters, str):

            # Store the "is" filters as a list
            is_filters = [is_filters]

        # Are the "not" filters a string?
        if isinstance(not_filters, str):

            # Store the "not" filters as a list
            is_filters = [not_filters]

        # Store the filters and return types
        self._is_filters = is_filters
        self._not_filters = not_filters
        self._return_types = return_types

    def __iter__(self):
        '''Iterates through the class objects
            and filters out any unneeded ones'''

        # Loop through the items in classes iterator
        for item in self.iterator():

            # Is the current item yieldable?
            if not self._is_valid(item):

                # If not, move to the next item
                continue

            # Are the return types a string?
            if isinstance(self._return_types, str):

                # Yield the proper type for the current item
                yield self.manager._return_types[self._return_types](item)

            # Otherwise
            else:

                # Create an empty list to yield
                yield_list = []

                # Loop through all of the return types
                for return_type in self._return_types:

                    # Add the current return type for
                    # the current item to the yield list
                    yield_list.append(
                        self.manager._return_types[return_type](item))

                # Yield the list of return types for the current item
                yield yield_list

    def _is_valid(self, item):
        '''Returns whether the given item is valid for the instances filters'''

        # Loop through all "is" filters
        for filter_name in self._is_filters:

            # Does the item pass this filter?
            if not self.manager._filters[filter_name](item):

                # If not, return False
                return False

        # Loop through all "not" filters
        for filter_name in self._not_filters:

            # Does the item pass this filter?
            if self.manager._filters[filter_name](item):

                # If it does, return False since these are "not" filters
                return False

        # If all checks pass, return True
        return True
