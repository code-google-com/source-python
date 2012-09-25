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
#include "export_main.h"
#include "export_player.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "utility/sp_util.h"
#include "eiface.h"
#include "game/server/iplayerinfo.h"
#include "boost/python/iterator.hpp"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern IPlayerInfoManager* playerinfomanager;
extern IBotManager* botmanager;

//---------------------------------------------------------------------------------
// Returns the playerinfomanager instance.
//---------------------------------------------------------------------------------
IPlayerInfoManager* GetPlayerInfoManager( void )
{
	return playerinfomanager;
}

//---------------------------------------------------------------------------------
// Returns the botmanager instance.
//---------------------------------------------------------------------------------
IBotManager* GetBotManager( void )
{
	return botmanager;
}

//---------------------------------------------------------------------------------
// Players Constructor.
//---------------------------------------------------------------------------------
Players::Players(PyObject* self):
	IPythonGenerator<IPlayerInfo>(self),
	m_iEntityIndex(0)
{
}

//---------------------------------------------------------------------------------
// Players Copy-Constructor.
//---------------------------------------------------------------------------------
Players::Players(PyObject* self, const Players& rhs):
	IPythonGenerator<IPlayerInfo>(self),
	m_iEntityIndex(rhs.m_iEntityIndex)
{
}

//---------------------------------------------------------------------------------
// Players Destructor.
//---------------------------------------------------------------------------------
Players::~Players()
{
}

//---------------------------------------------------------------------------------
// Returns the next valid IPlayerInfo instance, or NULL if reached maxClients.
//---------------------------------------------------------------------------------
IPlayerInfo* Players::getNext()
{
	IPlayerInfo* pPlayerInfo = NULL;
	while(m_iEntityIndex < gpGlobals->maxClients && !pPlayerInfo)
	{
		m_iEntityIndex++;
		pPlayerInfo = playerinfomanager->GetPlayerInfo(PEntityOfEntIndex(m_iEntityIndex));
	}

	return pPlayerInfo;
}

