# ../_libs/config/config.py

# =============================================================================
# >> IMPORTS
# =============================================================================
from os.path import join

from Source import ServerCommand
from core.excepthook import ExceptHooks
from config.command import CommandManager
from config.cvar import CvarManager
from config.section import SectionManager


# =============================================================================
# >> CLASSES
# =============================================================================
class ConfigManager(object):
    def __init__(self, filepath, indention=3, max_line_length=80):
        self.filepath = filepath
        self.indention = indention
        self.header = ''
        self.max_line_length = max_line_length
        self._cvars = set()
        self._commands = set()

    def __enter__(self):
        self._sections = list()
        return self

    def ConfigCvar(self, name, default=0, text=''):
        section = CvarManager(name, default, text)
        self._cvars.add(name)
        self._sections.append(section)
        return section

    def ConfigSection(self, name):
        section = SectionManager(name)
        self._sections.append(section)
        return section

    def ConfigCommand(self, name):
        section = CommandManager(name)
        self._commands.add(name)
        self._sections.append(section)
        return section

    def __exit__(self, exctype, value, trace_back):
        if trace_back:
            ExceptHooks.PrintException(exctype, value, trace_back)
            return False

        _old_config = self._ParseOldFile()

        with open(self.fullpath, 'w') as open_file:
            open_file.write(self.header + '\n')
            for section in self._sections:
                for line in section:
                    for fixed_line in self._FixLines(line):
                        open_file.write(line + '\n')
            if _old_config:
                open_file.write('\n')
            for name in sorted(_old_config):
                for line in _old_config[name]:
                    open_file.write('// %s\n' % line)

    def _ParseOldFile(self):
        if not isfile(self.fullpath):
            return {}

        with open(self.fullpath) as open_file:
            _all_lines = [line.strip() for line in open_file.readlines()]
        _old_config = {}
        for line in _all_lines:
            if line.startswith('//') or not line:
                continue
            name = line.split(' ', 1)[0]
            if name in self._commands | self._cvars and not line.count(' '):
                continue
            line = line + ('"' if line.count('"') % 2 else '')
            if not name in _old_config:
                _old_config[name] = []
            if not line in _old_config[name]:
                _old_config[name].append(line)

    def Execute(self):
        ServerCommand('exec %s' % join('source-python', self.filepath))

    @property
    def fullpath(self):
        return join(CFG_PATH, self.filepath)
