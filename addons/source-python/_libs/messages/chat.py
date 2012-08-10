# ../_libs/messages/chat.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from core import GameEngine
#   Filters
from filters.recipients import RecipientFilter
#   Messages
from messages._base import MessageTypes


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the SayText2 message type
_MessageType = MessageTypes['SayText2']


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def Chat(users, message, index=0):
    '''Sends a chat message to the given players'''

    # Get a RecipientFilter for the given users
    Recipients = RecipientFilter.GetRecipients(users)

    # Create the UserMessage
    UserMessage = GameEngine.UserMessageBegin(Recipients, _MessageType, None)

    # Write the given index to the UserMessage
    UserMessage.WriteByte(index)

    # Write the given string to the UserMessage
    UserMessage.WriteString(message)

    # Send the message and clean up
    GameEngine.MessageEnd()
