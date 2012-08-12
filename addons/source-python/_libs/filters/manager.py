# ../_libs/filters/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Filters
from filters.errors import FilterError
from filters.errors import ReturnTypeError
from filters.registry import _BaseRegistry


# =============================================================================
# >> CLASSES
# =============================================================================
class _BaseFilterManager(object):
    '''Class designed to be used for object
        filtering and returning specific types'''

    def __init__(self):
        '''Called on class initialization'''

        # Store filter/return type dictionaries
        self._filters = _BaseRegistry('filter', FilterError)
        self._return_types = _BaseRegistry('return type', ReturnTypeError)

    def RegisterFilter(self, filter_name, function):
        '''Registers the given filter to the class'''

        # Register the filter
        self._filters.Register(filter_name, function)

    def UnregisterFilter(self, filter_name):
        '''Unregisters the given filter from the class'''

        # Unregister the filter
        self._filters.Unregister(filter_name)

    def RegisterReturnType(self, return_type, function):
        '''Registers the given return type to the class'''

        # Register the return type
        self._return_types.Register(return_type, function)

    def UnregisterReturnType(self, return_type, function):
        '''Unregisters the given return type from the class'''

        # Unregister the return type
        self._return_types.Unregister(return_type)
