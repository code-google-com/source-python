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
// Source includes
//---------------------------------------------------------------------------------
#include "loader_main.h"
#include "interface.h"
#include "eiface.h"
#include "strtools.h"
#ifdef _WIN32
#	include <windows.h>
#endif

//---------------------------------------------------------------------------------
// Disable warnings.
//---------------------------------------------------------------------------------
#if defined(_WIN32)
#    pragma warning( disable : 4005 )
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//---------------------------------------------------------------------------------
// Interfaces.
//---------------------------------------------------------------------------------
ICvar* g_pCVar = NULL; // This is required for linux linking..

// 
// The plugin is a static singleton that is exported as an interface
//
CSourcePython g_EmtpyServerPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CSourcePython, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS, g_EmtpyServerPlugin );

//---------------------------------------------------------------------------------
// Purpose: constructor/destructor
//---------------------------------------------------------------------------------
CSourcePython::CSourcePython()
{
	m_iClientCommandIndex = 0;
	m_pCore = NULL;
}

CSourcePython::~CSourcePython()
{
}

//---------------------------------------------------------------------------------
// This function will load libraries and return true if they load successfully.
// 
//---------------------------------------------------------------------------------
void* SPLoadLibrary( IVEngineServer* engine, const char* libraryPath )
{
	char szFullPath[1024];
	char szGamePath[1024];
	engine->GetGameDir(szGamePath, 1024);

	V_snprintf(szFullPath, sizeof(szFullPath), "%s/addons/source-python/%s", 
		szGamePath, libraryPath);

	// Fix up the slahes.
	V_FixSlashes(szFullPath);

#if defined(_WIN32)
	void* hModule = (void *)LoadLibrary(szFullPath);
#else
	void* hModule = (void *)dlopen(szFullPath, RTLD_NOW | RTLD_GLOBAL);
#endif

	if( !hModule ) {
		Msg("[SP-LOADER] Could not load library: %s\n", libraryPath);
		return hModule;
	}

	return hModule;
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is loaded, load the interface we need from the engine
//---------------------------------------------------------------------------------
bool CSourcePython::Load( CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory )
{
    Msg("[Source.Python] Loading...\n");

	IVEngineServer* engine = (IVEngineServer*)interfaceFactory(INTERFACEVERSION_VENGINESERVER, NULL);

	// ------------------------------------------------------------------
	// Build path to python engines directory.
	// ------------------------------------------------------------------
	char szGameDir[1024];
	char szPythonHome[1024];
	char szPythonEngine[1024];
	char szSourcePython[1024];

	// ------------------------------------------------------------------
	// Get the game directory.
	// ------------------------------------------------------------------
	engine->GetGameDir(szGameDir, 1024);

	// ------------------------------------------------------------------
	// Load windows dependencies.
	// ------------------------------------------------------------------
#if defined(_WIN32)
	if( SPLoadLibrary(engine, MSVCRT_LIB) == NULL ) {
		return false;
	}

	if( SPLoadLibrary(engine, MSVCP_LIB) == NULL ) {
		return false;
	}
#endif

	// ------------------------------------------------------------------
	// Construct paths to python and the core.
	// ------------------------------------------------------------------
	V_snprintf(szPythonHome, 1024, "%s/addons/source-python", szGameDir);
	V_snprintf(szSourcePython, sizeof(szSourcePython), "%s/%s", szPythonHome, CORE_NAME);
	V_snprintf(szPythonEngine, sizeof(szPythonEngine), "%s/%s", szPythonHome, PYLIB_NAME);

	V_FixSlashes(szSourcePython);
	V_FixSlashes(szPythonEngine);
	
	// ------------------------------------------------------------------
	// Load python.
	// ------------------------------------------------------------------
#ifdef _WIN32
	m_pPython = Sys_LoadModule(szPythonEngine);
#else
	// This little gem cost me an entire thursday and a night's worth of
	// sleep. Sys_LoadModule calls dlopen(lib, RTLD_NOW). Because it omits
	// RTLD_GLOBAL, when Core.so decides to load, it is unable to relocate
	// python's symbols correctly causing PyThreadState_GET() to fail!
	// Long story short, we need RTLD_NOW coupled with RTLD_GLOBAL.
	m_pPython = (CSysModule *)dlopen(szPythonEngine, RTLD_NOW | RTLD_GLOBAL);
#endif

	if( !m_pPython ) {
		Warning("===========================================\n");
		Warning("[SP-LOADER] Could not load %s!\n", szPythonEngine);
		Warning("===========================================\n");
		return false;
	}

	// ------------------------------------------------------------------
	// Load the Source.Python core.
	// ------------------------------------------------------------------
	m_pCore = new CDllDemandLoader(szSourcePython);

	if( !m_pCore->GetFactory() ) {
		Warning("===========================================\n");
		Warning("[SP-LOADER] Could not load the %s!\n", szSourcePython);
		Warning("===========================================\n");
		return false;
	}

	// Get the interface from it.
	m_pCorePlugin = reinterpret_cast<IServerPluginCallbacks*>(
		m_pCore->GetFactory()(INTERFACEVERSION_ISERVERPLUGINCALLBACKS, NULL)
		);

	if( !m_pCorePlugin ) {
		Warning("=========================================================================\n");
		Warning("[SP-LOADER] Could not retrieve the server plugin interface from the core!\n");
		Warning("=========================================================================\n");
		return false;
	}

	// Pass it on.
	return m_pCorePlugin->Load(interfaceFactory, gameServerFactory);
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is unloaded (turned off)
//---------------------------------------------------------------------------------
void CSourcePython::Unload( void )
{
	m_pCorePlugin->Unload();
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is paused (i.e should stop running but isn't unloaded)
//---------------------------------------------------------------------------------
void CSourcePython::Pause( void )
{
	m_pCorePlugin->Pause();
}

//---------------------------------------------------------------------------------
// Purpose: called when the plugin is unpaused (i.e should start executing again)
//---------------------------------------------------------------------------------
void CSourcePython::UnPause( void )
{
	m_pCorePlugin->UnPause();
}

//---------------------------------------------------------------------------------
// Purpose: the name of this plugin, returned in "plugin_print" command
//---------------------------------------------------------------------------------
const char *CSourcePython::GetPluginDescription( void )
{
	return m_pCorePlugin->GetPluginDescription();
}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void CSourcePython::LevelInit( char const *pMapName )
{
	m_pCorePlugin->LevelInit(pMapName);
}

//---------------------------------------------------------------------------------
// Purpose: called on level start, when the server is ready to accept client connections
//		edictCount is the number of entities in the level, clientMax is the max client count
//---------------------------------------------------------------------------------
void CSourcePython::ServerActivate( edict_t *pEdictList, int edictCount, int clientMax )
{
	m_pCorePlugin->ServerActivate(pEdictList, edictCount, clientMax);
}

//---------------------------------------------------------------------------------
// Purpose: called once per server frame, do recurring work here (like checking for timeouts)
//---------------------------------------------------------------------------------
void CSourcePython::GameFrame( bool simulating )
{
	m_pCorePlugin->GameFrame(simulating);
}

//---------------------------------------------------------------------------------
// Purpose: called on level end (as the server is shutting down or going to a new map)
//---------------------------------------------------------------------------------
void CSourcePython::LevelShutdown( void ) // !!!!this can get called multiple times per map change
{
	m_pCorePlugin->LevelShutdown();
}

//---------------------------------------------------------------------------------
// Purpose: called when a client spawns into a server (i.e as they begin to play)
//---------------------------------------------------------------------------------
void CSourcePython::ClientActive( edict_t *pEntity )
{
	m_pCorePlugin->ClientActive(pEntity);
}

//---------------------------------------------------------------------------------
// Purpose: called when a client leaves a server (or is timed out)
//---------------------------------------------------------------------------------
void CSourcePython::ClientDisconnect( edict_t *pEntity )
{
	m_pCorePlugin->ClientDisconnect(pEntity);
}

//---------------------------------------------------------------------------------
// Purpose: called on 
//---------------------------------------------------------------------------------
void CSourcePython::ClientPutInServer( edict_t *pEntity, char const *playername )
{
	m_pCorePlugin->ClientPutInServer(pEntity, playername);
}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void CSourcePython::SetCommandClient( int index )
{
	m_pCorePlugin->SetCommandClient(index);
}

//---------------------------------------------------------------------------------
// Purpose: called on level start
//---------------------------------------------------------------------------------
void CSourcePython::ClientSettingsChanged( edict_t *pEdict )
{
	m_pCorePlugin->ClientSettingsChanged(pEdict);
}

//---------------------------------------------------------------------------------
// Purpose: called when a client joins a server
//---------------------------------------------------------------------------------
PLUGIN_RESULT CSourcePython::ClientConnect( bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen )
{
	return m_pCorePlugin->ClientConnect(bAllowConnect, pEntity, pszName, pszAddress, reject, maxrejectlen);
}

//---------------------------------------------------------------------------------
// Purpose: called when a client is authenticated
//---------------------------------------------------------------------------------
PLUGIN_RESULT CSourcePython::NetworkIDValidated( const char *pszUserName, const char *pszNetworkID )
{
	return m_pCorePlugin->NetworkIDValidated(pszUserName, pszNetworkID);
}

//---------------------------------------------------------------------------------
// Purpose: called when a cvar value query is finished
//---------------------------------------------------------------------------------
void CSourcePython::OnQueryCvarValueFinished( QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, 
	EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue )
{
	m_pCorePlugin->OnQueryCvarValueFinished(iCookie, pPlayerEntity, eStatus, pCvarName, pCvarValue);
}

//---------------------------------------------------------------------------------
// Orangebox.
//---------------------------------------------------------------------------------
#if(SOURCE_ENGINE >= 1)
PLUGIN_RESULT CSourcePython::ClientCommand( edict_t *pEntity, const CCommand &args )
#else
PLUGIN_RESULT CSourcePython::ClientCommand( edict_t* pEntity )
#endif
{
	return m_pCorePlugin->ClientCommand(pEntity, args);
}

//---------------------------------------------------------------------------------
// Alien Swarm.
//---------------------------------------------------------------------------------
#if(SOURCE_ENGINE >= 3)
void CSourcePython::ClientFullyConnect( edict_t *pEntity )
{
	m_pCorePlugin->ClientFullyConnect(pEntity);
}

void CSourcePython::OnEdictAllocated( edict_t *edict )
{
	m_pCorePlugin->OnEdictAllocated(edict);
}

void CSourcePython::OnEdictFreed( const edict_t *edict )
{
	m_pCorePlugin->OnEdictFreed(edict);
}
#endif
