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
#include "../export_main.h"
#include "irecipientfilter.h"
#include "eiface.h"
#include "utility/wrap_macros.h"
#include "utility/sp_util.h"
#include "core/sp_python.h"
#include "engine/IEngineSound.h"
#include "engine/IEngineTrace.h"
#include "inetchannelinfo.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern IVEngineServer* engine;

//---------------------------------------------------------------------------------
// Returns the engine instance.
//---------------------------------------------------------------------------------
IVEngineServer* GetEngine( void )
{
	return engine;
}

//---------------------------------------------------------------------------------
// This is required because we can't wrap variadic functions with boost.
//---------------------------------------------------------------------------------
void Engine_ClientCommand( edict_t* pEdict, const char* szMsg ) 
{
	engine->ClientCommand(pEdict, szMsg);
}

//---------------------------------------------------------------------------------
// IVEngineServer overloads
//---------------------------------------------------------------------------------
DECLARE_CLASS_METHOD_OVERLOAD(IVEngineServer, PrecacheModel, 1, 2);
DECLARE_CLASS_METHOD_OVERLOAD(IVEngineServer, PrecacheSentenceFile, 1, 2);
DECLARE_CLASS_METHOD_OVERLOAD(IVEngineServer, PrecacheDecal, 1, 2);
DECLARE_CLASS_METHOD_OVERLOAD(IVEngineServer, PrecacheGeneric, 1, 2);

