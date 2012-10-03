# ../_libs/messages/__init__.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Path
from path import path
#   Sys
import sys


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the current module
_basemodule = sys.modules[__package__]

# Loop through all files in the directory
for _filepath in path(__file__).parent.files('*.py'):

    # Get the file's name
    _filename = _filepath.namebase

    # Is the file private?
    if _filename.startswith('_'):

        # If so, skip this file
        continue

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
            if type(_module.__dict__[item]).__name__ != 'function':

                # If not, do not import this item
                continue

            # Is the current item native to the current module?
            if _module.__dict__[item].__module__ == _module.__name__:

                # Add the function as a global object for this module
                _basemodule.__dict__[item] = _module.__dict__[item]

    # Was an error encountered?
    except:

        # Do nothing
        pass
