# ./_libs/filters/recipients.py

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
def GetRecipients(*users):
    '''Returns a RecipientFilter for the given users'''

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

    # Is this a PlayerIter filter?
    else:

        # Loop through all players in the PlayerIter object
        for index in PlayerIter(*users):

            # Add the index to the filter
            recipients.AddRecipient(index)

    # Return the RecipientFilter
    return recipients
