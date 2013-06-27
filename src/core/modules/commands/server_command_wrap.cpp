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

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "server_command_wrap.h"
#include "command_wrap.h"
#include "boost/python/call.hpp"
#include "boost/shared_array.hpp"

//-----------------------------------------------------------------------------
// Externs.
//-----------------------------------------------------------------------------
extern ICvar* g_pCVar;

//-----------------------------------------------------------------------------
// ConVar Accessor class and registration
//
// NOTE: This is used to ensure any new ConCommands created get registered to the
//	   active ICVar instance.
//-----------------------------------------------------------------------------
class CPluginConVarAccessor : public IConCommandBaseAccessor
{
public:
	virtual bool RegisterConCommandBase(ConCommandBase* pCommand)
	{
		g_pCVar->RegisterConCommand(pCommand);
		return true;
	}
};

CPluginConVarAccessor g_ConVarAccessor;

//-----------------------------------------------------------------------------
// Registers the ConVar accessor above to take in new ConCommand requests.
//-----------------------------------------------------------------------------
void InitServerCommands()
{
	ConVar_Register(0, &g_ConVarAccessor);
}

//-----------------------------------------------------------------------------
// Global server command mapping.
//-----------------------------------------------------------------------------
typedef boost::unordered_map<std::string, ServerCommandManager*> ServerCommandMap;
ServerCommandMap g_ServerCommandMap;

//-----------------------------------------------------------------------------
// Returns a ServerCommandManager for the given command name.
//-----------------------------------------------------------------------------
ServerCommandManager* get_server_command(const char* szName,
	const char* szHelpText = 0, int iFlags = 0)
{
	// Find if the given name is a registered server command
	ServerCommandMap::iterator commandMapIter = g_ServerCommandMap.find(szName);
	if( commandMapIter == g_ServerCommandMap.end())
	{
		// If the command is not already registered, add the name and the ServerCommandManager instance to the mapping
		g_ServerCommandMap.insert(std::make_pair(szName, ServerCommandManager::CreateCommand(szName, szHelpText, iFlags)));

		// Get the server command in the mapping
		commandMapIter = g_ServerCommandMap.find(szName);
	}

	// Return the ServerCommandManager instance for the command
	return commandMapIter->second;
}

//-----------------------------------------------------------------------------
// Removes a ServerCommandManager instance for the given name.
//-----------------------------------------------------------------------------
void RemoveServerCommandManager(const char* szName)
{
	// Find if the given name is a registered server command
	ServerCommandMap::iterator commandMapIter = g_ServerCommandMap.find(szName);
	if( commandMapIter != g_ServerCommandMap.end())
	{
		// If the command is registered, delete the ServerCommandManager instance
		//		and remove the command from the mapping
		delete commandMapIter->second;
		g_ServerCommandMap.erase(commandMapIter);
	}
}

//-----------------------------------------------------------------------------
// Returns a ServerCommandManager instance.
//-----------------------------------------------------------------------------
ServerCommandManager* ServerCommandManager::CreateCommand(const char* szName,
	const char* szHelpText, int iFlags)
{
	// Copy the name and store a help text copier value
	char* szNameCopy = strdup(szName);
	char* szHelpTextCopy = NULL;

	// FInd if the command already exists
	ConCommand* pConCommand = g_pCVar->FindCommand(szName);
	if( pConCommand )
	{
		// Store the current command's help text and flags
		szHelpTextCopy = strdup(pConCommand->GetHelpText());
		iFlags = pConCommand->GetFlags();

		// Unregister the old command
		g_pCVar->UnregisterConCommand(pConCommand);
	}
	else
	{
		// Store the given help text
		szHelpTextCopy = strdup(szHelpText);
	}

	// Return a new instance of ConCommand
	return new ServerCommandManager(pConCommand, szNameCopy, szHelpTextCopy, iFlags);
}

//-----------------------------------------------------------------------------
// ServerCommandManager constructor.
//-----------------------------------------------------------------------------
ServerCommandManager::ServerCommandManager(ConCommand* pConCommand,
		const char* szName, const char* szHelpText, int iFlags):
	ConCommand(szName, (FnCommandCallback_t)NULL, szHelpText, iFlags),
	m_pOldCommand(pConCommand)
{
	m_Name = szName;
}

