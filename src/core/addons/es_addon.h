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
#ifndef _ES_ADDON_H
#define _ES_ADDON_H

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "core/es_python.h"
#include "utllinkedlist.h"
#include "igameevents.h"

//---------------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------------
#define MAX_ADDON_NAME 64

//---------------------------------------------------------------------------------
// The addon class.
//---------------------------------------------------------------------------------
class CAddon
{
	private:
		bool			m_bIsLoaded;
		char			m_szAddonName[MAX_ADDON_NAME];
		python::dict	m_Namespace;

	public:
		CAddon( char* szAddonName );
		~CAddon( void );

		python::dict&	GetNamespace( void ) { 
			return m_Namespace; 
		}
		
		void			PrintInfo( void );
		
		bool			Load( void );
		bool			Unload( void );
		
		char*			GetName( void );
};

//---------------------------------------------------------------------------------
// Addon manager.
//---------------------------------------------------------------------------------
class CAddonManager
{
	private:
		CUtlLinkedList<CAddon *> m_Addons;

	public:
		~CAddonManager( void );

		// Addon functionality.
		bool LoadAddon( char* szName );
		bool UnloadAddon( char* szName );
		void PrintAddons( void );

		// Required by IGameEventListener2.
		void FireGameEvent( IGameEvent* event );
};

//---------------------------------------------------------------------------------
// Static singleton.
//---------------------------------------------------------------------------------
extern CAddonManager g_AddonManager;

#endif // _ES_ADDON_H