//---------------------------------------------------------------------------------
// This function exports engine IVEngineServer
//---------------------------------------------------------------------------------
void Export_IVEngineServer( void )
{
	// ----------------------------------------------------------
	// The engine interface.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS( IVEngineServer )

		CLASS_METHOD(IVEngineServer, 
			ChangeLevel,
			"Tells the engine to change the level. If s2 is None, the engine will execute a \
			changelevel command. If s2 is a valid map, the engine will execute a changelevel2 \
			command",
			args("s1", "s2")
		)

		CLASS_METHOD(IVEngineServer, 
			IsMapValid, 
			"Returns true if filename refers to a valid map.", 
			args("filename")
		)

		CLASS_METHOD(IVEngineServer, 
			IsDedicatedServer, 
			"Returns true if the engine is running in dedicated mode."
		)
		
		CLASS_METHOD(IVEngineServer, 
			IsInEditMode, 
			"Returns false if the engine is not in hammer editing mode."
		)

		CLASS_METHOD_OVERLOAD(IVEngineServer, 
			PrecacheModel, 
			"Precaches a model and returns an integer containing its index.",
			args("s", "preload")
		)

		CLASS_METHOD_OVERLOAD(IVEngineServer,
			PrecacheSentenceFile,
			"Precaches a sentence file and returns an integer containing its index.",
			args("s", "preload")
		)

		CLASS_METHOD_OVERLOAD(IVEngineServer,
			PrecacheDecal,
			"Precaches a decal file and returns an integer containing its index.",
			args("name", "preload")
		)

		CLASS_METHOD_OVERLOAD(IVEngineServer,
			PrecacheGeneric,
			"Precaches a generic asset file and returns an integer containing its index.",
			args("s", "preload")
		)

		CLASS_METHOD(IVEngineServer,
			IsModelPrecached,
			"Returns true if the given model is precached.",
			args("s")
		)

		CLASS_METHOD(IVEngineServer,
			IsDecalPrecached,
			"Returns true if the given decal is precached.",
			args("s")
		)

		CLASS_METHOD(IVEngineServer,
			IsGenericPrecached,
			"Returns true if the given generic asset is precached.",
			args("s")
		)

		CLASS_METHOD(IVEngineServer,
			GetClusterForOrigin,
			"Returns the cluster number for the specified position.",
			args("origin")
		)

		CLASS_METHOD(IVEngineServer,
			GetPVSForCluster,
			"Gets the PVS bits for a specified cluster and copies the bits into outputpvs.",
			args("cluster", "outputpvslength", "outputpvs")
		)

		CLASS_METHOD(IVEngineServer,
			CheckOriginInPVS,
			"Check whether the specified origin is inside the PVS",
			args("org", "checkpvs", "checkpvssize")
		)

		CLASS_METHOD(IVEngineServer,
			CheckBoxInPVS,
			"Checks whether the specified worldspace bounding box is inside the specified PVS",
			args("mins", "maxs", "checkpvs", "checkpvssize")
		)

		CLASS_METHOD(IVEngineServer,
			GetPlayerUserId,
			"Returns the server assigned userid for this player. Returns -1 if the edict could not \
			be found.",
			args("playerInstance")
		)

		CLASS_METHOD(IVEngineServer,
			GetPlayerNetworkIDString,
			"Returns the player's network id as a string.",
			args("playerInstance")
		)

		CLASS_METHOD(IVEngineServer,
			GetEntityCount,
			"Returns the number of used edict slots."
		)

		CLASS_METHOD(IVEngineServer,
			GetPlayerNetInfo,
			"Returns stats info interface for a client netchannel.",
			args("playerIndex"),
			reference_existing_object_policy()
		)

		CLASS_METHOD(IVEngineServer,
			CreateEdict,
			"Creates an edict. If iForceEdictIndex is not -1, then it return the edict with that index.",
			args("iForceEdictIndex"),
			reference_existing_object_policy()
		)

		CLASS_METHOD(IVEngineServer,
			RemoveEdict,
			"Remove the specified edict and place back into the free edict list.",
			args("edictInstance")
		)

		CLASS_METHOD(IVEngineServer,
			ServerCommand,
			"Issues a command to the command parser as if it was typed at the server console.",
			args("command")
		)

		CLASS_METHOD(IVEngineServer,
			ServerExecute,
			"Executes any commands currently in the command parser immediately (instead of once per frame).",
			args("command")
		)

		// Note: This is requierd because we can't wrap variadic functions correctly.
		CLASS_METHOD_TYPEDEF("ClientCommand",
			Engine_ClientCommand,
			"Runs a command on the client.",
			args("pEdict", "szCmd")
		)

		CLASS_METHOD(IVEngineServer,
			LightStyle,
			"Set the lightstyle to the specified value and network the change to any connected clients.",
			args("style", "val")
		)

		CLASS_METHOD(IVEngineServer,
			StaticDecal,
			"Project a static decal onto the specified entity / model (for level placed decals in the .bsp)",
			args("originInEntitySpace", "decalIndex", "entityIndex", "modelIndex", "bLowPriority")
		)

		// TODO: Message_DetermineMulticastRecipients

		CLASS_METHOD(IVEngineServer,
			UserMessageBegin,
			"Begin a message from the server to the client.dll",
			args("filter", "msg_type", "msgname"),
			reference_existing_object_policy()
			)

		CLASS_METHOD(IVEngineServer,
			MessageEnd,
			"Finish entity or user message and dispatch it.",
			reference_existing_object_policy()
		)

		CLASS_METHOD(IVEngineServer,
			ClientPrintf,
			"Prints the message to the console of the given client.",
			args("pEdict", "szMsg")
		)

        CLASS_METHOD(IVEngineServer,
            GetClientConVarValue,
            "Get a convar keyvalue for a specific client",
            args("clientIndex", "name")
        )

#if( SOURCE_ENGINE >= 2 )
		CLASS_METHOD(IVEngineServer, 
			GetLaunchOptions, 
			"Returns a keyvalues structure containing launch options for srcds.",
			reference_existing_object_policy()
		)

		CLASS_METHOD(IVEngineServer,
			IsUserIDInUse,
			"Returns true if the userid given is in use.",
			args("userID")
		)

		CLASS_METHOD(IVEngineServer,
			GetLoadingProgressForUserID,
			"Returns percentage complete a player is while loading.",
			args("userID")
		)
#endif

	BOOST_END_CLASS()

    BOOST_ABSTRACT_CLASS(INetChannelInfo)
        CLASS_METHOD(INetChannelInfo,
            GetAddress,
            "Returns the IP address as a string."
        )

        CLASS_METHOD(INetChannelInfo,
            GetTimeConnected,
            "Returns the connection time (in seconds)."
        )

    BOOST_END_CLASS()

	// Functions
	BOOST_FUNCTION(GetEngine, reference_existing_object_policy());
}