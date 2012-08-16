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
#ifndef _SP_UTIL_H
#define _SP_UTIL_H

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "eiface.h"
#include "public/game/server/iplayerinfo.h"

//---------------------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------------------
extern IVEngineServer* engine;
extern CGlobalVars*	   gpGlobals;
extern IPlayerInfoManager* playerinfomanager;

//---------------------------------------------------------------------------------
// Returns the index of an entity.
//---------------------------------------------------------------------------------
inline int IndexOfEdict(const edict_t* pEdict) 
{
	return (int)(pEdict - gpGlobals->pEdicts);
}

inline edict_t* PEntityOfEntIndex(int iEntIndex)
{
	if(iEntIndex >= 0 && iEntIndex < gpGlobals->maxEntities) 
	{
		return (edict_t *)(gpGlobals->pEdicts + iEntIndex);	
	}

	return NULL;
}

//---------------------------------------------------------------------------------
// Returns the edict instance given a userid
//---------------------------------------------------------------------------------
inline edict_t* EdictOfUserid(int userid)
{
	edict_t* pEdict;
	for(int i=1; i <= gpGlobals->maxClients; ++i)
	{
		pEdict = PEntityOfEntIndex(i);
		if (pEdict && !pEdict->IsFree() &&
			strcmp(pEdict->GetClassName(), "player") == 0 &&
			engine->GetPlayerUserId(pEdict) == userid)
		{
			return pEdict;
		}
	}

	return NULL;
}

//---------------------------------------------------------------------------------
// Returns the playerinfo instance given a userid
//---------------------------------------------------------------------------------
inline IPlayerInfo* PlayerOfUserid(int userid)
{
	edict_t* pEdict = EdictOfUserid(userid);
	if (!pEdict)
	{
		return NULL;
	}

	return playerinfomanager->GetPlayerInfo(pEdict);
}

//---------------------------------------------------------------------------------
// Returns the playerinfo instance given a player(entity) index
//---------------------------------------------------------------------------------
inline IPlayerInfo* PlayerOfIndex(int index)
{
	if (index < 1 || index > gpGlobals->maxClients)
	{
		return NULL;
	}

	edict_t* pEdict = PEntityOfEntIndex(index);
	if (pEdict && !pEdict->IsFree() &&
		strcmp(pEdict->GetClassName(), "player") == 0)
	{
		return playerinfomanager->GetPlayerInfo(pEdict);
	}

	return NULL;
}

#endif