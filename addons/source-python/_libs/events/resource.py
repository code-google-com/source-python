# ../_libs/events/resource.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Collections
from collections import OrderedDict

# Source.Python Imports
from paths import EVENT_PATH
from public import public
#   Events
from events import EventsLogger
from events.custom import CustomEvent
from events.manager import GameEventManager
from events.variable import _EventVariable


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the sp.events.resource logger
EventsResourceLogger = EventsLogger.resource


# =============================================================================
# >> CLASSES
# =============================================================================
@public
class ResourceFile(OrderedDict):
    '''Class used to write and load custom event .res files'''

    def __init__(self, filepath, *events):
        '''Called on instatiation'''

        # Create the OrderedDict instance
        super(ResourceFile, self).__init__()

        # Does the given path end with the extension?
        if filepath.endswith('.res'):

            # Remove the extension
            filepath = filepath[:~3]

        # Store the filepath
        self._filepath = filepath

        # Loop through all given events
        for event in events:

            # Is the given class not a CustomEvent class?
            if not issubclass(event, CustomEvent):

                # Clear the dictionary
                self.clear()

                # Raise an error
                raise TypeError(
                    'Event classes must be sub-classes of CustomEvent')

            # Store the event with its variables in the dictionary
            self[event.__name__.lower()] = event

    @property
    def filepath(self):
        '''Returns the path to the .res file'''
        return self._filepath

    @property
    def fullpath(self):
        '''Returns the full path of the .res file'''
        return EVENT_PATH.joinpath(self.filepath + '.res')

    def write(self):
        '''Writes the .res file to disk'''

        # Does the director for the .res file exist?
        if not self.fullpath.parent.isdir():

            # Create the directory
            self.fullpath.parent.makedirs()

        # Open the .res file to write to it
        with self.fullpath.open('w') as open_file:

            # Write the .res file's name
            open_file.write('"%s"\n' % self.filepath)

            # Create a group of events for the file
            open_file.write('{\n')

            # Loop through all events
            for event in self:

                # Write the event
                open_file.write('    "%s"\n' % event)

                # Create a group of variables for the event
                open_file.write('    {\n')

                # Loop through the event's variables
                for variable in self[event]._odict:

                    # Get the variable's instance
                    instance = self[event]._odict[variable]

                    # Write the variable with its type and comment
                    open_file.write(
                        '        "%s"\t"%s"%s\n' % (variable, instance.name,
                        ('\t// %s' % instance._comment if
                        instance._comment else '')))

                # End the group of variables
                open_file.write('    }\n')

            # End the group of events
            open_file.write('}\n')

    def load_events(self):
        '''Loads events from the .res file'''
        GameEventManager.load_events_from_file(self.fullpath)
