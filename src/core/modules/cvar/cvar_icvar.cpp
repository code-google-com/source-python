/**
* =============================================================================
* Source Python
* Copyright (C) 2012 Source Python Development Team.  All rights reserved.
* =============================================================================
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License, version 3.0, as published by the
* Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
*
* As a special exception, the Source Python Team gives you permission
* to link the code of this program (as well as its derivative works) to
* "Half-Life 2," the "Source Engine," and any Game MODs that run on software
* by the Valve Corporation.  You must obey the GNU General Public License in
* all respects for all other code used.  Additionally, the Source.Python
* Development Team grants this exception to all derivative works.
*/

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "utility/sp_util.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "icvar.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern ICvar* cvar;

//---------------------------------------------------------------------------------
// Accessor for the convar interface.
//---------------------------------------------------------------------------------
ICvar* GetCvar( void )
{
	return cvar;
}

//---------------------------------------------------------------------------------
// Wraps the ICvar class.
//---------------------------------------------------------------------------------
void Export_ICvar( void )
{
	// ----------------------------------------------------------
	// The ICvar interface.
	// ----------------------------------------------------------
	typedef ConVar*		(ICvar::*FindVarFn)(const char*);
	typedef ConCommand* (ICvar::*FindCommandFn)(const char*);

	FindVarFn		ICvar_FindVar = &ICvar::FindVar;
	FindCommandFn	ICvar_FindCommand = &ICvar::FindCommand;

	// ----------------------------------------------------------
	// The ICvar class.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS( ICvar )

		// ----------------------------------------------------------
		// Methods
		// ----------------------------------------------------------
		CLASS_METHOD_TYPEDEF(
			FindVar,
			ICvar_FindVar,
			"Returns a ConVar instance based on the given name. Returns None if not found.",
			reference_existing_object_policy()
		)

		CLASS_METHOD_TYPEDEF(
			FindCommand,
			ICvar_FindCommand,
			"Returns a ConCommand instance based on the given name. Returns None if not found.",
			reference_existing_object_policy()
		)

	BOOST_END_CLASS()

	// Global ICvar accessor.
	BOOST_FUNCTION(GetCvar, reference_existing_object_policy());
}
