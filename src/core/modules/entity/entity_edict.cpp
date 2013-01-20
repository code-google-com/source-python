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
#include "entity_props.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "utility/sp_util.h"
#include "utility/wrap_macros.h"
#include "eiface.h"
#include "dt_common.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
//  All external functions for creating entities & managing their keyvalues.
//---------------------------------------------------------------------------------
extern const char* GetKeyValue(edict_t* pEdict, const char* szKeyName);
extern void SetKeyValueInt(edict_t* pEdict, const char* szKeyName, int iValue);
extern void SetKeyValueString(edict_t* pEdict, const char* szKeyName, const char* szValue);
extern void SetKeyValueFloat(edict_t* pEdict, const char* szKeyName, float fValue);
extern void SetKeyValueVector(edict_t* pEdict, const char* szKeyName, Vector value);
extern void DispatchSpawn(edict_t* pEdict);

//---------------------------------------------------------------------------------
// This function exports CBaseEdict and edict_t
//---------------------------------------------------------------------------------
void Export_Edict()
{
	// ----------------------------------------------------------
	// Entity flags
	// ----------------------------------------------------------
	BOOST_GLOBAL_ATTRIBUTE("FL_EDICT_CHANGED", FL_EDICT_CHANGED);
	BOOST_GLOBAL_ATTRIBUTE("FL_EDICT_FREE", FL_EDICT_FREE);
	BOOST_GLOBAL_ATTRIBUTE("FL_EDICT_FULL", FL_EDICT_FULL);
	BOOST_GLOBAL_ATTRIBUTE("FL_EDICT_FULLCHECK", FL_EDICT_FULLCHECK);
	BOOST_GLOBAL_ATTRIBUTE("FL_EDICT_ALWAYS", FL_EDICT_ALWAYS);
	BOOST_GLOBAL_ATTRIBUTE("FL_EDICT_DONTSEND", FL_EDICT_DONTSEND);
	BOOST_GLOBAL_ATTRIBUTE("FL_EDICT_PVSCHECK", FL_EDICT_PVSCHECK);
	BOOST_GLOBAL_ATTRIBUTE("FL_EDICT_PENDING_DORMANT_CHECK", FL_EDICT_PENDING_DORMANT_CHECK);
	BOOST_GLOBAL_ATTRIBUTE("FL_EDICT_DIRTY_PVS_INFORMATION", FL_EDICT_DIRTY_PVS_INFORMATION);
	BOOST_GLOBAL_ATTRIBUTE("FL_FULL_EDICT_CHANGED", FL_FULL_EDICT_CHANGED);

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

		// ----------------------------------------------------------
		// Expose methods for getting the values of network props
		// of entities.
		// ----------------------------------------------------------
		CLASS_METHOD_TYPEDEF(GetPropInt,
			&GetPropValue<int, DPT_Int>,
			"Returns the value (as an integer) of a network prop name.",
			args("szFullPath")
		)
		CLASS_METHOD_TYPEDEF(GetPropFloat,
			&GetPropValue<float, DPT_Float>,
			"Returns the value (as a float) of a network prop name.",
			args("szFullPath")
		)
		CLASS_METHOD_TYPEDEF(GetPropVector,
			&GetPropValue<Vector, DPT_Vector>,
			"Returns the value (as a Vector) of a network prop name.",
			args("szFullPath")
		)
		CLASS_METHOD_TYPEDEF(GetPropVectorXY,
			&GetPropValue<Vector, DPT_VectorXY>,
			"Returns the value (as an Vector, with only the X and Y elements set) of a network prop name.",
			args("szFullPath")
		)
		CLASS_METHOD_TYPEDEF(GetPropString,
			&GetPropValue<const char*, DPT_String>,
			"Returns the value (as a string) of a network prop name.",
			args("szFullPath")
		)
#if( SOURCE_ENGINE >= 2 )
		CLASS_METHOD_TYPEDEF(GetPropLong,
			&GetPropValue<long long, DPT_Int64>,
			"Returns the value (as a long long) of a network prop name.",
			args("szFullPath")
		)
#endif

		// ----------------------------------------------------------
		// Expose methods for setting the values of network props
		// of entities.
		// ----------------------------------------------------------
		CLASS_METHOD_TYPEDEF(SetPropInt,
			&SetPropValue<int, DPT_Int>,
			"Sets the value (as an integer) of a network prop name.",
			args("szFullPath", "propValue")
		)
		CLASS_METHOD_TYPEDEF(SetPropFloat,
			&SetPropValue<float, DPT_Float>,
			"Sets the value (as a float) of a network prop name.",
			args("szFullPath", "propValue")
		)
		CLASS_METHOD_TYPEDEF(SetPropVector,
			&SetPropValue<Vector, DPT_Vector>,
			"Sets the value (as a Vector) of a network prop name.",
			args("szFullPath", "propValue")
		)
		CLASS_METHOD_TYPEDEF(SetPropVectorXY,
			&SetPropValue<Vector, DPT_VectorXY>,
			"Sets the value (as an Vector, with only the X and Y elements set) of a network prop name.",
			args("szFullPath", "propValue")
		)
		CLASS_METHOD_TYPEDEF(SetPropString,
			&SetPropValue<const char*, DPT_String>,
			"Sets the value (as a string) of a network prop name.",
			args("szFullPath", "propValue")
		)
#if( SOURCE_ENGINE >= 2 )
		CLASS_METHOD_TYPEDEF(SetPropLong,
			&SetPropValue<long long, DPT_Int64>,
			"Sets the value (as a long long) of a network prop name.",
			args("szFullPath", "propValue")
		)
#endif
		// ----------------------------------------------------------
		// Expose methods for access keyvalues of entities, and also
		// to spawn entities.
		// ----------------------------------------------------------
		CLASS_METHOD_TYPEDEF(GetKeyValue,
			&GetKeyValue,
			"Returns the key value of an entity.",
			args("szKeyName")
		)
		CLASS_METHOD_TYPEDEF(SetKeyValueInt,
			&SetKeyValueInt,
			"Sets the key value (as an integer) of an entity.",
			args("szKeyName", "szValue")
		)
		CLASS_METHOD_TYPEDEF(SetKeyValueString,
			&SetKeyValueString,
			"Sets the key value (as a string) of an entity.",
			args("szKeyName", "szValue")
		)
		CLASS_METHOD_TYPEDEF(SetKeyValueFloat,
			&SetKeyValueFloat,
			"Sets the key value (as a float) of an entity.",
			args("szKeyName", "fValue")
		)
		CLASS_METHOD_TYPEDEF(SetKeyValueVector,
			&SetKeyValueVector,
			"Sets the key value (as a Vector) of an entity.",
			args("szKeyName", "value")
		)
		CLASS_METHOD_TYPEDEF(DispatchSpawn,
			&DispatchSpawn,
			"Dispatches a message to spawn the entity."
		)
	BOOST_END_CLASS()
}
