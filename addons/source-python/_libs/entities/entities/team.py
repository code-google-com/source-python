# ../_libs/entities/entities/team.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Configobj
from configobj import ConfigObj

# Source.Python Imports
from core import GAME_NAME
from paths import DATA_PATH
#   Entities
from entities.entity import BaseEntity


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the path to the game's team ini file
_ini_file = DATA_PATH.joinpath('teams', GAME_NAME + '.ini')

# Does the file exist?
if _ini_file.isfile():

    # Get the ConfigObj instance of the file
    _ini = ConfigObj(_ini_file)

    # Store the team manager
    team_manager = _ini['manager']

# Does the file not exist?
else:

    # Store the team manager as None for comparison
    team_manager = None


# =============================================================================
# >> CLASSES
# =============================================================================
class TeamEntity(BaseEntity):
    '''Class used to interact directly with team entites'''

    def __init__(self, index):
        '''Override the __init__ method to add "team" to the _game_inis list'''

        # Run the inherited class __init__ method
        super(TeamEntity, self).__init__(index)

        # Add "team" to the _game_inis list
        self._game_inis.append('team')

    @classmethod
    def _is_valid_index_for_entity_type(cls, edict):
        '''Verifies that the given edict is of a team entity'''

        # Return whether the given edict is one of a team entity?
        return edict.GetClassName() == team_manager
