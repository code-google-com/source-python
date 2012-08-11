# ../_libs/messages/shake.py

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
# Get the Shake message type
_MessageType = MessageTypes['Shake']


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def Shake(users, magnitude, time):
    '''Sends a shake message to the given players to shake their screen'''

    # Get a RecipientFilter for the given users
    Recipients = GetRecipients(users)

    # Create the UserMessage
    UserMessage = GameEngine.UserMessageBegin(Recipients, _MessageType, None)

    # Write 0 to the UserMessage
    UserMessage.WriteByte(0)

    # Write the magnitude to the UserMessage
    UserMessage.WriteFloat(magnitude)

    # Write 1.0 to the UserMessage
    UserMessage.WriteFloat(1.0)

    # Write the time to the UserMessage
    UserMessage.WriteFloat(time)

    # Send the message and clean up
    GameEngine.MessageEnd()
