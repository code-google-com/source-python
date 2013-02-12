# ../_libs/config/manager.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from paths import CFG_PATH
#   Config
from config.cvar import CvarManager
from config.section import SectionManager
from config.command import CommandManager
#   Core
from core import GameEngine
from core.excepthook import ExceptHooks
#   Translations
from translations.manager import LanguageManager
from translations.strings import LangStrings
from translations.strings import TranslationStrings


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the config language strings
_config_strings = LangStrings('_core/config_strings')


# =============================================================================
# >> CLASSES
# =============================================================================
class ConfigManager(object):
    '''Config Management class used to create a config file'''

    def __init__(self, filepath, indention=3, max_line_length=80):
        '''Called on instanciation'''

        # Store the primary attributes
        self.filepath = filepath
        self.indention = indention
        self.max_line_length = max_line_length

        # Store the header and separator
        self.header = ''
        self.separator = '#'

        # Store the section types
        self._cvars = set()
        self._commands = set()

        # Store the section list
        self._sections = list()

    def __enter__(self):
        '''Used when using "with" context management to create the file'''
        return self

    @property
    def fullpath(self):
        '''Returns the "path" instance of the full path to the file'''
        return CFG_PATH.joinpath(self.filepath + '.cfg')

    def cvar(
            self, name, default='0', flags=0,
            description='', min_value=None, max_value=None):
        '''Adds/returns a cvar instance to add to the config file'''

        # Get the CvarManager instance for the given arguments
        section = CvarManager(
            name, default, flags, description, min_value, max_value)

        # Add the cvar to the list of cvars
        self._cvars.add(name)

        # Add the CvarManager instance to the list of sections
        self._sections.append(section)

        # Return the CvarManager instance
        return section

    def section(self, name, separator='#'):
        '''Adds/returns a section instance to add to the config file'''

        # Get the SectionManager instance for the given arguments
        section = SectionManager(name, separator)

        # Add the SectionManager instance to the list of sections
        self._sections.append(section)

        # Return the SectionManager instance
        return section

    def command(self, name, description=''):
        '''Adds/returns a command instance to add to the config file'''

        # Get the CommandManager instance for the given arguments
        section = CommandManager(name, description)

        # Add the command to the list of commands
        self._commands.add(name)

        # Add the CommandManager instance to the list of sections
        self._sections.append(section)

        # Return the CommandManager instance
        return section

    def text(self, text):
        '''Adds text to the config file'''
        self._sections.append(text)

    def __exit__(self, exctype, value, trace_back):
        '''Used when exiting "with" context management to create file'''

        # Was an exception raised?
        if trace_back:

            # Print the exception
            ExceptHooks.print_exception(exctype, value, trace_back)

            # Return
            return False

        # Write the file
        self.write()

        # Execute the file
        self.execute()

        # Return
        return True

    def write(self):
        '''Writes the config file'''

        # Get any old values from the existing file
        _old_config = self._parse_old_file()

        # Is the indention too small?
        if self.indention < 3:

            # Set the indention to the lowest amount
            self.indention = 3

        # Do all directories to the file exist?
        if not self.fullpath.parent.isdir():

            # Create the directories
            self.fullpath.parent.makedirs()

        # Open/close the file to write to it
        with self.fullpath.open('w') as open_file:

            # Get the number of spaces to indent after //
            spaces = ' ' * (self.indention - 2)

            # Is there a header for the file?
            if self.header:

                # Get the length of the header's separator
                length = len(self.separator)

                # Get the number of times to repeat the separator
                times, remainder = divmod(
                    self.max_line_length - (2 * self.indention), length)

                # Get the string separator value
                separator = (
                    '//' + spaces + self.separator * times +
                    self.separator[:remainder] + spaces + '//\n')

                # Write the separator
                open_file.write(separator)

                # Get the header's translation
                header = self._get_translation(self.header)

                # Loop through each line in the header
                for lines in header.splitlines():

                    # Loop through the current line to get valid
                    # lines with length less than the max line length
                    for line in self._get_lines(lines):

                        # Strip the // and new line characters from the line
                        line = line.lstrip('/ ').replace('\n', '')

                        # Write the current line
                        open_file.write(
                            '//%s//\n' % line.center(self.max_line_length - 4))

                # Write the separator to end the header
                open_file.write(separator)

            # Loop through all sections in the file
            for section in self._sections:

                # Is the current section a Cvar?
                if isinstance(section, CvarManager):

                    # Has any text been added to the file?
                    if open_file.tell():

                        # If so, add a blank line prior to section
                        open_file.write('\n')

                    # Loop through all lines in the section
                    for lines, indent in section:

                        # Get the current line's translation
                        lines = self._get_translation(lines)

                        # Loop through the current line to get valid
                        # lines with length less than the max line length
                        for line in self._get_lines(lines, indent):

                            # Write the current line
                            open_file.write(line)

                    # Write the cvar's default value
                    open_file.write(
                        '//' + spaces + _config_strings['Default'].get_string(
                        LanguageManager.default) + ' %s\n' % section.default)

                    # Get the cvar's description language string
                    description = self._get_translation(section.description)

                    # Loop through the description to get valid
                    # lines with length less than the max line length
                    for line in self._get_lines(description):

                        # Write the current line
                        open_file.write(line)

                    # Does the cvar exist in the old config file?
                    if section.name in _old_config:

                        # Write the old config file's value
                        open_file.write(
                            ' ' * self.indention +
                            _old_config[section.name][0] + '\n')

                        # Remove the cvar from the old config file dictionary
                        del _old_config[section.name]

                    # Does the cvar not exist in the old config file?
                    else:

                        # Write the cvar line using the default value
                        open_file.write(
                            ' ' * self.indention +
                            section.name + ' %s\n' % section.default)

                # Is the current section a Section?
                elif isinstance(section, SectionManager):

                    # Has any text been added to the file?
                    if open_file.tell():

                        # If so, add a blank line prior to section
                        open_file.write('\n')

                    # Get the length of the section's separator
                    length = len(section.separator)

                    # Get the number of times to repeat the separator
                    times, remainder = divmod(
                        self.max_line_length - (2 * self.indention), length)

                    # Get the string separator value
                    separator = (
                        '//' + spaces + section.separator * times +
                        section.separator[:remainder] + spaces + '//\n')

                    # Write the separator
                    open_file.write(separator)

                    # Get the section's translation
                    name = self._get_translation(section.name)

                    # Loop through each line in the section
                    for lines in name.splitlines():

                        # Loop through the current line to get valid
                        # lines with length less than the max line length
                        for line in self._get_lines(lines):

                            # Strip the // from the line and remove newline
                            line = line.lstrip('/ ').replace('\n', '')

                            # Write the current line
                            open_file.write(
                                '//%s//\n' %
                                line.center(self.max_line_length - 4))

                    # Write the separator to end the section
                    open_file.write(separator)

                # Is the current section a Command?
                elif isinstance(section, CommandManager):

                    # Has any text been added to the file?
                    if open_file.tell():

                        # If so, add a blank line prior to section
                        open_file.write('\n')

                    # Does the command have a description?
                    if section.description:

                        # Get the description's translation
                        description = self._get_translation(
                            section.description)

                        # Loop through description to get valid lines
                        # with length less than the max line length
                        for line in self._get_lines(description):

                            # Write the current line
                            open_file.write(line + '\n')

                    # Does the command exist in the old config file?
                    if section.name in _old_config:

                        # Loop through each line in the
                        # old config for the command
                        for line in _old_config[section.name]:

                            # Write the line to the file
                            open_file.write(line + '\n')

                        # Remove the command from the old config
                        del _old_config[section.name]

                # Is the current section just text?
                else:

                    # Get the translation for the text
                    lines = self._get_translation(section)

                    # Loop through the current line to get valid
                    # lines with length less than the max line length
                    for line in self._get_lines(lines):

                        # Write the current line
                        open_file.write(line)

            # Are there any more values not used from the old config file?
            if _old_config:

                # Add a blank line
                open_file.write('\n')

                # Loop through the items in the old config
                for name in sorted(_old_config):

                    # Loop through each line for the current item
                    for line in _old_config[name]:

                        # Write the line to the config file
                        open_file.write('// %s\n' % line)

    def execute(self):
        '''Executes the config file'''
        GameEngine.ServerCommand('exec source-python/%s\n' % self.filepath)

    def _parse_old_file(self):
        '''Parses the old config file to get any values already set'''

        # Get the _OldConfig instance
        _old_config = _OldConfig()

        # Does the file exist?
        if not self.fullpath.isfile():

            # If not, simply return the empty dictionary
            return _old_config

        # Open/close the file
        with self.fullpath.open() as open_file:

            # Get all lines from the file
            _all_lines = [line.strip() for line in open_file.readlines()]

        # Loop through each line in the old config
        for line in _all_lines:

            # Is the line a command or cvar?
            if line.startswith('//') or not line:

                # If not, continue to the next line
                continue

            # Get the command's or cvar's name
            name = line.split(' ', 1)[0]

            # Is the command/cvar valid, but have to value/arguments?
            if name in self._commands | self._cvars and not line.count(' '):

                # If not, continue to the next line
                continue

            # Make sure the line has the proper number of quotes
            line = line + ('"' if line.count('"') % 2 else '')

            # Add the line to the old config
            _old_config[name].append(line)

        # Return the dictionary
        return _old_config

    def _get_lines(self, lines, indention=0):
        '''Yields lines that are less than the file's max line length'''

        # Get the first line and the remainder
        first_line, remainder = self._get_line(
            '//' + ' ' * (self.indention - 2) + lines)

        # Does the line exist?
        if first_line.strip('/ '):

            # Yield the line
            yield first_line + '\n'

        # Is there no text in the line?
        else:

            # Yield an empty line
            yield '\n'

        # Use "while" statement to yield all lines less than file's max length
        while remainder:

            # Get the current line and the remainder
            current_line, remainder = self._get_line(
                '//' + ' ' * (self.indention if not indention
                else indention - 2) + remainder)

            # Does the line exist?
            if current_line.strip('/ '):

                # Yield the line
                yield current_line + '\n'

            # Is there not text in the line?
            else:

                # Yield an empty line
                yield '\n'

    def _get_line(self, line):
        '''Returns a line with less than the
            file's max length and the remainder'''

        # Get the first line
        start = the_line = line.splitlines()[0]

        # Get the remainder
        remainder = line.splitlines()[1:]

        # Is the first line less than the file's max length?
        if len(start) < self.max_line_length:

            # Return the line and the remainder
            return start, '\n'.join(remainder)

        # Use "while" statement to find a "space" to split from
        while start[~0] != ' ' and start:

            # Move the end of the line down one spot
            start = start[:~0]

        # Is there any text in the line?
        if not start.strip(' '):

            # If not, set the line to the original line
            start = the_line

        # Get the remainder
        remainder = line.split(start, 1)[1]

        # Return the line and the remainder
        return start, remainder

    @staticmethod
    def _get_translation(text):
        '''Returns the proper language string for the given text'''

        # Is the given text a TranslationStrings instance?
        if isinstance(text, TranslationStrings):

            # Return the server's language string
            return text.get_string(LanguageManager.default)

        # Is the given text just a string?
        if isinstance(text, str):

            # Return the text
            return text

        # Raise an error if the text is not a
        # string or TranslationStrings instance
        raise TypeError(
            'Unsupported type "%s" for config text' % type(text).__name__)


class _OldConfig(dict):
    '''Dictionary class used to store values from the old config file'''

    def __missing__(self, item):
        '''Define __missing__ to add the item as an empty list'''

        # Add the item as an empty list
        value = self[item] = list()

        # Return the list
        return value