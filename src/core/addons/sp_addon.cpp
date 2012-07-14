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
* all respects for all other code used.  Additionally, the Eventscripts
* Development Team grants this exception to all derivative works.  
*/

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "sp_addon.h"
#include "strtools.h"
#include "convar.h"
#include "filesystem.h"
#include "core/sp_gamedir.h"
#include "utility/wrap_macros.h"

//---------------------------------------------------------------------------------
// External variables
//---------------------------------------------------------------------------------
extern IFileSystem* filesystem;

//---------------------------------------------------------------------------------
// Static singleton.
//---------------------------------------------------------------------------------
CAddonManager g_AddonManager;

//---------------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------------
CAddonManager::CAddonManager( void )
{

}

//---------------------------------------------------------------------------------
// Destructor
//---------------------------------------------------------------------------------
CAddonManager::~CAddonManager( void )
{
	
}

//---------------------------------------------------------------------------------
// Fires game event.
//---------------------------------------------------------------------------------
void CAddonManager::FireGameEvent( IGameEvent* event )
{
	// Pass that on to python.
	python::object mainFile = g_PythonManager.GetSP();

	// Execute addon_load.
	BEGIN_BOOST_PY()
		mainFile.attr("event_fire")(python::ptr(event));
	END_BOOST_PY();
}

//---------------------------------------------------------------------------------
// Loads an addon.
//---------------------------------------------------------------------------------
bool CAddonManager::LoadAddon( const char* szName )
{
	// Pass that on to python.
	python::object mainFile = g_PythonManager.GetSP();

	// Execute addon_load.
	// TODO: Add error handling.
	BEGIN_BOOST_PY()
		mainFile.attr("addon_load")(szName);
	END_BOOST_PY(true);

	return true;
}

//---------------------------------------------------------------------------------
// Unloads an addon
//---------------------------------------------------------------------------------
bool CAddonManager::UnloadAddon( const char* szName )
{
	// Pass that on to python.
	python::object mainFile = g_PythonManager.GetSP();

	// Execute addon_load.
	// TODO: Add error handling.
	BEGIN_BOOST_PY()
		mainFile.attr("addon_unload")(szName);
	END_BOOST_PY(true);

	return true;
}

//---------------------------------------------------------------------------------
// Reloads an addon.
//---------------------------------------------------------------------------------
bool CAddonManager::ReloadAddon( const char* szName )
{
	// Pass that on to python.
	python::object mainFile = g_PythonManager.GetSP();

	// Execute addon_load.
	// TODO: Add error handling.
	BEGIN_BOOST_PY()
		mainFile.attr("addon_reload")(szName);
	END_BOOST_PY(true);

	return true;
}

//---------------------------------------------------------------------------------
// Console command to load an addon
//---------------------------------------------------------------------------------
CON_COMMAND(sp_load, "Loads a python addon.")
{
	if( args.ArgC() < 2 ) {
		g_AddonManager.LoadAddon("");
		return;
	}

	PyRun_SimpleString("import sp");
	PyRun_SimpleString("print(sp.__dict__)");

	g_AddonManager.LoadAddon((char *)args.Arg(1));
}

//---------------------------------------------------------------------------------
// Console command to unload an addon
//---------------------------------------------------------------------------------
CON_COMMAND(sp_unload, "Unloads a python addon.")
{
	if( args.ArgC() < 2 ) {
		Msg("Usage: sp_unload <addon-name>\n");
		return;
	}

	g_AddonManager.UnloadAddon(args.Arg(1));
}

//---------------------------------------------------------------------------------
// Console command to reload an addon.
//---------------------------------------------------------------------------------
CON_COMMAND(sp_reload, "Reloads a python addon.")
{
	if( args.ArgC() < 2 ) {
		Msg("Usage: sp_reload <addon-name>\n");
		return;
	}

	g_AddonManager.ReloadAddon(args.Arg(1));
}