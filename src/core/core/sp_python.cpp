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
*
* Special thanks to Mark Chandler <mark@moddb.com>!
* Sources:
* http://code.google.com/p/sourcesdkpython/source/browse/trunk/src/game/server/py/ge_pymanager.cpp
*/

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "sp_python.h"
#include "sp_gamedir.h"
#include "eiface.h"
#include "modules/export_main.h"

//---------------------------------------------------------------------------------
// Interfaces we're going to use.
//---------------------------------------------------------------------------------
extern IVEngineServer* engine;

//---------------------------------------------------------------------------------
// Singleton
//---------------------------------------------------------------------------------
CPythonManager g_PythonManager;

//---------------------------------------------------------------------------------
// This is externed because we need to manually import ES's core library into the
// python namespace.
//---------------------------------------------------------------------------------
// PyMODINIT_FUNC PyInit_sp( void );

//---------------------------------------------------------------------------------
// Initializes python.
//---------------------------------------------------------------------------------
bool CPythonManager::Initialize( void )
{
	// Construct a path to the python engine directory.
	char szPythonHome[MAX_GAME_PATH];
	V_snprintf(szPythonHome, MAX_GAME_PATH, "%s/engines", g_GamePaths.GetESDir());
	V_FixSlashes(szPythonHome);
	DevMsg(1, "[SP] Python home path set to %s\n", szPythonHome);

	// Convert to wide char for python.
	wchar_t wszPythonHome[1024];
	V_strtowcs(szPythonHome, -1, wszPythonHome, 1024);

	// Always add es as a module.
	// PyImport_AppendInittab("sp", &PyInit_sp);

	// Set that as the python home directory.
 	Py_SetPythonHome(wszPythonHome);
 	Py_SetProgramName(wszPythonHome);
	Py_SetPath(wszPythonHome);

	// Initialize python and its namespaces.
	Py_Initialize();

	// Print some information
	DevMsg(1, "Python version %s initialized!\n", Py_GetVersion());

	// Add _libs to the library path.
	char szLibsPath[MAX_GAME_PATH];
	V_snprintf(szLibsPath, MAX_GAME_PATH, "%s/_libs", g_GamePaths.GetESDir());
	V_FixSlashes(szLibsPath);
	
	PyRun_SimpleString("import sys");
	char szLibsCmd[MAX_GAME_PATH];
	V_snprintf(szLibsCmd, MAX_GAME_PATH, "sys.path.append(r\"%s\")", szLibsPath);
	PyRun_SimpleString(szLibsCmd);
	
	// Add the platform specific directory to the path.
	char szPlatDir[MAX_GAME_PATH];
	char szPlatCmd[MAX_GAME_PATH];
#if defined(_WIN32)
	V_snprintf(szPlatDir, MAX_GAME_PATH, "%s/engines/plat-win", g_GamePaths.GetESDir());
#else
	V_snprintf(szPlatDir, MAX_GAME_PATH, "%s/engines/plat-linux", g_GamePaths.GetESDir());
#endif
	V_FixSlashes(szPlatDir);
	V_snprintf(szPlatCmd, MAX_GAME_PATH, "sys.path.append(r\"%s\")", szPlatDir);
	PyRun_SimpleString(szPlatCmd);

    // Add the site packages directory.
	char szSitePackages[MAX_GAME_PATH];
	V_snprintf(szSitePackages, MAX_GAME_PATH, "%s/engines/site-packages", g_GamePaths.GetESDir());
	V_FixSlashes(szSitePackages);
    
    char szSitePackagesCmd[MAX_GAME_PATH];
    V_snprintf(szSitePackagesCmd, MAX_GAME_PATH, "sys.path.append(r\"%s\")", szSitePackages);
    PyRun_SimpleString(szSitePackagesCmd);
    
	// Add the addons directory too.
	char szAddonsCmd[MAX_GAME_PATH];
	V_snprintf(szAddonsCmd, MAX_GAME_PATH, "sys.path.append(r\"%s\")", g_GamePaths.GetESDir());
	PyRun_SimpleString(szAddonsCmd);

	// Import the main module file.
	Msg("[SP] Importing main module..\n");
 	BEGIN_BOOST_PY()
 		m_SpPy = python::import("sp");
 	END_BOOST_PY_NORET(); // Noret because we have more stuff to do after this import.

	// Initialize all submodules
	modulsp_init();

	return true;
}

//---------------------------------------------------------------------------------
// Shuts down python.
//---------------------------------------------------------------------------------
bool CPythonManager::Shutdown( void )
{
	return true;
}
