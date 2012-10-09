# ../_libs/messages/chat.py

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
# Get the SayText2 message type
_MessageType = MessageTypes['SayText2']

_HexChars = ('\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07')


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def chat(users, message, index=0):
    '''Sends a chat message to the given players'''

    # Get a RecipientFilter for the given users
    recipients = get_recipients(users)

    # Create the UserMessage
    UserMessage = GameEngine.UserMessageBegin(recipients, _MessageType, None)

    # Write the given index to the UserMessage
    UserMessage.WriteByte(index)

    # Does the message startwith a hex character?
    if not message.startswith(_HexChars):

        # Add \x01 to the start of the message
        message = '\x01' + message

    # Write the given string to the UserMessage
    UserMessage.WriteString(message)

    # Send the message and clean up
    GameEngine.MessageEnd()
