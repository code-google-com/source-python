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
#include "es_addon.h"
#include "strtools.h"
#include "convar.h"
#include "filesystem.h"
#include "core/es_gamedir.h"
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
// Addon constructor
//---------------------------------------------------------------------------------
CAddon::CAddon( char* szAddonName )
{
	// Copy the addon name over.
	V_strncpy(m_szAddonName, szAddonName, MAX_ADDON_NAME);
	m_bIsLoaded = false;
}

//---------------------------------------------------------------------------------
// Addon destructor
//---------------------------------------------------------------------------------
CAddon::~CAddon( void )
{
	// Make sure we have unloaded.
	if( m_bIsLoaded ) {
		Unload();
		m_bIsLoaded = false;
	}
}

//---------------------------------------------------------------------------------
// Prints information about this addon.
//---------------------------------------------------------------------------------
void CAddon::PrintInfo( void )
{
	Msg("\t%s", m_szAddonName);
}

//---------------------------------------------------------------------------------
// Returns the addon name.
//---------------------------------------------------------------------------------
char* CAddon::GetName( void )
{
	return m_szAddonName;
}

//---------------------------------------------------------------------------------
// Loads the addon
//---------------------------------------------------------------------------------
bool CAddon::Load( void )
{
	// Construct the path to the addon.
	char szAddonPath[MAX_GAME_PATH];
	V_snprintf(szAddonPath, MAX_GAME_PATH, "%s/%s/%s.py", g_GamePaths.GetESDir(), 
		m_szAddonName, m_szAddonName);
	V_FixSlashes(szAddonPath);

	// Attempt to open the file to make sure it exists.
	FileHandle_t fScript = filesystem->Open(szAddonPath, "r");
	if( !fScript ) {
		Msg("[ES] Failed to load addon at %s\n", szAddonPath);
		return false;
	}
	
	// No longer need the file handle.
	filesystem->Close(fScript);

	// Call its load function.
	BEGIN_BOOST_PY()
		python::exec_file(szAddonPath, g_PythonManager.GetGlobals(), m_Namespace);
		python::object load = m_Namespace["load"];
		load();
	END_BOOST_PY( false )
	
	Msg("[ES] Addon %s loaded successfully.\n", m_szAddonName);

	m_bIsLoaded = true;
	return true;
}

//---------------------------------------------------------------------------------
// Unloads the addon
//---------------------------------------------------------------------------------
bool CAddon::Unload( void )
{
	// Only attempt unload if we are loaded.
	if( m_bIsLoaded ) {
		BEGIN_BOOST_PY()
			python::object unload = m_Namespace["unload"];
			unload();
		END_BOOST_PY( false )
	}

	m_bIsLoaded = false;
	return true;
}

//---------------------------------------------------------------------------------
// Destructor
//---------------------------------------------------------------------------------
CAddonManager::~CAddonManager( void )
{
	// Free up all memory.
	m_Addons.PurgeAndDeleteElements();
}

//---------------------------------------------------------------------------------
// Fires game event.
//---------------------------------------------------------------------------------
void CAddonManager::FireGameEvent( IGameEvent* event )
{
	for( int i = 0; i < m_Addons.Count(); i++ )
	{
		CAddon* Addon = m_Addons[i];

		// Get locals for the module.
		python::object Locals = Addon->GetNamespace();

		// Does the addon contain a function for this event?
		const char* szEventName = event->GetName();
		if( Locals.contains(szEventName) ) {
			BEGIN_BOOST_PY()
				Locals[szEventName](python::ptr(event));
			END_BOOST_PY()
		}
	}
}

//---------------------------------------------------------------------------------
// Loads an addon.
//---------------------------------------------------------------------------------
bool CAddonManager::LoadAddon( char* szName )
{
	DevMsg(1, "[ES] Loading addon %s\n", szName);
	CAddon* Addon = new CAddon(szName);

	// Attempt to load it.
	if( !Addon->Load() ) {
		Msg("[ES] Could not load addon %s\n", szName);
		delete Addon;
		return false;
	}

	// Add it to our list.
	m_Addons.AddToTail(Addon);

	return true;
}

//---------------------------------------------------------------------------------
// Unloads an addon
//---------------------------------------------------------------------------------
bool CAddonManager::UnloadAddon( char* szName )
{
	DevMsg(1, "[ES] Unloading addon %s\n", szName);

	// FIXME: There is probably a better way of doing this.
	for( int i = 0; i < m_Addons.Count(); i++ )
	{
		CAddon* Addon = m_Addons[i];
		if( V_strncmp(szName, Addon->GetName(), MAX_ADDON_NAME) == 0 ) {
			// Unload and free the memory.
			Addon->Unload();
			delete Addon;

			// Remove it from the list.
			m_Addons.Remove(i);
			Msg("[ES] Unloaded %s successfully.\n", szName);
			return true;
		}
	}

	Msg("[ES] Could not find addon %s\n", szName);
	return false;
}

//---------------------------------------------------------------------------------
// Prints out addon information.
//---------------------------------------------------------------------------------
void CAddonManager::PrintAddons( void )
{
	Msg("----------------------------------------------------\n");
	Msg("Eventscripts Addon listing:\n");
	Msg("----------------------------------------------------\n");
	
	for( int i = 0; i < m_Addons.Count(); i++ ) {
		CAddon* Addon = m_Addons[i];
		Msg("%d: %s\n", i, Addon->GetName());
	}
}

//---------------------------------------------------------------------------------
// Console command to load an addon
//---------------------------------------------------------------------------------
CON_COMMAND(es_load, "Loads a python addon.")
{
	if( args.ArgC() < 2 ) {
		g_AddonManager.PrintAddons();
		Msg("Usage: es_load <addon-name>\n");
		return;
	}

	g_AddonManager.LoadAddon((char *)args.Arg(1));
}

//---------------------------------------------------------------------------------
// Console command to unload an addon
//---------------------------------------------------------------------------------
CON_COMMAND(es_unload, "Unloads a python addon.")
{
	if( args.ArgC() < 2 ) {
		Msg("Usage: es_unload <addon-name>\n");
		return;
	}

	g_AddonManager.UnloadAddon((char *)args.Arg(1));
}