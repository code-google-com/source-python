/**
* =============================================================================
* Eventscripts
* Copyright (C) 2012 Eventscripts Development Team.  All rights reserved.
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
* As a special exception, the Eventscripts Development Team gives you permission 
* to link the code of this program (as well as its derivative works) to 
* "Half-Life 2," the "Source Engine," and any Game MODs that run on software
* by the Valve Corporation.  You must obey the GNU General Public License in
* all respects for all other code used.  Additionally, the Eventscripts
* Development Team grants this exception to all derivative works.  
*/
#ifndef _ES_PYTHON_H
#define _ES_PYTHON_H

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "boost/python/detail/wrap_python.hpp"
#include "boost/python.hpp"

//---------------------------------------------------------------------------------
// Namespaces
//---------------------------------------------------------------------------------
using namespace boost;

//---------------------------------------------------------------------------------
// This is the python manager class.
//---------------------------------------------------------------------------------
class CPythonManager
{
	private:
		python::object m_MainModule;
		python::object m_MainNameSpace;

	public:
		bool Initialize( void );
		bool Shutdown( void );

		python::object& GetGlobals( void ) { return m_MainNameSpace; }
		python::object& GetLocals( void ) { return m_MainModule; }
};

//---------------------------------------------------------------------------------
// The singleton.
//---------------------------------------------------------------------------------
extern CPythonManager g_PythonManager;

#endif // _ES_PYTHON_H
