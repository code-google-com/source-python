# ../_libs/loggers.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Logging
from logging import CRITICAL
from logging import DEBUG
from logging import ERROR
from logging import INFO
from logging import WARNING
from logging import FileHandler
from logging import Formatter
from logging import addLevelName
from logging import getLogger

# Source.Python Imports
from core import GameEngine
from core import echo_console
from cvars import ServerVar
from paths import LOG_PATH


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Store the areas constants
CONSOLE = 1
MAIN_LOG = 2
SP_LOG = 4
SCRIPT_LOG = 8

# Store the new level names
ALWAYS = 60

# Add the new level names
addLevelName(ALWAYS, 'MESSAGE')


# =============================================================================
# >> CLASSES
# =============================================================================
class _LogInstance(dict):
    '''Base logging class used to create child logging instances'''

    def __init__(self, name, parent):
        '''Stores the parent and gets a child of the parent'''

        # Store the parent instance
        self.parent = parent

        # Store a child logging instance
        self.logger = parent.logger.getChild(name)

    def __missing__(self, item):
        '''Adds new items as logging instances'''

        # Get the new logging instance
        value = self[item] = _LogInstance(item, self)

        # Return the logging instance
        return value

    def __getattr__(self, attr):
        '''Calls __getitem__ to return the item in the dictionary'''
        return self[attr]

    def __delitem__(self, item):
        '''Removes all children of the instance and closes the logger'''

        # Remove all children
        self[item].clear()

        # Close the logger
        self.logger.close()

    def clear(self):
        '''Deletes each item individually to close all loggers'''

        # Loop through each child
        for item in list(self):

            # Remove the child
            del self[item]

    def critical(self, msg, *args, **kwargs):
        '''Use to call a critical message'''
        self._log(CRITICAL, msg, *args, **kwargs)

    def debug(self, msg, *args, **kwargs):
        '''Use to call a debug message'''
        self._log(DEBUG, msg, *args, **kwargs)

    def exception(self, msg, *args, **kwargs):
        '''Use to call an exception message'''
        self._log(ERROR, msg, *args, **kwargs)

    def info(self, msg, *args, **kwargs):
        '''Use to call a basic info message'''
        self._log(INFO, msg, *args, **kwargs)

    def warning(self, msg, *args, **kwargs):
        '''Use to call a warning message'''
        self._log(WARNING, msg, *args, **kwargs)

    def message(self, msg, *args, **kwargs):
        '''Use to call a message that should always print'''
        self._log(ALWAYS, msg, *args, **kwargs)

    def log(self, level, msg, *args, **kwargs):
        '''Use to call a message with the given logging level'''

        # Get the value of the given level
        level = self._get_level_value(level)

        # Call the main logging method
        self._log(level, msg, *args, **kwargs)

    def _log(self, level, msg, *args, **kwargs):
        '''Main logging method'''

        # Does the message need logged?
        if self.disable >= level:

            # If not, simply return
            return

        # Get the areas to be used
        areas = self.areas

        # Print to main log file?
        if MAIN_LOG & areas:

            # Get the message to send
            record = self.logger.makeRecord(
                self.logger.name, level, '(unknown file)', 0, msg, args, None)
            message = self.root.format(record)

            # Print to the main log
            GameEngine.log_print(message)

        # Print to the console?
        if CONSOLE & areas:

            # Print to the console
            echo_console(msg)

        # Print to the script's log file?
        if SCRIPT_LOG & areas and self.root != SPLogger:

            # Print message to the log file
            self.logger.log(level, msg, *args, **kwargs)

        # Print to the main SP log file?
        if SP_LOG & areas:

            # Print to the SP log file
            SPLogger.logger.log(level , msg, *args, **kwargs)

    @staticmethod
    def _get_level_value(level):
        '''Returns a level value used by the logging package'''
        return 50 - (10 * level)

    @property
    def root(self):
        '''Returns the root class'''

        # Store the current instance
        instance = self

        # Use a while statement to get the parent until root is found
        while not instance.parent is None:

            # Set the current instance to the parent
            instance = instance.parent

        # Return the root instance
        return instance

    @property
    def areas(self):
        '''Returns the root's areas value'''
        return self.root.areas

    @property
    def disable(self):
        '''Returns the root's disable value'''
        return self.root.disable


class LogManager(_LogInstance):
    '''Main log class used as a root to create children instances'''

    def __init__(
            self, name, filepath, level, areas,
            format=None, date_format=None):
        '''Stores the base values and creates the logger'''

        # Create the root logger
        self.logger = getLogger(name)
        self.handler = FileHandler(LOG_PATH.joinpath(filepath + '.log'))
        self.format = Formatter(format, date_format)
        self.handler.setFormatter(self.format)
        self.logger.addHandler(self.handler)

        # Store the base attributes
        self._level = level
        self._areas = areas
        self.parent = None

    @property
    def disable(self):
        '''Returns the disable value'''
        return 50 - (self._level.get_int() * 10 + 1)

    @property
    def areas(self):
        '''Returns the areas to print messages to'''
        return self._areas.get_int()

# Get the Source.Python main LogManager instance
SPLogger = LogManager(
    'sp', 'source-python', None, None,
    '%(asctime)s - %(name)s\t-\t%(levelname)s\n%(message)s',
    '%m-%d-%Y %H:%M:%S')
