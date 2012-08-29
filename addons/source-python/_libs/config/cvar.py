from config.attributes import ListManager


class CvarManager(object):
    def __init__(self, name, default, text):
        self.name = name
        self.default = default
        self.text = text
        self.CvarText = _CvarTextManager()

    def __iter__(self):
        if len(self.CvarText):
            for line in self.C

class _CvarTextManager(dict):
    def __init__(self):
        self.order = []

    def __getitem__(self, item):
        if item in self:
            return super(_CvarTextManager, self).__getitem__(item)
        value = self[item] = ListManager(item)
        self.order.append(item)
        return value

    def __iter__(self):
        for item in self.order:
            yield self[item]
