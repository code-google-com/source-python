# ../_libs/messages/types/shake.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import GameEngine
#   Messages
from messages.base import BaseMessageNoText


# =============================================================================
# >> CLASSES
# =============================================================================
class Shake(BaseMessageNoText):
    '''Class used to send Shake messages'''

    def __init__(self, magnitude, time, users=()):
        '''Initializes the class instance and stores the given values'''

        # Store all the base attributes
        self.magnitude = magnitude
        self.time = time
        self.users = users

    def _send_message(self, recipients):
        '''Sends the message to the given recipients'''

        # Create the UserMessage
        UserMessage = self._get_usermsg_instance(recipients)

        # Write 0 to the UserMessage
        UserMessage.WriteByte(0)

        # Write the magnitude to the UserMessage
        UserMessage.WriteFloat(self.magnitude)

        # Write 1.0 to the UserMessage
        UserMessage.WriteFloat(1.0)

        # Write the time to the UserMessage
        UserMessage.WriteFloat(self.time)

        # Send the message and clean up
        GameEngine.MessageEnd()

    def _send_protobuf_message(self, recipients, message):
        UserMessage = self._get_protobuf_instance()
        UserMessage.set_command(0)
        UserMessage.set_local_amplitude(self.magnitude)
        UserMessage.set_frequency(1.0)
        UserMessage.set_duration(self.time)
        GameEngine.SendUserMessage(
            recipients, MessageTypes[self.__class__.__name__], UserMessage)
