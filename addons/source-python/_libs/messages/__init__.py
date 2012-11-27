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

# Loop through all files in the "types" directory
for _filepath in path(__file__).parent.joinpath('types').files():

    # Get the file's name
    _filename = _filepath.namebase

    # Import the module
    _module = __import__('messages.types.' + _filename, fromlist=[''])

    # Loop through all items in the module
    for item in _module.__dict__:

        # Is the item private?
        if item.startswith('_'):

            # If so, do not import this item
            continue

        # Is the current item native to the current module?
        if _module.__dict__[item].__module__ == _module.__name__:

            # Add the function as a global object for this module
            _basemodule.__dict__[item] = _module.__dict__[item]
