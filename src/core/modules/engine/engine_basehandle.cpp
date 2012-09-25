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
#include "../export_main.h"
#include "basehandle.h"
#include "utility/wrap_macros.h"
#include "utility/sp_util.h"
#include "core/sp_python.h"

//---------------------------------------------------------------------------------
// This function exports engine CBaseHandle
//---------------------------------------------------------------------------------
void Export_CBaseHandle( void )
{
	// ----------------------------------------------------------
	// CBaseHandle
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(CBaseHandle)

		// ----------------------------------------------------------
		// Methods
		// ----------------------------------------------------------
		CLASS_METHOD(CBaseHandle,
            IsValid,
            "Returns true if the handle has been initted with any values."
        )

		CLASS_METHOD(CBaseHandle,
            ToInt,
            "Returns an integer value of the handle."
        )

        CLASS_METHOD(CBaseHandle,
            GetEntryIndex,
            "Returns the index of the handle."
        )

		// ----------------------------------------------------------
		// Operators
		// ----------------------------------------------------------
		.def(self == self)
		.def(self != self)
		.def(self < self)

	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// IHandleEntity.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(IHandleEntity)
	
		// ----------------------------------------------------------
		// Methods
		// ----------------------------------------------------------
		CLASS_METHOD(IHandleEntity, 
			GetRefEHandle, 
			"Returns the CBaseHandle instance for this entity.", 
			reference_existing_object_policy()
		)
	
	BOOST_END_CLASS()
}