# ../_libs/core/decorators.py


# =============================================================================
# >> CLASSES
# =============================================================================
class BaseDecorator(object):
    '''Decorator class used to make sure all decorators are
        unregistered when the addon that registered them is unloaded'''
