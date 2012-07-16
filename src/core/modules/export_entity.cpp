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
#include "utility/wrap_macros.h"
#include "eiface.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// Wraps player related structures.
//---------------------------------------------------------------------------------
DECLARE_SP_MODULE(entity)
{
	// ----------------------------------------------------------
	// Entity flags
	// ----------------------------------------------------------
	BOOST_GLOBAL_DEFINE(FL_EDICT_CHANGED);
	BOOST_GLOBAL_DEFINE(FL_EDICT_FREE);
	BOOST_GLOBAL_DEFINE(FL_EDICT_FULL);
	BOOST_GLOBAL_DEFINE(FL_EDICT_FULLCHECK);
	BOOST_GLOBAL_DEFINE(FL_EDICT_ALWAYS);
	BOOST_GLOBAL_DEFINE(FL_EDICT_DONTSEND);
	BOOST_GLOBAL_DEFINE(FL_EDICT_PVSCHECK);
	BOOST_GLOBAL_DEFINE(FL_EDICT_PENDING_DORMANT_CHECK);
	BOOST_GLOBAL_DEFINE(FL_EDICT_DIRTY_PVS_INFORMATION);
	BOOST_GLOBAL_DEFINE(FL_FULL_EDICT_CHANGED);

	// ----------------------------------------------------------
	// CBaseEdict
	// ----------------------------------------------------------
	typedef IServerEntity* (CBaseEdict::*ServerEntityFn)();
	ServerEntityFn fnGetIServerEntity = &CBaseEdict::GetIServerEntity;

	
	BOOST_ABSTRACT_CLASS(CBaseEdict)
		CLASS_METHOD_TYPEDEF(GetIServerEntity,
			fnGetIServerEntity,
			"Returns an IServerEntity if FL_FULLEDICT is set or NULL if this \
			is a lightweight networking entity.",
			reference_existing_object_policy()
		)

		CLASS_METHOD(CBaseEdict,
			GetNetworkable,
			"Returns an IServerNetworkable instance for this entity.",
			reference_existing_object_policy()
		)

		CLASS_METHOD(CBaseEdict,
			GetUnknown,
			"Returns an IServerUnknown instance for this entity.",
			reference_existing_object_policy()
		)

		CLASS_METHOD(CBaseEdict,
			SetEdict,
			"Set when initting an entity. If it's only a networkable, bFullEdict is false.",
			args("pUnk", "bFullEdict")
		)

		CLASS_METHOD(CBaseEdict,
			AreaNum
		)

		CLASS_METHOD(CBaseEdict,
			GetClassName,
			"Returns the classname of this entity"
		)

		CLASS_METHOD(CBaseEdict,
			IsFree,
			"Returns true if this entity has the FL_EDICT_FREE flag."
		)

		CLASS_METHOD(CBaseEdict,
			SetFree,
			"Frees the edict. USE AT YOUR OWN RISK."
		)

		CLASS_METHOD(CBaseEdict,
			ClearFree,
			"Clears the free flags."
		)

		CLASS_MEMBER(CBaseEdict,
			m_fStateFlags
		)

		CLASS_MEMBER(CBaseEdict,
			m_pNetworkable
		)

		CLASS_MEMBER(CBaseEdict,
			m_NetworkSerialNumber
		)

	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Wrap edict_t.
	// ----------------------------------------------------------
	BOOST_INHERITED_CLASS(edict_t, CBaseEdict)
		CLASS_METHOD(edict_t,
			GetCollideable,
			"Returns the ICollideable instance for this entity.",
			reference_existing_object_policy()
		)
	BOOST_END_CLASS()
}