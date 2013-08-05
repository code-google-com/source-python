# ../_libs/auth/paths.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python imports
from paths import ADDON_PATH
from paths import CFG_PATH


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Store the path to the auth providers
AUTH_PROVIDER_PATH = ADDON_PATH.joinpath('_libs', 'auth', 'providers')

# Store the path to the auth configurations
AUTH_CFG_PATH = CFG_PATH.joinpath('auth_providers')
