# ../_libs/messages/__init__.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   OS
from os.path import dirname
from os.path import join
from os import listdir
#   Sys
import sys


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the current directory
_basepath = dirname(__file__)

# Get the current module
_basemodule = sys.modules[__package__ + '.' + __package__]

# Loop through all files in the directory
for _filename in listdir(_basepath):

    # Is the file private?
    if _filename.startswith('_'):

        # If so, skip this file
        continue

    # Get the filename without the extension
    _filename = _filename[:-3]

    # Try to import the module and get its globals
    try:

        # Import the module
        _module = __import__(__package__ + '.' + _filename, fromlist=[''])

        # Loop through all items in the module
        for item in _module.__dict__:

            # Is the item private?
            if item.startswith('_'):

                # If so, do not import this item
                continue

            # Is the current item a function?
            if type(_module.__dict__[item]).__name__ == 'function':

                # Add the function as a global object for this module
                _basemodule.__dict__[item] = _module.__dict__[item]
    # Was an error encountered?
    except:

        # Do nothing
        pass
