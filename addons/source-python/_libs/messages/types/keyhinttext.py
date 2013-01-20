# ../_libs/messages/types/keyhinttext.py

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
class KeyHintText(BaseMessage):
    '''Class used to send KeyHintText messages'''

    def __init__(self, message, users=(), tokens={}):
        '''Initializes the class instance and stores the given values'''

        # Store all the base attributes
        self.message = message
        self.users = users
        self.tokens

    def _send_message(self, recipients, message):
        '''Sends the message to the given recipients'''

        # Create the UserMessage
        UserMessage = self._get_usermsg_instance(recipients)

        # Write the message to the UserMessage
        UserMessage.WriteString(message)

        # Send the message to the recipients
        GameEngine.MessageEnd()
