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
#include "boost/python.hpp"
#include "core/sp_python.h"
#include "export_main.h"
#include "tier0/dbg.h"

//---------------------------------------------------------------------------------
// Namespaces to use
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// Global module definition array.
//---------------------------------------------------------------------------------
SourcePythonModule_t g_SourcePythonModules[MAX_SOURCEPYTHON_MODULES];

//---------------------------------------------------------------------------------
// Static variable initializer.
//---------------------------------------------------------------------------------
int CSPModule::nextFreeModule = 0;

//---------------------------------------------------------------------------------
// The ES module. Never remove this function as we need it in order to be able
// to execute 'import sp; from sp import event'.
//---------------------------------------------------------------------------------
BOOST_PYTHON_MODULE(Source)
{
 
}

//---------------------------------------------------------------------------------
// Initializes all python modules
//---------------------------------------------------------------------------------
void modulsp_init( void )
{
	BEGIN_BOOST_PY()
		// Get the Source.Python module
		object spmodule(borrowed(PyImport_AddModule("Source")));
		// object spmodule(g_PythonManager.GetSP());

		// Now iterate through all submodules and add them.
		for( int i = 0; i < MAX_SOURCEPYTHON_MODULES; i++ ) {
			// Break out if we are at the end.
			if( !g_SourcePythonModules[i].szName ) {
				return;
			}

			// Get the module name.
			char* szModuleName = g_SourcePythonModules[i].szName;

			// Debug info.
			DevMsg(1, "[SP] Initializing %s submodule\n", szModuleName);

			// Set the new module as the current scope.
			object newmodule(borrowed(PyImport_AddModule(szModuleName)));
		
			// Add the module to the es module.
			spmodule.attr(szModuleName) = newmodule;

			// We're now working with the submodule.
			scope moduleScope = newmodule;

			// Run the module's init function.
			g_SourcePythonModules[i].initFunc();

			// Add the module to the import table.
			// PyImport_AppendInittab(g_SourcePythonModules[i].szName, g_SourcePythonModules[i].initFunc);
		}
	END_BOOST_PY_NORET()
}