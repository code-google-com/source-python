# ../_libs/auth/paths.py

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python imports
from paths import ADDON_PATH as _ADDON_PATH
from paths import CFG_PATH as _CFG_PATH


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Store the path to the auth providers
AUTH_PROVIDER_PATH = _ADDON_PATH.joinpath('_libs', 'auth', 'providers')

# Store the path to the auth configurations
AUTH_CFG_PATH = _CFG_PATH.joinpath('auth_providers')

# Add all paths to __all__
__all__ = [x for x in globals() if x.isupper() and not x.startswith('_')]
