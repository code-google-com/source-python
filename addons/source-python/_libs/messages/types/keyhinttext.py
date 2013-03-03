# ../_libs/messages/types/keyhinttext.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import GameEngine
#   Messages
from messages.base import BaseMessage
from messages.base import MessageTypes


# =============================================================================
# >> CLASSES
# =============================================================================
class KeyHintText(BaseMessage):
    '''Class used to send KeyHintText messages'''

    def __init__(self, message, users=(), **tokens):
        '''Initializes the class instance and stores the given values'''

        # Store all the base attributes
        self.message = message
        self.users = users
        self.tokens = tokens

    def _send_message(self, recipients, message):
        '''Sends the message to the given recipients'''

        # Create the UserMessage
        UserMessage = self._get_usermsg_instance(recipients)

        # Write the message to the UserMessage
        UserMessage.WriteString(message)

        # Send the message to the recipients
        GameEngine.MessageEnd()

    def _send_protobuf_message(self, recipients, message):
        '''Sends a protobuf message to the given recipients'''

        # Get the usermessage instance
        UserMessage = self._get_protobuf_instance()

        # Set the message's text
        UserMessage.add_hints(message)

        # Send the message
        GameEngine.SendUserMessage(
            recipients, MessageTypes[self.__class__.__name__], UserMessage)
