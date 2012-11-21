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
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "igameevents.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern IGameEventManager2* gameeventmanager;

//---------------------------------------------------------------------------------
// Returns the gameeventmanager interface.
//---------------------------------------------------------------------------------
IGameEventManager2* GetGameEventManager( void )
{
	return gameeventmanager;
}

//---------------------------------------------------------------------------------
// IGameEvent overloads.
//---------------------------------------------------------------------------------
DECLARE_CLASS_METHOD_OVERLOAD(IGameEvent, IsEmpty, 0, 1)
DECLARE_CLASS_METHOD_OVERLOAD(IGameEvent, GetBool, 0, 2)
DECLARE_CLASS_METHOD_OVERLOAD(IGameEvent, GetInt, 0, 2)
DECLARE_CLASS_METHOD_OVERLOAD(IGameEvent, GetUint64, 0, 2)
DECLARE_CLASS_METHOD_OVERLOAD(IGameEvent, GetFloat, 0, 2)
DECLARE_CLASS_METHOD_OVERLOAD(IGameEvent, GetString, 0, 2)

//---------------------------------------------------------------------------------
// IGameEventManager overloads.
//---------------------------------------------------------------------------------
#if( SOURCE_ENGINE >= 2 )
DECLARE_CLASS_METHOD_OVERLOAD(IGameEventManager2, CreateEvent, 1, 3)
#else
DECLARE_CLASS_METHOD_OVERLOAD(IGameEventManager2, CreateEvent, 1, 2)
#endif
DECLARE_CLASS_METHOD_OVERLOAD(IGameEventManager2, FireEvent, 1, 2)

//---------------------------------------------------------------------------------
// Wraps game events related structures.
//---------------------------------------------------------------------------------
DECLARE_SP_MODULE(Event)
{
	// ----------------------------------------------------------
	// do the submodule handling here.
	// ----------------------------------------------------------

	// ----------------------------------------------------------
	// Wrap the game event structure.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS( IGameEvent )
		CLASS_METHOD(IGameEvent, GetName,		"Returns the name of the event")
		
		CLASS_METHOD(IGameEvent, IsReliable,	"True if the event was handled reliably.")
		CLASS_METHOD(IGameEvent, IsLocal,		"True if the event is never networked.")
		
		CLASS_METHOD_OVERLOAD(IGameEvent, 
			IsEmpty,
			"Checks to see if the given key exists.", 
			args("keyName")
		)
		
		CLASS_METHOD_OVERLOAD(IGameEvent, GetBool, 
			"Returns given key's value as a boolean.",
			args("keyName", "defaultValue")
		)

		CLASS_METHOD_OVERLOAD(IGameEvent, 
			GetInt,
			"Returns given key's value as an integer.",
			args("keyName", "defaultValue")
		)

		CLASS_METHOD_OVERLOAD(IGameEvent, 
			GetFloat,
			"Returns given key's value as a floating point.",
			args("keyName", "defaultValue")
		)

		CLASS_METHOD_OVERLOAD(IGameEvent, 
			GetString,
			"Returns given key's value as a string.",
			args("keyName", "defaultValue")
		)

		CLASS_METHOD(IGameEvent, 
			SetBool,
			"Sets given key's value as a boolean.",
			args("keyName", "value")
		)

		CLASS_METHOD(IGameEvent, 
			SetInt,
			"Sets given key's value as an integer.",
			args("keyName", "value")
		)

		CLASS_METHOD(IGameEvent,
			SetFloat,
			"Sets given key's value as a floating point.",
			args("keyName", "value")
		)

		CLASS_METHOD(IGameEvent, 
			SetString, 
			"Sets given key's value as a string.",
			args("keyName", "value")
		)

#if( SOURCE_ENGINE >= 2 )
		CLASS_METHOD_OVERLOAD(IGameEvent, GetUint64,
			"Returns given key's value as a 64-bit integer.",
			args("keyName", "defaultValue")
		)

		CLASS_METHOD(IGameEvent,
			SetUint64,
			"Sets given key's value as a 64-bit integer.",
			args("keyName", "value")
		)
#endif


	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Wrap the game event manager.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS( IGameEventManager2 )
		CLASS_METHOD(IGameEventManager2, LoadEventsFromFile, 
			"Loads game event descriptions from a file.",
			args("filename")
		)
		
		// Note that CreateEvent returns a new IGameEvent structure, but if you fire it, it
		// will be freed. If you don't fire it, you must call FreeEvent.
		CLASS_METHOD_OVERLOAD_RET(IGameEventManager2, 
			CreateEvent, 
			"Creates an event instance. Custom events must have had a description loaded via LoadEventsFromFile.",
			args("name", "bForce", "pCookie"),
			reference_existing_object_policy()
		)

		CLASS_METHOD_OVERLOAD(IGameEventManager2, 
			FireEvent,
			"Fires off an event on the server. If bDontBroadcast is set to true, it will not fire on clients.",
			args("event", "bDontBroadcast")
		)

		// This duplicates an event and returns a new pointer to it. Must call FreeEvent
		// if you don't fire it.
		CLASS_METHOD(IGameEventManager2, 
			DuplicateEvent, 
			reference_existing_object_policy(),
			"Duplicates an IGameEvent instance. You must free this later using FreeEvent.",
			args("event")
		)

		CLASS_METHOD(IGameEventManager2, 
			FreeEvent, 
			"Frees an IGameEvent instance.",
			args("event")
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Expose the global interface to the event manager.
	// ----------------------------------------------------------
	BOOST_FUNCTION(GetGameEventManager, reference_existing_object_policy());
}