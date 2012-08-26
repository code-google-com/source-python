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
#include "entity_generator.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "utility/sp_util.h"
#include "eiface.h"
#include "dt_common.h"
#include "dt_send.h"
#include "server_class.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern IServerGameDLL* servergamedll;

//---------------------------------------------------------------------------------
// Entities Constructor.
//---------------------------------------------------------------------------------
Entities::Entities(PyObject* self):
	IPythonGenerator<edict_t>(self),
	m_szClassName(NULL),
	m_uiClassNameLen(0),
	m_iEntityIndex(0),
	m_bExactMatch(false)
{
}

//---------------------------------------------------------------------------------
// Entities Copy-Contstructor.
//---------------------------------------------------------------------------------
Entities::Entities(PyObject* self, const Entities& rhs):
	IPythonGenerator<edict_t>(self),
	m_uiClassNameLen(rhs.m_uiClassNameLen),
	m_iEntityIndex(rhs.m_iEntityIndex),
	m_bExactMatch(rhs.m_bExactMatch)
{
	makeStringCopy(rhs.m_szClassName, m_uiClassNameLen);
}

//---------------------------------------------------------------------------------
// Entities Constructor (takes a filter string).
//---------------------------------------------------------------------------------
Entities::Entities(PyObject* self, const char* szClassName):
	IPythonGenerator<edict_t>(self),
	m_uiClassNameLen(strlen(szClassName)),
	m_iEntityIndex(0),
	m_bExactMatch(false)
{
	makeStringCopy(szClassName, m_uiClassNameLen);
}

//---------------------------------------------------------------------------------
// Entities Constructor (takes a filter string and a boolean flag).
//---------------------------------------------------------------------------------
Entities::Entities(PyObject* self, const char* szClassName, bool bExactMatch):
	IPythonGenerator<edict_t>(self),
	m_uiClassNameLen(strlen(szClassName)),
	m_iEntityIndex(0),
	m_bExactMatch(bExactMatch)
{
	makeStringCopy(szClassName, m_uiClassNameLen);
}

//---------------------------------------------------------------------------------
// Entities Destructor.
//---------------------------------------------------------------------------------
Entities::~Entities()
{
	delete[] m_szClassName;
}

//---------------------------------------------------------------------------------
// Returns the next valid edict_t instance, or NULL if reached maxEntities.
//---------------------------------------------------------------------------------
edict_t* Entities::getNext()
{
	edict_t* pEDict = NULL;
	while(m_iEntityIndex < gpGlobals->maxEntities && (!pEDict || pEDict->IsFree()))
	{
		m_iEntityIndex++;
		pEDict = PEntityOfEntIndex(m_iEntityIndex);

		//If the filter string is set, then only allow edict_t instances which either:
		//- Begin with the filter string if m_bExactMatch is false
		//- An exact match with the filter string if m_bExactMatch is true
		if (m_uiClassNameLen && m_szClassName && pEDict && !pEDict->IsFree())
		{
			if (!m_bExactMatch && strncmp(pEDict->GetClassName(), m_szClassName, m_uiClassNameLen) != 0)
			{
				pEDict = NULL;
			}
			else if (m_bExactMatch && strcmp(pEDict->GetClassName(), m_szClassName) != 0)
			{
				pEDict = NULL;
			}
		}
	}

	return pEDict;
}

//---------------------------------------------------------------------------------
// Private function, creates a copy of the class name string.
//---------------------------------------------------------------------------------
void Entities::makeStringCopy(const char* szClassName, unsigned int uiClassNameLen)
{
	if (uiClassNameLen > 0)
	{
		char* szClassNameCopy = new char[uiClassNameLen + 1];
		memcpy(szClassNameCopy, szClassName, uiClassNameLen);
		szClassNameCopy[uiClassNameLen] = 0;
		m_szClassName = szClassNameCopy;
	}
	else
	{
		m_szClassName = NULL;
	}
}

//---------------------------------------------------------------------------------
// This function exports a generator for iterating over entities
//---------------------------------------------------------------------------------
void Export_EntityGenerator()
{
	// ----------------------------------------------------------
	// Entities (Generator)
	// ----------------------------------------------------------
	BOOST_GENERATOR_CLASS(Entities)
		CLASS_CONSTRUCTOR(const char*)
		CLASS_CONSTRUCTOR(const char*, bool)
	BOOST_END_CLASS()
}

