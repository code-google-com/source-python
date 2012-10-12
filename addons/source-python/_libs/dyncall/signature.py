# ../_libs/dyncall/signature.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   OS
from os import name as os_name
if os_name != 'nt':
    os_name = 'linux'

# Source.Python Imports
from Source import Binutils
#   DynCall
from dyncall.base import DynCallArgs
from dyncall.base import DynCallCalls
from dyncall.base import DynCallModes
from dyncall.modules import ModuleData


# =============================================================================
# >> CLASSES
# =============================================================================
class Signature(object):
    '''Class used to call a dynamic function'''

    def __init__(self, ini):
        '''Called when the instance is initializes'''

        # Get the functions return type
        return_type = ini['return_type']

        # Is this a proper return type?
        if not return_type in DynCallCalls:

            # Raise an error about the return type
            raise ValueError('Unknown return type "%s"' % return_type)

        # Get the module instance
        module = ModuleData[ini['module']]

        # Is the server running on Windows?
        if os_name == 'nt':

            # Get the address of the signature
            self.address = Binutils.FindSignature(
                module, ini['sig'], len(ini['sig']))

        # Is the server not running on Windows?
        else:

            # Get the address of the symbol
            self.address = Binutils.FindSymbol(module, ini['symbol'])

        # Store the arguments, return type, and convention
        self.arguments = ini['arguments']
        self.return_type = return_type
        self.convention = DynCallModes.get(
            ini['convention'], DynCallModes[os_name])

    def call_function(self, *args):
        '''Calls the function with the given arguments'''

        # Were the correct number of arguments passed?
        if len(args) != len(self.arguments):

            # Raise an error about the number of arguments passed
            raise ValueError(
                'Given arguments (%s) do not match' % len(args) +
                ' required arguments (%s)' % len(self.arguments))

        # Reset the vm
        Binutils.dcReset(DynCallVM)

        # Set the mode to the functions convention
        Binutils.dcMode(self.convention)

        # Loop through all arguments
        for index in range(len(args)):

            # Is the current argument a known argument type?
            if self.arguments[index] in DynCallArgs:

                # Push the argument on the stack
                DynCallArgs[self.arguments[index]](args[index])

            # Is the current argument of an unknown type?
            else:

                # Raise an error about the argument type
                raise ValueError(
                    'Unknown argument type "%s"' % self.arguments[index])

        # Call the function
        DynCallCalls[self.return_type](DynCallVM, self.address)
