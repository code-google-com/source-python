# ../_libs/events/resource.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Collections
from collections import OrderedDict

# Source.Python Imports
from Source import event_c
from paths import EVENT_PATH
#   Events
from events.custom import CustomEvent
from events.manager import GameEventManager
from events.variable import _EventVariable


# =============================================================================
# >> CLASSES
# =============================================================================
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

            # Get the event's name
            name = event.__name__.lower()

            # Get the event's variables
            variables = [
                variable for variable in dir(event) if
                isinstance(getattr(event, variable), _EventVariable)]

            # Sort the event's variables
            variables = sorted(
                variables, key=lambda variable:
                getattr(event, variable).counter)

            # Create an ordered dictionary instance
            self[name] = event._variables = OrderedDict()

            # Loop through the sorted variables
            for variable in variables:

                # Store the variable in the ordered dictionary
                self[name][variable] = getattr(event, variable)

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
                for variable in self[event]:

                    # Write the variable with its type and comment
                    open_file.write('        "%s"\t"%s"%s\n' % (
                        variable, self[event][variable].name,
                        ('\t// %s' % self[event][variable].comment if
                        self[event][variable].comment else '')))

                # End the group of variables
                open_file.write('    }\n')

            # End the group of events
            open_file.write('}\n')

    def load_events(self):
        '''Loads events from the .res file'''
        GameEventManager.load_events_from_file(self.fullpath)
