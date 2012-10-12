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
#include "eiface.h"
#include "utility/wrap_macros.h"
#include "utility/sp_util.h"
#include "core/sp_python.h"

//---------------------------------------------------------------------------------
// Required because cbaseentity isn't defined.
//---------------------------------------------------------------------------------
class CBaseEntity {};

//---------------------------------------------------------------------------------
// This is required because boost::python hates void pointers..
//---------------------------------------------------------------------------------
unsigned long GetBaseEntity(IServerUnknown* pUnk)
{
	return (unsigned long)(pUnk->GetBaseEntity());
}

//---------------------------------------------------------------------------------
// Wraps misc engine classes.
//---------------------------------------------------------------------------------
void Export_EngineMisc( void )
{
	// ----------------------------------------------------------
	// Dummy CBaseEntity.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(CBaseEntity)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// INetworkable interface.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(IServerNetworkable)

		// ----------------------------------------------------------
		// Class methods.
		// ----------------------------------------------------------
		CLASS_METHOD(IServerNetworkable, 
			GetEntityHandle, 
			"Returns the entity handle associated with the collideable.",
			reference_existing_object_policy()
		)

		CLASS_METHOD(IServerNetworkable, 
			GetEdict, 
			"Returns the edict for this entity.", 
			reference_existing_object_policy()
		)

		CLASS_METHOD(IServerNetworkable, 
			GetClassName, 
			"Returns the classname for this object."
		)

	BOOST_END_CLASS()


	// ----------------------------------------------------------
	// IServerUnknown
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS_INHERITED(IServerUnknown, IHandleEntity)

		// ----------------------------------------------------------
		// Methods
		// ----------------------------------------------------------
		CLASS_METHOD(IServerUnknown, GetCollideable, "Returns the ICollideable object for this entity.",
			reference_existing_object_policy()
		)

		CLASS_METHOD(IServerUnknown, GetNetworkable, "Returns the IServerNetworkable object for this entity.", 
			reference_existing_object_policy()
		)

		CLASS_METHOD_TYPEDEF(GetBaseEntity, GetBaseEntity, "Returns the CBaseEntity object for this entity.")

	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// IServerEntity
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS_INHERITED(IServerEntity, IServerUnknown)
		CLASS_METHOD(IServerEntity,
			GetModelIndex,
			"Gets the model index used by the server entity."
		)
		CLASS_METHOD(IServerEntity,
			SetModelIndex,
			"Sets the model index used by the server entity."
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Expose some entity functions
	// ----------------------------------------------------------
	BOOST_FUNCTION(PEntityOfEntIndex,
        "Returns the edict for an entity index.",
        reference_existing_object_policy());
	BOOST_FUNCTION(IndexOfEdict,
        "Returns the index of an entity edict",
        args("edict"));
	BOOST_FUNCTION(IndexOfIntHandle,
        "Returns the index of an entity from its handle in integer form",
        args("iHandle"));
}