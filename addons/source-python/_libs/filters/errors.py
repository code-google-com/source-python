# ../_libs/filters/errors.py


# =============================================================================
# >> CLASSES
# =============================================================================
class FilterError(Exception):
    '''Exception raised when an invalid filter is requested'''


class ReturnTypeError(Exception):
    '''Exception raised when an invalid return type is requested'''
