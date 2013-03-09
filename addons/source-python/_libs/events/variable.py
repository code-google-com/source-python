# ../_libs/events/variable.py

# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Store a dictionary to get default values
_DEFAULT_VALUES = {'bool': bool, 'int': int, 'float': float, 'string': str}


# =============================================================================
# >> CLASSES
# =============================================================================
class _EventVariable(object):
    '''Base class used for event variable types'''

    def __init__(self, comment='', default=None):
        '''Called on instantiation'''

        # Was a default value passed?
        if not default is None:

            # Set the default value
            self._default = default

        # Was no default value passed?
        else:

            # Set the default value to the type's default
            self._default = _DEFAULT_VALUES[self._method]()

        # Store the comment
        self._comment = comment

    @property
    def name(self):
        '''Returns the variable type name'''
        return self.__class__.__name__.lower().replace('variable', '')


class BoolVariable(_EventVariable):
    '''Class used to store bool event variables'''
    _method = 'bool'


class ByteVariable(_EventVariable):
    '''Class used to store byte event variables'''
    _method = 'int'


class ShortVariable(_EventVariable):
    '''Class used to store short event variables'''
    _method = 'int'


class LongVariable(_EventVariable):
    '''Class used to store long event variables'''
    _method = 'int'


class FloatVariable(_EventVariable):
    '''Class used to store floating point event variables'''
    _method = 'float'


class StringVariable(_EventVariable):
    '''Class used to store string event variables'''
    _method = 'string'
