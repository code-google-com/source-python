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
#ifndef _EXPORT_MAIN_H
#define _EXPORT_MAIN_H

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "boost/python.hpp"
#include "utility/wrap_macros.h"

//---------------------------------------------------------------------------------
// Maximum number of modules we can have.
//---------------------------------------------------------------------------------
#define MAX_EVENTSCRIPTS_MODULES 64

//---------------------------------------------------------------------------------
// Python init function typedef.
//---------------------------------------------------------------------------------
typedef void (*ModuleInitFn)( void );

//---------------------------------------------------------------------------------
// This declares an eventscripts module.
//---------------------------------------------------------------------------------
#define DECLARE_ES_MODULE( name ) \
	void PyInit_##name( void ); \
	static CESModule g_##name##_Init(XSTRINGIFY(name), &PyInit_##name); \
	void PyInit_##name( void )

//---------------------------------------------------------------------------------
// This is a module definition structure. The way our module system is going to
// work is you declare a module via BOOST_PYTHON_MODULE. Then the CPythonManager
// class will iterate over the module list and add it to the import table.
//---------------------------------------------------------------------------------
struct EventscriptsModule_t
{
	char*		 szName;
	ModuleInitFn initFunc;
};

//---------------------------------------------------------------------------------
// Global module array.
//---------------------------------------------------------------------------------
extern EventscriptsModule_t g_EventscriptsModules[];

//---------------------------------------------------------------------------------
// This helper class will do some static initialization.
//---------------------------------------------------------------------------------
class CESModule
{
	public:
		static int nextFreeModule;

	public:
		CESModule(char* szName, ModuleInitFn initFunc) {
			if( nextFreeModule < MAX_EVENTSCRIPTS_MODULES ) {
				g_EventscriptsModules[nextFreeModule].initFunc = (ModuleInitFn)initFunc;
				g_EventscriptsModules[nextFreeModule].szName = szName;
				
				nextFreeModule++;

				g_EventscriptsModules[nextFreeModule].initFunc = NULL;
				g_EventscriptsModules[nextFreeModule].szName = NULL;
			}
		}
};

//---------------------------------------------------------------------------------
// Exports everything we're exposing from boost to python.
//---------------------------------------------------------------------------------
extern void modules_init( void );

#endif // _EXPORT_MAIN_H