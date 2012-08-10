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
# Get the Fade message type
_MessageType = MessageTypes['Fade']


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def Fade(users, fade_type, fade_time, hold_time, red, green, blue, alpha=255):
    '''
        Sends a fade message to the given players to fade their screen in/out
    '''

    # Get a RecipientFilter for the given users
    Recipients = RecipientFilter.GetRecipients(users)

    # Create the UserMessage
    UserMessage = GameEngine.UserMessageBegin(Recipients, _MessageType, None)

    # Write the fade time to the UserMessage
    UserMessage.WriteShort(fade_time)

    # Write the hold time to the UserMessage
    UserMessage.WriteShort(hold_time)

    # Write the fade type to the UserMessage
    UserMessage.WriteShort(fade_type)

    # Write the red value to the UserMessage
    UserMessage.WriteByte(red)

    # Write the green value to the UserMessage
    UserMessage.WriteByte(green)

    # Write the blue value to the UserMessage
    UserMessage.WriteByte(blue)

    # Write the alpha value to the UserMessage
    UserMessage.WriteByte(alpha)

    # Send the message and clean up
    GameEngine.MessageEnd()
