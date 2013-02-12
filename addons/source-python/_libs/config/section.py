# ../_libs/config/section.py


# =============================================================================
# >> CLASSES
# =============================================================================
class SectionManager(object):
    '''Class used to store a section instance'''

    def __init__(self, name, separator):
        '''Called on instanciation'''

        # Store the base attributes for the section
        self.name = name
        self.separator = separator
