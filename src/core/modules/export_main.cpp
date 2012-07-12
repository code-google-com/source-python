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

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "boost/python.hpp"
#include "export_main.h"
#include "tier0/dbg.h"

//---------------------------------------------------------------------------------
// Namespaces to use
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// Global module definition array.
//---------------------------------------------------------------------------------
EventscriptsModule_t g_EventscriptsModules[MAX_EVENTSCRIPTS_MODULES];

//---------------------------------------------------------------------------------
// Static variable initializer.
//---------------------------------------------------------------------------------
int CESModule::nextFreeModule = 0;

//---------------------------------------------------------------------------------
// The ES module. Never remove this function as we need it in order to be able
// to execute 'import es; from es import event'.
//---------------------------------------------------------------------------------
BOOST_PYTHON_MODULE(es)
{

}

//---------------------------------------------------------------------------------
// Initializes all python modules
//---------------------------------------------------------------------------------
void modules_init( void )
{
	// Get the Eventscripts module
	object esmodule(borrowed(PyImport_AddModule("es")));

	// Now iterate through all submodules and add them.
	for( int i = 0; i < MAX_EVENTSCRIPTS_MODULES; i++ ) {
		// Break out if we are at the end.
		if( !g_EventscriptsModules[i].szName ) {
			return;
		}

		// Get the module name.
		char* szModuleName = g_EventscriptsModules[i].szName;

		// Debug info.
		DevMsg(1, "[ES] Initializing %s submodule\n", szModuleName);

		// Set the new module as the current scope.
		object newmodule(borrowed(PyImport_AddModule(szModuleName)));
		
		// Add the module to the es module.
		esmodule.attr(szModuleName) = newmodule;

		// We're now working with the submodule.
		scope moduleScope = newmodule;

		// Run the module's init function.
		g_EventscriptsModules[i].initFunc();

		// Add the module to the import table.
		// PyImport_AppendInittab(g_EventscriptsModules[i].szName, g_EventscriptsModules[i].initFunc);
	}
}