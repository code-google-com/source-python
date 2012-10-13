# ../_libs/dyncall/base.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Binutils


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
DynCallVM = Binutils.dcGetVM()


DynCallModes = {
    'cdecl': Binutils.DC_CALL_C_DEFAULT,
    'nt': Binutils.DC_CALL_C_X86_WIN32_THIS_MS,
    'linux': Binutils.DC_CALL_C_X86_WIN32_THIS_GNU,
}


DynCallArgs = {
    'b': Binutils.dcArgBool,
    'c': Binutils.dcArgChar,
    's': Binutils.dcArgShort,
    'i': Binutils.dcArgInt,
    'l': Binutils.dcArgLong,
    'f': Binutils.dcArgFloat,
    'd': Binutils.dcArgDouble,
    'p': Binutils.dcArgPointer,
}


DynCallCalls = {
    'v': Binutils.dcCallVoid,
    'b': Binutils.dcCallBool,
    'c': Binutils.dcCallChar,
    's': Binutils.dcCallShort,
    'i': Binutils.dcCallInt,
    'l': Binutils.dcCallLong,
    'f': Binutils.dcCallFloat,
    'd': Binutils.dcCallDouble,
    'p': Binutils.dcCallPointer,
}
