# ../_libs/messages/type/hinttext.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import GameEngine
#   Messages
from messages.base import BaseMessage
from messages.base import get_usermsg_instance


# =============================================================================
# >> CLASSES
# =============================================================================
class HintText(BaseMessage):
    '''Class used to send HintText messages'''

    def __init__(self, message, users=()):
        '''Initializes the class instance and stores the given values'''

        # Store all the base attributes
        self.message = message
        self.users = users

    def _send_message(self, recipients, message):
        '''Sends the message to the given recipients'''

        # Create the UserMessage
        UserMessage = get_usermsg_instance(recipients, self._message_index)

        # Write the message to the UserMessage
        UserMessage.WriteString(message)

        # Send the message to the recipients
        GameEngine.MessageEnd()
