# ../_libs/messages/types/textmsg.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from core import GameEngine
#   Messages
from messages.base import BaseMessage
from messages.base import MessageTypes


# =============================================================================
# >> CLASSES
# =============================================================================
class TextMsg(BaseMessage):
    '''Class used to send TextMsg messages'''

    # Store the TextMsg destinations
    Echo = 2
    CenterMsg = 4

    def __init__(self, message, destination=0, users=(), **tokens):
        '''Initializes the class instance and stores the given values'''

        # Store all the base attributes
        self.message = message
        self.destination = destination
        self.users = users
        self.tokens = tokens

    def _send_message(self, recipients, message):
        '''Sends the message to the given recipients'''

        # Create the UserMessage
        UserMessage = self._get_usermsg_instance(recipients)

        # Write the message destination to the UserMessage
        UserMessage.WriteByte(self.destination)

        # Write the message to the UserMessage
        UserMessage.WriteString(message)

        # Send the message to the recipients
        GameEngine.MessageEnd()

    def _send_protobuf_message(self, recipients, message):
        '''Sends a protobuf message to the given recipients'''

        # Get the usermessage instance
        UserMessage = self._get_protobuf_instance()

        # Set the message's destination
        UserMessage.set_msg_dst(self.destination)

        # Set the message's text
        UserMessage.set_params(message)

        # Send the message
        GameEngine.SendUserMessage(
            recipients, MessageTypes[self.__class__.__name__], UserMessage)
