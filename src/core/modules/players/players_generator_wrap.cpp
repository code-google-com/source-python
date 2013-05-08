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

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#include "players_generator_wrap.h"
#include "players_wrap.h"
#include "utility/sp_util.h"
#include "game/server/iplayerinfo.h"
#include "boost/python/iterator.hpp"

// ----------------------------------------------------------------------------
// External variables.
// ----------------------------------------------------------------------------
extern IPlayerInfoManager* playerinfomanager;

// ----------------------------------------------------------------------------
// Players Constructor.
// ----------------------------------------------------------------------------
Players::Players( PyObject* self ):
	IPythonGenerator<CPlayerInfo>(self),
	m_iEntityIndex(0)
{
}

// ----------------------------------------------------------------------------
// Players Copy-Constructor.
// ----------------------------------------------------------------------------
Players::Players( PyObject* self, const Players& rhs ):
	IPythonGenerator<CPlayerInfo>(self),
	m_iEntityIndex(rhs.m_iEntityIndex)
{
}

// ----------------------------------------------------------------------------
// Players Destructor.
// ----------------------------------------------------------------------------
Players::~Players()
{
}

// ----------------------------------------------------------------------------
// Returns the next valid CPlayerInfo instance.
// ----------------------------------------------------------------------------
CPlayerInfo* Players::getNext()
{
	IPlayerInfo* pIPlayerInfo = NULL;
	CPlayerInfo* pPlayerInfo = NULL;
	while(m_iEntityIndex < gpGlobals->maxClients)
	{
		m_iEntityIndex++;
		edict_t* edict = PEntityOfEntIndex(m_iEntityIndex);
		IPlayerInfo* pIPlayerInfo = playerinfomanager->GetPlayerInfo(edict);
		if ( !pIPlayerInfo )
		{
			pIPlayerInfo = NULL;
		}
		else
		{
			CPlayerInfo* nPlayerInfo = new CPlayerInfo(pIPlayerInfo);
			pPlayerInfo = nPlayerInfo;
			return pPlayerInfo;
		}
	}
	return NULL;
}
