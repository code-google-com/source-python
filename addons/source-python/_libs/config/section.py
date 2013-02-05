class ConfigSection(object):
    def __init__(self, name):
        self.name = name
        self.text = []
        self.

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, trace_back):
        if exc_type:
            return False
        return True

    def __iter__(self):
        if len(self.text):
            for line in self.text:
                yield line % {'name': self.name}
        else:
            yield self.name
