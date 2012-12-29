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
#include "convar.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// Wraps ConCommandBase
//---------------------------------------------------------------------------------
void Export_ConCommandBase( void )
{
	// ----------------------------------------------------------
	// Console variable/command base.
	// ----------------------------------------------------------
	BOOST_CLASS( ConCommandBase )

		// ----------------------------------------------------------
		// Constructors.
		// ----------------------------------------------------------
		CLASS_CONSTRUCTOR(const char*, const char*, int)

		// ----------------------------------------------------------
		// Methods
		// ----------------------------------------------------------
		CLASS_METHOD(ConCommandBase,
			IsCommand,
			"Returns true if the ConCommandBase instance is a command."
		)

		CLASS_METHOD(ConCommandBase,
			IsFlagSet,
			"Returns true if the flag given is set on the ConCommandBase instance.",
			args("flag")
		)

		CLASS_METHOD(ConCommandBase,
			AddFlags,
			"Adds the given flags to the ConCommandBase instance.",
			args("flags")
		)

		CLASS_METHOD(ConCommandBase,
			GetName,
			"Returns the name of this ConCommandBase instance."
		)

#if( SOURCE_ENGINE >= 2 )
		CLASS_METHOD(ConCommandBase,
			GetFlags,
			"Returns the flags set on this ConCommandBase."
		)

		CLASS_METHOD(ConCommandBase,
			RemoveFlags,
			"Removes the given flags from the ConCommandBase instance.",
			args("flags")
		)
#endif

	BOOST_END_CLASS()
}
