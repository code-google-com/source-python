class ListManager(list):
    def __init__(self, name):
        self.name = name
        self.header = ''
        self.first_indent = ''
        self.indent = 0
