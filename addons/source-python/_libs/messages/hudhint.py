# ../_libs/messages/hudhint.py

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
# Get the HintText message type
_MessageType = MessageTypes['HintText']


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def hudhint(users, message):
    '''Sends a hud_hint message to the given players'''

    # Get a RecipientFilter for the given users
    recipients = get_recipients(users)

    # Create the UserMessage
    UserMessage = GameEngine.UserMessageBegin(recipients, _MessageType, None)

    # Write the given string to the UserMessage
    UserMessage.WriteString(message)

    # Send the message and clean up
    GameEngine.MessageEnd()
