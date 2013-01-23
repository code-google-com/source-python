# ../_libs/core/commands.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import GameEngine


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def echo_console(text):
    '''echos a message to the server's console'''

    # Loop through each line in the text
    for line in text.split('\n'):

        # Echo the message
        GameEngine.ServerCommand('echo "%s"\n' % line.replace('"', "'"))
