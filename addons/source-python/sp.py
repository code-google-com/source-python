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
from _core.settings import CoreSettings
from _core.commands import SPCommands
from loggers import SPLogger
#   Translations
from translations.manager import LanguageManager


# Set the default language
LanguageManager._register_default_language(
    CoreSettings['BASE_SETTINGS']['language'])

# Loop through the log settings
for variable in CoreSettings['LOG_SETTINGS']:

    # Create a variable for the current log setting
    # and store the value to SPLogger's attributes
    setattr(SPLogger, '_' + variable, CConVar(
        'sp_logging_' + variable, CoreSettings['LOG_SETTINGS'][variable],
        0, CoreSettings['LOG_SETTINGS'].comments[variable][0]))

# Get the auth providers that should be loaded
auth_providers = CoreSettings['AUTH_SETTINGS']['providers'].split()

# Should any providers be loaded?
if auth_providers:

    # Load the auth providers
    SPCommands.call_command('auth', ['load'] + auth_providers)
