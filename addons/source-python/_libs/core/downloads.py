# ../_libs/core/downloads.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Misc
#   Core
from core.decorators import BaseDecorator
#   Events
from events.manager import EventRegistry


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the downloadables string table instance
DownloadTable = Misc.GetStringTables().FindTable('downloadables')


# =============================================================================
# >> CLASSES
# =============================================================================
class Downloadables(BaseDecorator, set):
    '''Class used to store downloadables for a script'''

    def __init__(self):
        '''Add the instance to the downloadables list'''
        DownloadablesList.append(self)

    def add(self, item):
        '''Adds an item to the downloadables for a script'''

        # Is the item already in the list?
        if item in self:

            # If so, no need to add it
            return

        # Add the item to the downloadables stringtable
        DownloadTable.AddString(item)

        # Add the item to the script's downloadables
        super(Download, self).add(item)

    def _set_all_downloads(self):
        '''Adds all downloadables for the script on level init'''

        # Loop through all items in the list
        for item in self:

            # Add the item to the downloadables stringtable
            DownloadTable.AddString(item)

    def _unregister_decorator(self):
        '''Removes the instance from the downloadables list'''
        DownloadablesList.remove(self)


class _DownloadablesList(list):
    '''List object used to store downloads on a per-script basis'''

    def level_init(self, GameEvent):
        '''Adds all items stored as downloadables to the stringtable'''

        # Loop through all items in the list
        for item in self:

            # Set all items in the current item as downloadables
            item._set_all_downloads()

# Get the _DownloadablesList instance
DownloadablesList = _DownloadablesList()

# Register for the event level_init in
# order to reset all downloads on map change
EventRegistry.register_for_event(
    'level_init', DownloadablesList.level_init)
