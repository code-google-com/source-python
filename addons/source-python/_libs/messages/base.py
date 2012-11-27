# ../_libs/messages/base.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Engine
from Source import Player
#   Core
from core import GameEngine
from core.cvar import ServerVar
#   Filters
from filters.recipients import get_recipients


# =============================================================================
# >> CLASSES
# =============================================================================
class _MessageTypes(dict):
    '''Dictionary class used to store UserMessage types with their index'''

    def __missing__(self, item):
        '''Called the first time an item is added to the dictionary'''

        # Get the message's index
        index = Engine.IndexOfUserMessage(item)

        # Was the index not found?
        if index == -1:

            # Return -1 to show the index was not found
            return -1

        # Add the message type to the dictionary with its index
        self[item] = index

        # Return the index
        return index

# Get the _MessageTypes instance
MessageTypes = _MessageTypes()


class BaseMessage(object):
    '''Base message class'''

    def __new__(cls, *args):
        '''Verifies that the message type exists for the
            current game before returning a class instance'''

        # Get the message type
        index = MessageTypes[cls.__name__]

        # Was the message type found?
        if index == -1:

            # If not, raise an error
            raise

        self = object.__new__(cls)
        self.__init__(*args)

        # Set the class' message index
        self._message_index = index

        # Return the class
        return self

    def send(self, users=None):
        '''Called when the message should be sent to users'''

        # Were any users passed?
        if users is None:

            # Use the instance's specified users
            users = self.users

        # Get a recipient filter for the given users
        recipients = get_recipients(users)

        # Does the message contain lang strings?
        if isinstance(self.message, dict):

            # Loop through all items in the recipient filter
            for slot in range(recipients.GetRecipientCount()):

                # Get the index of the current item
                index = recipients.GetRecipientIndex(slot)

                # Get a recipient filter with the current index
                recipients = get_recipients(index)

                # Get the lang string for the current player
                message = self._get_player_message(index)

                # Send the message to the player
                self._send_message(recipients, message)

        # Is the message simply supposed to be sent
        # to all players in the recipient filter?
        else:

            # Send the message to the recipients
            self._send_message(recipients, self.message)

    def _get_player_message(self, index):
        '''Returns the lang string for the current player index'''

        # Get the IPlayerInfo instance for the given index
        player = Player.PlayerOfIndex(index)

        # Get the player's language
        language = GameEngine.GetClientConVarValue(player, 'cl_language')

        # Return the proper lang string for the player
        return self.message[language]


class BaseMessageNoText(BaseMessage):
    '''Base class used for UserMessages that do not send text'''

    def send(self, users=None):
        '''Called when the message should be sent to users'''


        # Were any users passed?
        if users is None:

            # Use the instance's specified users
            users = self.users

        # Get a recipient filter for the given users
        recipients = get_recipients(users)

        # Send the message to the recipients
        self._send_message(recipients)


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def get_usermsg_instance(recipients, message_type):
    '''Returns a UserMessage instance based on the engine version'''

    # Is this an older engine?
    if ServerVar('sp_engine_ver').GetInt() < 3:

        # Return using the older version of UserMessageBegin
        return GameEngine.UserMessageBegin(recipients, message_type)

    # Return using the newest version of UserMessageBegin
    return GameEngine.UserMessageBegin(recipients, message_type, None)