//-----------------------------------------------------------------------------
// ServerCommandManager destructor.
//-----------------------------------------------------------------------------
ServerCommandManager::~ServerCommandManager()
{
	// Get the ConCommand instance
	ConCommand* pConCommand = g_pCVar->FindCommand(m_Name);

	// Unregister the ConCommand
	g_pCVar->UnregisterConCommand(pConCommand);

	// Was the command registered before we registered it?
	if( m_pOldCommand )
	{
		// Re-register the old command instance
		g_pCVar->RegisterConCommand(m_pOldCommand);
	}
}

//-----------------------------------------------------------------------------
// ServerCommandManager Init override.
//-----------------------------------------------------------------------------
void ServerCommandManager::Init()
{
	ConCommand::Init();
}

//-----------------------------------------------------------------------------
// Adds a callable to a ServerCommandManager instance.
//-----------------------------------------------------------------------------
void ServerCommandManager::add_callback( PyObject* pCallable )
{
	// Get the object instance of the callable
	object oCallable = object(handle<>(borrowed(pCallable)));

	// Is the callable already in the vector?
	if( !m_vecCallables.HasElement(oCallable) )
	{
		// Add the callable to the vector
		m_vecCallables.AddToTail(oCallable);
	}
}

//-----------------------------------------------------------------------------
// Removes a callable from a ServerCommandManager instance.
//-----------------------------------------------------------------------------
void ServerCommandManager::remove_callback( PyObject* pCallable )
{
	// Get the object instance of the callable
	object oCallable = object(handle<>(borrowed(pCallable)));

	// Remove the callback from the ServerCommandManager instance
	m_vecCallables.FindAndRemove(oCallable);

	// Are there any more callbacks registered for this command?
	if( !m_vecCallables.Count() )
	{
		// Remove the ServerCommandManager instance
		RemoveServerCommandManager(m_Name);
	}
}

//-----------------------------------------------------------------------------
// Calls all callables for the command when it is called on the server.
//-----------------------------------------------------------------------------
void ServerCommandManager::Dispatch( const CCommand &command )
{
	// Get the CICommand instance for the CCommand instance
	CICommand* ccommand = new CICommand(&command);

	// Loop through all registered callbacks for the command
	// (use equals also to know when to call the old callback)
	for(int i = 0; i <= m_vecCallables.Count(); i++)
	{

		// Is the current iteration for a registered callback?
		if( i < m_vecCallables.Count() )
		{
			
			BEGIN_BOOST_PY()

				// Get the PyObject instance of the callable
				PyObject* pCallable = m_vecCallables[i].ptr();

				// Store a return value
				object returnValue;

				// Is the object an instance or class method?
				if(PyObject_HasAttrString(pCallable, "__self__"))
				{
					// Get the class' instance
					PyObject *oClassInstance = PyObject_GetAttrString(pCallable, "__self__");

					// Get the name of the method needed to be called
					PyObject *oMethodName = PyObject_GetAttrString(pCallable, "__name__");
					const char* szMethodName = extract<const char*>(oMethodName);

					// Call the callable
					returnValue = boost::python::call_method<object>(oClassInstance, szMethodName, ccommand);
				}

				else
				{
					// Call the callable
					returnValue = call<object>(pCallable, ccommand);
				}
				// Does the callable wish to block the command?
				if( !returnValue.is_none() && extract<int>(returnValue) == (int)BLOCK)
				{
					// Block the command
					break;
				}

			END_BOOST_PY_NORET()
		}

		// Was the command previously registered?
		else if(m_pOldCommand)
		{
			// Call the old callback
			m_pOldCommand->Dispatch(command);
		}
	}
}

//-----------------------------------------------------------------------------
// Removes all ServerCommandManager instances.
//-----------------------------------------------------------------------------
void ClearAllServerCommands()
{
	// Loop through all items in the mapping
	for(ServerCommandMap::iterator commandMapIter = g_ServerCommandMap.begin(); commandMapIter != g_ServerCommandMap.end(); ++commandMapIter)
	{
		// Remove the ServerCommandManager instance
		delete commandMapIter->second;
	}
	// Clear the mapping
	g_ServerCommandMap.clear();
}