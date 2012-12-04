# ../_libs/messages/types/textmsg.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import GameEngine
#   Messages
from messages.base import BaseMessage


# =============================================================================
# >> CLASSES
# =============================================================================
class TextMsg(BaseMessage):
    '''Class used to send TextMsg messages'''

    # Store the TextMsg types
    Echo = 2
    CenterMsg = 4

    def __init__(self, message, type=0, users=(), tokens={}):
        '''Initializes the class instance and stores the given values'''

        # Store all the base attributes
        self.message = message
        self.type = type
        self.users = users
        self.tokens = tokens

    def _send_message(self, recipients, message):
        '''Sends the message to the given recipients'''

        # Create the UserMessage
        UserMessage = self._get_usermsg_instance(recipients)

        # Write the message type to the UserMessage
        UserMessage.WriteByte(self.type)

        # Write the message to the UserMessage
        UserMessage.WriteString(message)

        # Send the message to the recipients
        GameEngine.MessageEnd()
