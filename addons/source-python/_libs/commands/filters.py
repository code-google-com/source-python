# ../_libs/commands/filters.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from core import AutoUnload


# =============================================================================
# >> CLASSES
# =============================================================================
class _BaseFilter(AutoUnload):
    '''Class used to register a filter'''

    def __init__(self, callback):
        '''Stores the callback and registers the filter'''

        # Is the callback callable?
        if not callable(callback):

            # Raise an error
            raise TypeError(
                "'" + type(callback).__name__ + "' object is not callable")

        # Store the callback
        self.callback = callback

        # Register the filter
        self._ManagerClass.register_filter(self.callback)

    def _unload_instance(self):
        '''Unregisters the filter'''
        self._ManagerClass.unregister_filter(self.callback)
