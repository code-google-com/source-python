# ../_libs/entities/helpers.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Engine


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def index_from_edict(edict):
    '''Returns an index from the given edict'''
    return Engine.IndexOfEdict(edict)


def index_from_basehandle(bhandle):
    '''Returns an index from the given BaseHandle instance'''
    return bhandle.GetEntryIndex()


def index_from_inthandle(ihandle):
    '''Returns an index from the given handle in int form'''
    return Engine.IndexOfIntHandle(ihandle)


def index_from_pointer(pointer):
    '''Returns an index from the given BaseEntity pointer'''
    return Engine.IndexOfPointer(pointer)


def edict_from_index(index):
    '''Returns an edict from the given index'''
    return Engine.PEntityOfEntIndex(index)


def edict_from_basehandle(bhandle):
    '''Returns an edict from the given BaseHandle instance'''
    return edict_from_index(index_from_basehandle(bhandle))


def edict_from_inthandle(ihandle):
    '''Returns an edict from the given handle in int form'''
    return edict_from_index(index_from_inthandle(ihandle))


def edict_from_pointer(pointer):
    '''Returns an edict from the given BaseEntity pointer'''
    return edict_from_index(index_from_pointer(pointer))


def basehandle_from_index(index):
    '''Returns a BaseHandle instance from the given index'''
    return basehandle_from_edict(edict_from_index(index))


def basehandle_from_edict(edict):
    '''Returns a BaseHandle instance from the given edict'''
    return edict.GetNetworkable().GetEntityHandle().GetRefEHandle()


def basehandle_from_inthandle(ihandle):
    '''Returns a BaseHandle instance from the given handle in int form'''
    return basehandle_from_edict(edict_from_inthandle(ihandle))


def basehandle_from_pointer(pointer):
    '''Returns a BaseHandle instance from the given BaseEntity pointer'''
    return basehandle_from_edict(edict_from_pointer(pointer))


def inthandle_from_index(index):
    '''Returns a handle in int form from the given index'''
    return inthandle_from_basehandle(basehandle_from_index(index))


def inthandle_from_edict(edict):
    '''Returns a handle in int form from the given edict'''
    return inthandle_from_basehandle(basehandle_from_edict(edict))


def inthandle_from_basehandle(bhandle):
    '''Returns a handle in int form from the given BaseHandle instance'''
    return bhandle.ToInt()


def inthandle_from_pointer(pointer):
    '''Returns a handle in int form from the given BaseEntity pointer'''
    return inthandle_from_basehandle(basehandle_from_pointer(pointer))


def pointer_from_index(index):
    '''Returns a BaseEntity pointer from the given index'''
    return pointer_from_edict(edict_from_index(index))


def pointer_from_edict(edict):
    '''Returns a BaseEntity pointer from the given edict'''
    return edict.GetUnknown().GetBaseEntity()


def pointer_from_basehandle(bhandle):
    '''Returns a BaseEntity pointer from the given BaseHandle instance'''
    return pointer_from_edict(edict_from_basehandle(bhandle))


def pointer_from_inthandle(ihandle):
    '''Returns a BaseEntity pointer from the given handle in int form'''
    return pointer_from_edict(edict_from_inthandle(ihandle))