//---------------------------------------------------------------------------------
// Wraps player related structures.
//---------------------------------------------------------------------------------
DECLARE_SP_MODULE(Player)
{
	// ----------------------------------------------------------
	// CBotCmd
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(CBotCmd)
		CLASS_MEMBER(CBotCmd,
			command_number,
			"The specific command number. For matching server and client commands for debugging."
		)

		CLASS_MEMBER(CBotCmd,
			tick_count,
			"The tick the client created this command."
		)

		CLASS_MEMBER(CBotCmd,
			viewangles,
			"The players instantaneous view angles."
		)

		CLASS_MEMBER(CBotCmd,
			forwardmove,
			"The intended forward velocity."
		)

		CLASS_MEMBER(CBotCmd,
			sidemove,
			"The intended sideways velocity."
		)

		CLASS_MEMBER(CBotCmd,
			upmove,
			"The intended upward velocity."
		)

		CLASS_MEMBER(CBotCmd,
			buttons,
			"The attack button states."
		)

		CLASS_MEMBER(CBotCmd,
			impulse,
			"The impulse command issued."
		)

		CLASS_MEMBER(CBotCmd,
			weaponselect,
			"The current weapon ID."
		)

		CLASS_MEMBER(CBotCmd,
			weaponsubtype,
			"The current weapon subtype ID."
		)

		CLASS_MEMBER(CBotCmd,
			random_seed,
			"The random seed used for shared random functions."
		)

		CLASS_MEMBER(CBotCmd,
			mousedx,
			"The mouse accumulation in the x direction from create move."
		)

		CLASS_MEMBER(CBotCmd,
			mousedy,
			"The mouse accumulation in the y direction from create move."
		)

		CLASS_MEMBER(CBotCmd,
			hasbeenpredicted,
			"(Client only) Tracks whether we've predicted this command at least once."
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// IPlayerInfo
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(IPlayerInfo)
		CLASS_METHOD(IPlayerInfo,
			GetName,
			"Returns the players name (UTF-8 encoded)."
		)

		CLASS_METHOD(IPlayerInfo,
			GetUserID,
			"Returns the userid (slot number)."
		)

		CLASS_METHOD(IPlayerInfo,
			GetNetworkIDString,
			"Returns the string of their network (i.e Steam) ID."
		)

		CLASS_METHOD(IPlayerInfo,
			GetTeamIndex,
			"Returns the team the player is on."
		)

		CLASS_METHOD(IPlayerInfo,
			ChangeTeam,
			"Changes the player to a new team (if the game dll logic allows it)",
			args("iTeamNum")
		)

		CLASS_METHOD(IPlayerInfo,
			GetFragCount,
			"Returns the number of kills this player has (exact meaning is mod dependent)."
		)

		CLASS_METHOD(IPlayerInfo,
			GetDeathCount,
			"Returns the number of deaths this player has (exact meaning is mod dependent)."
		)

		CLASS_METHOD(IPlayerInfo,
			IsConnected,
			"Returns if this player slot is actually valid."
		)

		CLASS_METHOD(IPlayerInfo,
			GetArmorValue,
			"Returns the armor/health of the player (exact meaning is mod dependent)."
		)

		CLASS_METHOD(IPlayerInfo,
			IsHLTV,
			"Returns true if this player slot is an HLTV slot."
		)

#if defined( REPLAY_ENABLED )
		CLASS_METHOD(IPlayerInfo,
			IsReplay,
			"Returns true if this player slot is a replay slot."
		)
#endif

		CLASS_METHOD(IPlayerInfo,
			IsPlayer,
			"Returns true if this player slot is actually a player."
		)

		CLASS_METHOD(IPlayerInfo,
			IsFakeClient,
			"Returns true if this player slot is a fake client."
		)

		CLASS_METHOD(IPlayerInfo,
			IsDead,
			"Returns true if the player is dead."
		)

		CLASS_METHOD(IPlayerInfo,
			IsInAVehicle,
			"Returns true if the player is in a vehicle."
		)

		CLASS_METHOD(IPlayerInfo,
			IsObserver,
			"Returns true if the player is an observer."
		)

		CLASS_METHOD(IPlayerInfo,
			GetAbsOrigin,
			"Returns the absolute origin of the player."
		)

		CLASS_METHOD(IPlayerInfo,
			GetAbsAngles,
			"Returns the absolute angles of the player."
		)

		CLASS_METHOD(IPlayerInfo,
			GetPlayerMins,
			"Returns the player's minimum extents."
		)

		CLASS_METHOD(IPlayerInfo,
			GetPlayerMaxs,
			"Returns the player's maximum extents."
		)

		CLASS_METHOD(IPlayerInfo,
			GetWeaponName,
			"Returns the name of the weapon currently being carried."
		)

		CLASS_METHOD(IPlayerInfo,
			GetModelName,
			"Returns the name of the player model in use."
		)

		CLASS_METHOD(IPlayerInfo,
			GetHealth,
			"Returns the current health of the player."
		)

		CLASS_METHOD(IPlayerInfo,
			GetMaxHealth,
			"Returns the maximum health of the player."
		)

		CLASS_METHOD(IPlayerInfo,
			GetLastUserCommand,
			"Returns the last user input from this player."
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// IPlayerInfoManager
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(IPlayerInfoManager)
		CLASS_METHOD(IPlayerInfoManager,
			GetPlayerInfo,
			"Returns the IPlayerInfo instance from an entity.",
			args("pEdict"),
			reference_existing_object_policy()
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// IBotController
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(IBotController)
		CLASS_METHOD(IBotController,
			SetAbsOrigin,
			"Sets the absolute origin of the bot.",
			args("vec")
		)

		CLASS_METHOD(IBotController,
			SetAbsAngles,
			"Sets the absolute angles of the bot.",
			args("ang")
		)

		CLASS_METHOD(IBotController,
			SetLocalOrigin,
			"Sets the local origin of the bot.",
			args("origin")
		)

		CLASS_METHOD(IBotController,
			GetLocalOrigin,
			"Gets the local origin of the bot."
		)

		CLASS_METHOD(IBotController,
			SetLocalAngles,
			"Sets the local angles of the bot.",
			args("angles")
		)

		CLASS_METHOD(IBotController,
			GetLocalAngles,
			"Gets the local angles of the bot."
		)

		CLASS_METHOD(IBotController,
			RemoveAllItems,
			"Strips the bot of all weapons.",
			args("removeSuit")
		)

		CLASS_METHOD(IBotController,
			SetActiveWeapon,
			"Gives the bot a weapon by a weapon name.",
			args("WeaponName")
		)

		CLASS_METHOD(IBotController,
			IsEFlagSet,
			"Returns true if certain effect flags are set.",
			args("nEFlagMask")
		)

		CLASS_METHOD(IBotController,
			RunPlayerMove,
			"Fires a virtual move command to the bot.",
			args("ucmd")
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// IBotManager
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(IBotManager)
		CLASS_METHOD(IBotManager,
			GetBotController,
			"Returns a bot controller given an entity dict.",
			args("pEdict"),
			reference_existing_object_policy()
		)
		CLASS_METHOD(IBotManager,
			CreateBot,
			"Create a new bot with the given name and spawn it into the server.",
			args("botname"),
			reference_existing_object_policy()
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Players (Generator)
	// ----------------------------------------------------------
	BOOST_GENERATOR_CLASS(Players)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Expose the global interface to the playerinfomanager.
	// ----------------------------------------------------------
	BOOST_FUNCTION(GetPlayerInfoManager, reference_existing_object_policy());

	// ----------------------------------------------------------
	// Expose the global interface to the botmanager.
	// ----------------------------------------------------------
	BOOST_FUNCTION(GetBotManager, reference_existing_object_policy());

	// ----------------------------------------------------------
	// Expose some player functions
	// ----------------------------------------------------------
	BOOST_FUNCTION(EdictOfUserid, 
		"Returns the edict for a userid.", 
		args("userid"),
		reference_existing_object_policy()
	);

	BOOST_FUNCTION(PlayerOfUserid,
        "Returns the IPlayerInfo instance for a userid.",
        args("userid"),
		reference_existing_object_policy()
    );

    BOOST_FUNCTION(IndexOfUserid,
        "Returns the index of a userid.",
        args("userid")
    );

	BOOST_FUNCTION(PlayerOfIndex,
        "Returns the IPlayerInfo instance for a player index.",
        args("index"),
		reference_existing_object_policy()
    );

	BOOST_FUNCTION(EdictOfPlayer,
		"Returns the edict for a IPlayerInfo instance.",
		args("playerInfo"),
		reference_existing_object_policy()
	);
}
