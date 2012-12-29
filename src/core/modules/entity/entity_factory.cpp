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
#include "entity_props.h"
#include "../export_main.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "utility/sp_util.h"
#include "eiface.h"
#include "public/toolframework/itoolentity.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern IServerTools* servertools;

edict_t* CreateEntity(const char* szClassName)
{
	if (!servertools)
	{
		BOOST_RAISE_EXCEPTION(PyExc_Exception, "Cannot create an entity (missing the IServerTools interface instance).");
		return NULL;
	}

	if (!szClassName)
	{
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "szClassName cannot be a None/NULL object.");
		return NULL;
	}

	if (strlen(szClassName) == 0)
	{
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "szClassName cannot be an empty string.");
		return NULL;
	}

	void* pNewEntity = servertools->CreateEntityByName(szClassName);
	if (!pNewEntity)
	{
		BOOST_RAISE_EXCEPTION(PyExc_Exception, "Failed to create a new entity.");
		return NULL;
	}

	IServerUnknown* pNewEntityUnknown = (IServerUnknown*)pNewEntity;
	if (!pNewEntityUnknown)
	{
		BOOST_RAISE_EXCEPTION(PyExc_Exception, "Failed to create a valid new entity (could not cast to IServerUnknown).");
		return NULL;
	}

	IServerNetworkable* pNewEntityNetworkable = pNewEntityUnknown->GetNetworkable();
	if (!pNewEntityNetworkable)
	{
		BOOST_RAISE_EXCEPTION(PyExc_Exception, "Failed to create a valid new entity (could not obtain a valid IServerNetworkable instance).");
		return NULL;
	}

	edict_t* pNewEntityEdict = pNewEntityNetworkable->GetEdict();
	if (!pNewEntityEdict)
	{
		BOOST_RAISE_EXCEPTION(PyExc_Exception, "Failed to create a valid new entity (could not obtain a valid edict_t instance).");
		return NULL;
	}

	return pNewEntityEdict;
}

CBaseEntity* GetBaseEntityFromEdict(edict_t* pEdict)
{
	if (!pEdict)
	{
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "pEdict cannot be a None/NULL object.");
		return NULL;
	}

	IServerUnknown* pEntityUnknown = pEdict->GetUnknown();
	if (!pEntityUnknown)
	{
		BOOST_RAISE_EXCEPTION(PyExc_Exception, "pEdict is not a valid entity (could not obtain an IServerUnknown instance).");
		return NULL;
	}

	CBaseEntity* pEntityBase = pEntityUnknown->GetBaseEntity();
	if (!pEntityBase)
	{
		BOOST_RAISE_EXCEPTION(PyExc_Exception, "pEdict is not a valid entity (could not obtain an CBaseEntity instance).");
		return NULL;
	}

	return pEntityBase;
}

CBaseEntity* CanAccessKeyValue(edict_t* pEdict, const char* szKeyName)
{
	if (!servertools)
	{
		BOOST_RAISE_EXCEPTION(PyExc_Exception, "Cannot access an entity keyvalue (missing the IServerTools interface instance).");
		return NULL;
	}

	CBaseEntity* pEntityBase = GetBaseEntityFromEdict(pEdict);
	if (!pEntityBase)
	{
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "pEdict cannot be a None/NULL object.");
		return NULL;
	}

	if (!szKeyName)
	{
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "szKeyName cannot be a None/NULL object.");
		return NULL;
	}

	if (strlen(szKeyName) == 0)
	{
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "szKeyName cannot be an empty string.");
		return NULL;
	}

	return pEntityBase;
}

const char* GetKeyValue(edict_t* pEdict, const char* szKeyName)
{
	CBaseEntity* pEntityBase = CanAccessKeyValue(pEdict, szKeyName);
	if (!pEntityBase)
	{
		return NULL;
	}

	char* szValue = new char[1024];
	szValue[0] = '\0';
	servertools->GetKeyValue(pEntityBase, szKeyName, szValue, 1024);
	return szValue;
}

void SetKeyValueString(edict_t* pEdict, const char* szKeyName, const char* szValue)
{
	CBaseEntity* pEntityBase = CanAccessKeyValue(pEdict, szKeyName);
	if (!pEntityBase)
	{
		return;
	}

	if (!szValue)
	{
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "szValue cannot be a None/NULL object.");
		return;
	}

	servertools->SetKeyValue(pEntityBase, szKeyName, szValue);
}

void SetKeyValueInt(edict_t* pEdict, const char* szKeyName, int iValue)
{
	char szTemp[16];
	sprintf(szTemp, "%d", iValue);
	SetKeyValueString(pEdict, szKeyName, szTemp);
}

void SetKeyValueFloat(edict_t* pEdict, const char* szKeyName, float fValue)
{
	CBaseEntity* pEntityBase = CanAccessKeyValue(pEdict, szKeyName);
	if (!pEntityBase)
	{
		return;
	}

	servertools->SetKeyValue(pEntityBase, szKeyName, fValue);
}

void SetKeyValueVector(edict_t* pEdict, const char* szKeyName, Vector value)
{
	CBaseEntity* pEntityBase = CanAccessKeyValue(pEdict, szKeyName);
	if (!pEntityBase)
	{
		return;
	}

	servertools->SetKeyValue(pEntityBase, szKeyName, value);
}

void DispatchSpawn(edict_t* pEdict)
{
	if (!servertools)
	{
		BOOST_RAISE_EXCEPTION(PyExc_Exception, "Cannot spawn an entity (missing the IServerTools interface instance).");
		return;
	}

	CBaseEntity* pEntityBase = GetBaseEntityFromEdict(pEdict);
	if (!pEntityBase)
	{
		BOOST_RAISE_EXCEPTION(PyExc_Exception, "Cannot spawn an entity (could not retrieve a valid CBaseEntity instance from an edict_t instance).");
		return;
	}

	servertools->DispatchSpawn(pEntityBase);
}

//---------------------------------------------------------------------------------
// This function exports methods relating to entity props
//---------------------------------------------------------------------------------
void Export_EntityFactory()
{
	BOOST_FUNCTION(CreateEntity,
		"Creates an entity and returns an edict_t instance if successful.",
		args("szClassName"),
		reference_existing_object_policy()
	);
}
