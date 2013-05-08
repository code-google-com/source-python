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

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "entities_generator_wrap.h"
#include "entities_wrap.h"
#include "utility/sp_util.h"
#include "boost/python/iterator.hpp"

// ----------------------------------------------------------------------------
// Entities Constructor.
// ----------------------------------------------------------------------------
Entities::Entities( PyObject* self ):
	IPythonGenerator<CEdict>(self),
	m_iEntityIndex(0),
	m_szClassName(NULL),
	m_uiClassNameLen(0),
	m_bExactMatch(false)
{
}

// ----------------------------------------------------------------------------
// Entities Copy-Constructor.
// ----------------------------------------------------------------------------
Entities::Entities( PyObject* self, const Entities& rhs ):
	IPythonGenerator<CEdict>(self),
	m_iEntityIndex(rhs.m_iEntityIndex),
	m_uiClassNameLen(rhs.m_uiClassNameLen),
	m_bExactMatch(rhs.m_bExactMatch)
{
	makeStringCopy(rhs.m_szClassName, m_uiClassNameLen);
}

// ----------------------------------------------------------------------------
// Entities Constructor (takes a filter string).
// ----------------------------------------------------------------------------
Entities::Entities(PyObject* self, const char* szClassName):
	IPythonGenerator<CEdict>(self),
	m_iEntityIndex(0),
	m_uiClassNameLen(strlen(szClassName)),
	m_bExactMatch(false)
{
	makeStringCopy(szClassName, m_uiClassNameLen);
}

// ----------------------------------------------------------------------------
// Entities Constructor (takes a filter string and a boolean flag).
// ----------------------------------------------------------------------------
Entities::Entities(PyObject* self, const char* szClassName, bool bExactMatch):
	IPythonGenerator<CEdict>(self),
	m_iEntityIndex(0),
	m_uiClassNameLen(strlen(szClassName)),
	m_bExactMatch(bExactMatch)
{
	makeStringCopy(szClassName, m_uiClassNameLen);
}

// ----------------------------------------------------------------------------
// Entities Destructor.
// ----------------------------------------------------------------------------
Entities::~Entities()
{
	delete[] m_szClassName;
}

// ----------------------------------------------------------------------------
// Returns the next valid CEdict instance.
// ----------------------------------------------------------------------------
CEdict* Entities::getNext()
{
	edict_t* pEdict = NULL;
	CEdict* pCEdict = NULL;
	while(m_iEntityIndex < gpGlobals->maxEntities)
	{
		m_iEntityIndex++;
		pEdict = PEntityOfEntIndex(m_iEntityIndex);
		if (!pEdict || pEdict->IsFree() || !strlen(pEdict->GetClassName()))
		{
			pEdict = NULL;
		}
		else if (m_uiClassNameLen && m_szClassName)
		{
			if (!m_bExactMatch && strncmp(pEdict->GetClassName(), m_szClassName, m_uiClassNameLen) != 0)
			{
				pEdict = NULL;
			}
			else if (m_bExactMatch && strcmp(pEdict->GetClassName(), m_szClassName) != 0)
			{
				pEdict = NULL;
			}
		}
		if (pEdict)
		{
			pCEdict = new CEdict(pEdict);
			return pCEdict;
		}
	}
    return NULL;
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
