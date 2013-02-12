# ../_libs/config/command.py


# =============================================================================
# >> CLASSES
# =============================================================================
class CommandManager(object):
    '''Class used to store a command instance'''

    def __init__(self, name, description):
        '''Called on instanciation'''

        # Store the base attributes for the command
        self.name = name
        self.description = description
