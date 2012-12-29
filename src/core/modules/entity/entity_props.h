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
#ifndef _ENTITY_PROPS_H
#define _ENTITY_PROPS_H

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "utility/wrap_macros.h"
#include "utility/sp_util.h"
#include "eiface.h"
#include "dt_common.h"
#include "dt_send.h"
#include "server_class.h"

bool GetPropOffset(const char* szFullPath, int* iOffset, SendPropType* pType);

//---------------------------------------------------------------------------------
// Gets the pointer to a networked prop of an edict_t instance.
//---------------------------------------------------------------------------------
template<class T, int U>
T* GetPropPointer(edict_t* pEdict, const char* szFullPath)
{
	//Check Edict is not NULL
	if (!pEdict)
	{
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "pEdict cannot be a None/NULL object.");
		return NULL;
	}

	//Check the path is not NULL
	if (!szFullPath)
	{
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "szFullPath cannot be a None/NULL object.");
		return NULL;
	}

	//Check the 'Unknown' pointer is not NULL
	void* pUnknown = pEdict->GetUnknown();
	if (!pUnknown)
	{
		BOOST_RAISE_EXCEPTION(PyExc_ValueError, "pEdict is not a current valid instance.");
		return NULL;
	}

	//Get the offset of the network prop
	int iOffset = 0;
	SendPropType propType;
	if (!GetPropOffset(szFullPath, &iOffset, &propType))
	{
		BOOST_RAISE_EXCEPTION(PyExc_Exception, "Could not find the prop offset by the prop name.");
		return NULL;
	}

	//Check if the prop type can be correctly casted
	if (propType != U)
	{
		BOOST_RAISE_EXCEPTION(PyExc_TypeError, "Could not access the prop value in this type.");
		return NULL;
	}

	T* pPropValue = (T*)((unsigned int)pUnknown + iOffset);
	return pPropValue;
}

//---------------------------------------------------------------------------------
// Gets the value of a networked prop of an edict_t instance.
//---------------------------------------------------------------------------------
template<class T, int U>
T GetPropValue(edict_t* pEdict, const char* szFullPath)
{
	T* pPropValue = GetPropPointer<T, U>(pEdict, szFullPath);
	if (!pPropValue)
	{
		return T();
	}

	T propValue = *pPropValue;
	return propValue;
}

//---------------------------------------------------------------------------------
// Sets the value of a networked prop of an edict_t instance.
//---------------------------------------------------------------------------------
template<class T, int U>
void SetPropValue(edict_t* pEdict, const char* szFullPath, T propValue)
{
	T* pPropValue = GetPropPointer<T, U>(pEdict, szFullPath);
	if (!pPropValue)
	{
		return;
	}

	*pPropValue = propValue;
}

#endif // _ENTITY_PROPS_H
