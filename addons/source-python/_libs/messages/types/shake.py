# ../_libs/messages/types/shake.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import GameEngine
#   Messages
from messages.base import BaseMessageNoText
from messages.base import MessageTypes


# =============================================================================
# >> CLASSES
# =============================================================================
class Shake(BaseMessageNoText):
    '''Class used to send Shake messages'''

    def __init__(self, amplitude, frequency, duration, users=()):
        '''Initializes the class instance and stores the given values'''

        # Store all the base attributes
        self.amplitude = amplitude
        self.frequency = frequency
        self.duration = duration
        self.users = users

    def _send_message(self, recipients):
        '''Sends the message to the given recipients'''

        # Create the UserMessage
        UserMessage = self._get_usermsg_instance(recipients)

        # Write 0 to the UserMessage
        UserMessage.WriteByte(0)

        # Write the amplitude to the UserMessage
        UserMessage.WriteFloat(self.amplitude)

        # Write 1.0 to the UserMessage
        UserMessage.WriteFloat(1.0)

        # Write the duration to the UserMessage
        UserMessage.WriteFloat(self.duration)

        # Send the message and clean up
        GameEngine.MessageEnd()

    def _send_protobuf_message(self, recipients):
        '''Sends a protobuf message to the given recipients'''

        # Get the usermessage instance
        UserMessage = self._get_protobuf_instance()

        # Set the message's command
        UserMessage.set_command(0)

        # Set the message's amplitude
        UserMessage.set_local_amplitude(self.amplitude)

        # Set the message's frequency
        UserMessage.set_frequency(self.frequency)

        # Set the message's duration
        UserMessage.set_duration(self.duration)

        # Send the message
        GameEngine.SendUserMessage(
            recipients, MessageTypes[self.__class__.__name__], UserMessage)
