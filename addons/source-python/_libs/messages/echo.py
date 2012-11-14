# ../_libs/messages/echo.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from core import GameEngine
#   Filters
from filters.recipients import get_recipients
#   Messages
from messages._base import MessageTypes


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the TextMsg message type
_MessageType = MessageTypes['TextMsg']


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def echo(users, message):
    '''Sends an echo message to the given players' console'''

    # Get a RecipientFilter for the given users
    recipients = get_recipients(users)

    # Create the UserMessage
    UserMessage = GameEngine.UserMessageBegin(recipients, _MessageType, None)

    # Write 2 (echo) to the UserMessage
    UserMessage.WriteByte(2)

    # Write the given string to the UserMessage
    UserMessage.WriteString(message)

    # Send the message and clean up
    GameEngine.MessageEnd()
