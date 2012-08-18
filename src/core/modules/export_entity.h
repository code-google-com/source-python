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
#ifndef _EXPORT_ENTITY_H
#define _EXPORT_ENTITY_H

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "utility/ipythongenerator.h"

//---------------------------------------------------------------------------------
// Forward-declare IPlayerInfo.
//---------------------------------------------------------------------------------
struct edict_t;

//---------------------------------------------------------------------------------
// Declare a generator class to help iterate over the active entities.
//---------------------------------------------------------------------------------
class Entities: public IPythonGenerator<edict_t>
{
public:
	Entities(PyObject* self);
	Entities(PyObject* self, const Entities& rhs);
	Entities(PyObject* self, const char* szClassName);
	virtual ~Entities();
protected:
	virtual edict_t* getNext();
private:
	const char* m_szClassName;
	unsigned int m_uiClassNameLen;
	int m_iEntityIndex;
};

BOOST_SPECIALIZE_HAS_BACK_REFERENCE(Entities)

#endif // _EXPORT_ENTITY_H