# ../_libs/messages/hudhint.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from core import GameEngine
#   Filters
from filters.recipients import GetRecipients
#   Messages
from messages._base import MessageTypes


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the HintText message type
_MessageType = MessageTypes['HintText']


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def HudHint(users, message):
    '''Sends a HudHint message to the given players'''

    # Get a RecipientFilter for the given users
    Recipients = GetRecipients(users)

    # Create the UserMessage
    UserMessage = GameEngine.UserMessageBegin(Recipients, _MessageType, None)

    # Write the given string to the UserMessage
    UserMessage.WriteString(message)

    # Send the message and clean up
    GameEngine.MessageEnd()
