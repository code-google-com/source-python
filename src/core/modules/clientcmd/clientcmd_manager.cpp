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
#include "clientcmd_manager.h"
#include "boost/python/call.hpp"
#include "boost/shared_array.hpp"

//---------------------------------------------------------------------------------
// Global client command collections
//---------------------------------------------------------------------------------
typedef boost::unordered_map<std::string, ClientCommandManager*> ClientCommandMap;
ClientCommandMap g_ClientCommandMap;

//---------------------------------------------------------------------------------
// Returns a client command manager given the command name. If one does not exist,
// it will create one.
//---------------------------------------------------------------------------------
ClientCommandManager* GetClientCommand(const char* szName)
{
	ClientCommandMap::iterator commandMapIter = g_ClientCommandMap.find(szName);
	if (commandMapIter == g_ClientCommandMap.end())
	{
		g_ClientCommandMap.insert(std::make_pair(szName, new ClientCommandManager()));
		commandMapIter = g_ClientCommandMap.find(szName);
	}

	return commandMapIter->second;
}

//---------------------------------------------------------------------------------
// Removes a client command manager instance given its command name.
//---------------------------------------------------------------------------------
void RemoveClientCommand(const char* szName)
{
	ClientCommandMap::iterator commandMapIter = g_ClientCommandMap.find(szName);
	if (commandMapIter != g_ClientCommandMap.end())
	{
		delete commandMapIter->second;
		g_ClientCommandMap.erase(commandMapIter);
	}
}

//---------------------------------------------------------------------------------
// Dispatches a client command to a specific client command manager, given the
// first argument in the command parameter passed.
//---------------------------------------------------------------------------------
PLUGIN_RESULT DispatchClientCommand(edict_t *pEntity, const CCommand &command)
{
	const char* szCommand = command.Arg(0);
	ClientCommandMap::iterator commandMapIter = g_ClientCommandMap.find(szCommand);
	if (commandMapIter != g_ClientCommandMap.end())
	{
		ClientCommandManager* pClientCommandManager = commandMapIter->second;
		switch (pClientCommandManager->Dispatch(pEntity, command))
		{
		case BLOCK:
			return PLUGIN_STOP;
			break;
		case CONTINUE:
			return PLUGIN_CONTINUE;
			break;
		}
	}
	return PLUGIN_CONTINUE;
}

//---------------------------------------------------------------------------------
// Removes all client command manager instances.
//---------------------------------------------------------------------------------
void ClearAllClientCommands()
{
	for(ClientCommandMap::iterator commandMapIter = g_ClientCommandMap.begin(); commandMapIter != g_ClientCommandMap.end(); ++commandMapIter)
	{
		delete commandMapIter->second;
	}
	g_ClientCommandMap.clear();
}

//---------------------------------------------------------------------------------
// ClientCommandManager C'tor. Is kept private so they cannot be directly
// instanced.
//---------------------------------------------------------------------------------
ClientCommandManager::ClientCommandManager()
{
}

//---------------------------------------------------------------------------------
// ClientCommandManager D'tor.
//---------------------------------------------------------------------------------
ClientCommandManager::~ClientCommandManager()
{
}

//---------------------------------------------------------------------------------
// ClientCommandManager Dispatch function. Will loop through all of the Python
// callables and call them.
//---------------------------------------------------------------------------------
ClientCommandReturn ClientCommandManager::Dispatch(edict_t *pEntity, const CCommand &command)
{
	//Create a reference wrap around the command instance passed (as we will be passing this over the boundary in a moment).
	boost::reference_wrapper<const CCommand> pyCommand = boost::ref(command);
	boost::python::pointer_wrapper<edict_t*> pyEntity = boost::python::pointer_wrapper<edict_t*>(pEntity);
	unsigned int uiIndex = 0;

	//Loop through the vector of callable objects.
	for(std::vector<PyObject*>::const_iterator iterCallable = m_vecCallables.begin(); iterCallable != m_vecCallables.end(); ++iterCallable)
	{
		//Try calling the callable, which should return an integer value determining whether this loop should continue or not. Failing to return a value
		//or causing an Exception will be interpreted as a ClientCommandReturn.BLOCK value.
		BEGIN_BOOST_PY()
			object returnValue = call<object>(*iterCallable, pyEntity, pyCommand);	
			if (returnValue.is_none() || extract<int>(returnValue) == (int)BLOCK)
			{
				return BLOCK;
			}
		END_BOOST_PY_NORET()	
	}

	return CONTINUE;
}

//---------------------------------------------------------------------------------
// ClientCommandManager AddToStart function. Will add a Python callable right to
// the start of the vector, meaning it will be the first to be called (unless
// another callable gets added to the front afterwards).
//---------------------------------------------------------------------------------
void ClientCommandManager::AddToStart(PyObject* pCallable)
{
	m_vecCallables.insert(m_vecCallables.begin(), pCallable);
}

//---------------------------------------------------------------------------------
// ClientCommandManager AddToEnd function. The opposite of AddToStart. Will be
// called last in the vector.
//---------------------------------------------------------------------------------
void ClientCommandManager::AddToEnd(PyObject* pCallable)
{
	m_vecCallables.push_back(pCallable);
}

//---------------------------------------------------------------------------------
// ClientCommandManager Remove function. Removes the callable from the vector.
//---------------------------------------------------------------------------------
void ClientCommandManager::Remove(PyObject* pCallable)
{
	unsigned int uiCallableIndex = 0;
	for(uiCallableIndex = 0; uiCallableIndex < m_vecCallables.size(); ++uiCallableIndex)
	{
		if (m_vecCallables[uiCallableIndex] == pCallable)
		{
			m_vecCallables.erase(m_vecCallables.begin() + uiCallableIndex);
			break;
		}
	}
}

//---------------------------------------------------------------------------------
// Exports ClientCommandManager
//---------------------------------------------------------------------------------
void Export_ClientCommandManager( void )
{
	// ----------------------------------------------------------
	// Expose the CommandReturn enum
	// ----------------------------------------------------------
	enum_<ClientCommandReturn>("ClientCommandReturn")
		.value("CONTINUE", CONTINUE)
		.value("BLOCK", BLOCK)
		;

	// ----------------------------------------------------------
	// Expose the ClientCommandManager class
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(ClientCommandManager)
		CLASS_METHOD(ClientCommandManager,
			AddToStart,
			"Adds a callable to the start of the command queue.",
			args("pCallable")
		)
		CLASS_METHOD(ClientCommandManager,
			AddToEnd,
			"Adds a callable to the end of the command queue.",
			args("pCallable")
		)
		CLASS_METHOD(ClientCommandManager,
			Remove,
			"Removes a callable from the command queue.",
			args("pCallable")
		)
	BOOST_END_CLASS()
	
	// ----------------------------------------------------------
	// Expose GetCommand function
	// ----------------------------------------------------------
	BOOST_FUNCTION(GetClientCommand,
		"Gets the client command manager given the specific command name. Will create a client command manager if one does not yet exist.",
		args("szName"),
		reference_existing_object_policy());

	// ----------------------------------------------------------
	// Expose RemoveClientCommand function
	// ----------------------------------------------------------
	BOOST_FUNCTION(RemoveClientCommand,
		"Removes the client command manager given the specific command name.",
		args("szName"));
}