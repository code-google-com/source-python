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
#include "export_main.h"
#include "core/sp_python.h"
#include "utility/sp_util.h"
#include "utility/wrap_macros.h"
#include "shake.h"
#include "game/shared/IEffects.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern IEffects* effects;

//---------------------------------------------------------------------------------
// Returns the global effects instance.
//---------------------------------------------------------------------------------
IEffects* GetEffects( void )
{
	return effects;
}

//---------------------------------------------------------------------------------
// Wraps all miscellaneous classes, structures, etc.
// It is highly suggested that code in this module *will* be moved into a more
// permanent location in the future. Use of this module should be temporary.
//---------------------------------------------------------------------------------

//Declare method overloads to allow for default parameter options
DECLARE_CLASS_METHOD_OVERLOAD(IEffects, Sparks, 1, 4);
DECLARE_CLASS_METHOD_OVERLOAD(IEffects, EnergySplash, 2, 3);

DECLARE_SP_MODULE(Misc)
{
	// ----------------------------------------------------------
	// IEffects class
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(IEffects)
		CLASS_METHOD(IEffects,
			Beam,
			"Creates a beam particle effect.",
			args("Start", "End", "nModelIndex", "nHaloIndex", "frameStart", "frameRate", "flLife", "width", "endWidth", "fadeLength",
				 "noise", "red", "green", "blue", "brightness", "speed")
		)

		CLASS_METHOD(IEffects,
			Smoke,
			"Creates a smoke effect.",
			args("origin", "modelIndex", "scale", "framerate")
		)


		CLASS_METHOD_OVERLOAD(IEffects,
			Sparks,
			"Creates a sparks effect.",
			args("position", "nMagnitude", "nTrailLength", "pvecDir")
		)

		CLASS_METHOD(IEffects,
			Dust,
			"Creates a dust effect.",
			args("pos", "dir", "size", "speed")
		)

		CLASS_METHOD(IEffects,
			MuzzleFlash,
			"Creates a muzzle flash effect.",
			args("vecOrigin", "vecAngles", "flScale", "iType")
		)

		CLASS_METHOD(IEffects,
			MetalSparks,
			"Creates a muzzle flash effect.",
			args("position", "direction")
		)

		CLASS_METHOD_OVERLOAD(IEffects,
			EnergySplash,
			"Creates an energy splash effect.",
			args("position", "direction", "bExplosive")
		)

		CLASS_METHOD(IEffects,
			Ricochet,
			"Creates a ricochet effect.",
			args("position", "direction")
		)

		CLASS_METHOD(IEffects,
			Time,
			"Returns the current time. [NOTE: May be removed by Valve at a later date]"
		)

		CLASS_METHOD(IEffects,
			IsServer,
			"Returns True if this is a server. [NOTE: May be removed by Valve at a later date]"
		)

		CLASS_METHOD(IEffects,
			SuppressEffectsSounds,
			"Set to True to suppress effect sounds.",
			args("bSuppress")
		)		
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Expose the global effects instance.
	// ----------------------------------------------------------
	BOOST_FUNCTION(GetEffects, reference_existing_object_policy());
}
