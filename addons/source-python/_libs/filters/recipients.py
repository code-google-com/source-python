# ../_libs/filters/recipients.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from Source import Shared
#   Filters
from filters.players import PlayerIter


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def get_recipients(*users):
    '''Returns a RecipientFilter for the given users'''

    # Was a RecipientFilter passed?
    if len(users) and type(users[0]).__name__ == 'MRecipientFilter':

        # Simply return the given filter
        return users[0]

    # Create a RecipientFilter
    recipients = Shared.MRecipientFilter()

    # Were any users specified?
    if not len(users):

        # Add all players
        recipients.AddAllPlayers()

    # Was a list of indexes given?
    elif isinstance(users[0], int):

        # Loop through all indexes given
        for index in users:

            # Add the index to the filter
            recipients.AddRecipient(index)

    # Was a PlayerIter instance passed?
    elif isinstance(users[0], PlayerIter):

        # Loop through all PlayerIter indexes
        for index in users[0]:

            # Add the index to the filter
            recipients.AddRecipient(index)

    # Is this a PlayerIter filter?
    else:

        # Was a string filter passed as the users argument?
        if isinstance(users, str):

            # Convert the users to a list
            users = [users]

        # Loop through all players in the PlayerIter object
        for index in PlayerIter(users[0], users[1] if len(users) >= 2 else []):

            # Add the index to the filter
            recipients.AddRecipient(index)

    # Return the RecipientFilter
    return recipients
