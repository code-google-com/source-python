# ../_libs/messages/base.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   String
from string import Template

# Source.Python Imports
from Source import Engine
from Source import Player
#   Core
from core import GameEngine
from core import GAME_NAME
from core.cvar import ServerVar
#   Filters
from filters.recipients import get_recipients
#   Translations
from translations.strings import TranslationStrings

# Try to import Usermessages for the protobuf system
try:
    from Source import Usermessages
except:
    Usermessages = None


# =============================================================================
# >> CLASSES
# =============================================================================
class _MessageTypes(dict):
    '''Dictionary class used to store UserMessage types with their index'''

    def __init__(self):
        '''Gets all user message indexes and stores them in the dictionary'''

        # Is the protobuf system implemented for the current engine?
        if not Usermessages is None:

            # Import necessary objects
            from configobj import ConfigObj
            from paths import DATA_PATH

            # Get the messages data
            _UserMessageData = ConfigObj(
                DATA_PATH.joinpath('messages', GAME_NAME + '.ini'))

            # Get the class that stores usermessages
            _UserMessageTypes = getattr(
                Usermessages, _UserMessageData['Usermessages'])

            # Get the message names
            _UserMessageNames = dict(zip(
                _UserMessageTypes.names.values(),
                _UserMessageTypes.names.keys()))

            # Loop through all usermessage indexes
            for index in _UserMessageTypes.values:

                # Get the message's full name
                value = _UserMessageNames[_UserMessageTypes.values[index]]

                # Remove the prefix from the message name
                value = value.replace(_UserMessageData['type_prefix'], '')

                # Add the message name and index to the dictionary
                self[value] = index

            # Set the message prefix
            self._message_prefix = _UserMessageData['message_prefix']
            
        # Is the protobuf system not implemented in the current engine?
        else:

            # Set a base value to increment
            index = 0

            # Use a while statement to increment the index
            while True:

                # Get the message name of the current index
                value = Engine.UserMessageOfIndex(index)

                # Is the index invalid?
                if value is None:

                    # Break at this point, since the
                    # last index has been reached
                    break

                # Add the message name and index to the dictionary
                self[value] = index

# Get the _MessageTypes instance
MessageTypes = _MessageTypes()


class BaseMessage(object):
    '''Base message class'''

    def __new__(cls, *args, **kw):
        '''Verifies that the message type exists for the
            current game before returning a class instance'''

        # Get the message type
        index = MessageTypes[cls.__name__]

        # Was the message type found?
        if index == -1:

            # If not, raise an error
            raise NotImplementedError(
                'UserMessage type "%s" is' % cls.__name__ +
                ' not implemented for game "%s"' % GAME_NAME)

        self = object.__new__(cls)
        self.__init__(*args, **kw)

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
        if isinstance(self.message, TranslationStrings):

            # Get all languages and recipient indexes for each language
            recipient_languages = self._get_recipients_per_language(recipients)
            
            # Loop through all languages needed to be sent
            for language in recipient_languages:

                # Get a recipient filter instance for the current recipients
                recipients = get_recipients(*recipient_languages[language])

                # Get the proper message for the current language
                message = self.message.get_string(language, **self.tokens)

                # Send the message
                self._check_send_message(recipients, message)

        # Is the message simply supposed to be sent
        # to all players in the recipient filter?
        else:

            # Get the message
            message = Template(self.message)

            # Add the tokens to the message
            message = message.substitute(self.tokens)

            # Send the message to the recipients
            self._check_send_message(recipients, message)

    def _get_recipients_per_language(self, recipients):
        '''Returns a dictionary of player languages
            with each player index for a language'''

        # Get an instance of RecipientLanguages
        recipient_languages = _RecipientLanguages()

        # Loop through all slots in the given recipient filter
        for slot in range(recipients.GetRecipientCount()):

            # Get the current slot's index
            index = recipients.GetRecipientIndex(slot)

            # Get the player's language
            language = GameEngine.GetClientConVarValue(index, 'cl_language')

            # Get the proper language for the current message for the player
            language = self.message.get_language(language)

            # Was a valid language found?
            if not language is None:

                # Add the index to the player's language's list
                recipient_languages[language].append(index)

        # Return the RecipientLanguages instance
        return recipient_languages

    def _get_player_message(self, index):
        '''Returns the lang string for the current player index'''
        
        # Get the player's language
        language = GameEngine.GetClientConVarValue(index, 'cl_language')

        # Return the proper lang string for the player
        return self.message[language]

    def _get_protobuf_instance(self):
        '''Returns the proper usermessage instance for the usermessage type'''
        return getattr(Usermessages,
            MessageTypes._message_prefix + self.__class__.__name__)()

    def _get_usermsg_instance(self, recipients):
        '''Returns the UserMessage instance base on the engine version'''

        # Is this an older engine?
        if ServerVar('sp_engine_ver').GetInt() < 3:

            # Return using the older version of UserMessageBegin
            return GameEngine.UserMessageBegin(recipients, self._message_index)

        # Return using the newest version of UserMessageBegin
        return GameEngine.UserMessageBegin(
            recipients, self._message_index, None)

    def _check_send_message(self, *args):
        '''Verifies which type of message system should be used to send'''

        # Is the protobuf system not implemented for the current engine?
        if Usermessages is None:

            # Use the base UserMessage system to send the message
            self._send_message(*args)

        # Is the protobuf system implemented for the current engine?
        else:

            # Use the protobuf system to send the message
            self._send_protobuf_message(*args)


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
        self._check_send_message(recipients)


class _RecipientLanguages(dict):
    '''Class used to store languages with player indexes for that language'''

    def __missing__(self, item):
        '''Overrides the __missing__ method to set the given item to a list'''

        # Set the language to a list
        value = self[item] = list()

        # Return the list
        return value
