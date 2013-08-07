# ../sp.py

'''
    ===========================================================================
    Source Python
    Copyright (C) 2012 Source Python Development Team.  All rights reserved.
    ===========================================================================

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License, version 3.0, as
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along
    with this program.  If not, see <http://www.gnu.org/licenses/>.

    As a special exception, the Source.Python Team gives you permission
    to link the code of this program (as well as its derivative works) to
    "Half-Life 2," the "Source Engine," and any Game MODs that run on software
    by the Valve Corporation.  You must obey the GNU General Public License in
    all respects for all other code used.  Additionally, the Source.Python
    Development Team grants this exception to all derivative works.
'''

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
from cvar_c import CConVar
from _core.settings import _CoreSettingsInstance
#   Translations
from translations.manager import LanguageManager


# =============================================================================
# >> LOGGING SETUP
# =============================================================================
# Set the logging level
CConVar('sp_logging_level').set_int(
    int(_CoreSettingsInstance['LOG_SETTINGS']['level']))

# Set the logging areas
CConVar('sp_logging_areas').set_int(
    int(_CoreSettingsInstance['LOG_SETTINGS']['areas']))


# =============================================================================
# >> TRANSLATIONS SETUP
# =============================================================================
# Set the default language
LanguageManager._register_default_language(
    _CoreSettingsInstance['BASE_SETTINGS']['language'])


# =============================================================================
# >> AUTH SETUP
# =============================================================================
# Get the auth providers that should be loaded
auth_providers = _CoreSettingsInstance['AUTH_SETTINGS']['providers'].split()

# Should any providers be loaded?
if auth_providers:

    # Import the the SP Commands
    from _core.commands import _SPCommandsInstance

    # Load the auth providers
    _SPCommandsInstance.call_command('auth', ['load'] + auth_providers)
