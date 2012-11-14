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
#include "cvar_concommand.h"
#include "boost/python/call.hpp"
#include "boost/shared_array.hpp"

//---------------------------------------------------------------------------------
// Extern variables
//---------------------------------------------------------------------------------
extern ICvar* g_pCVar;

//---------------------------------------------------------------------------------
// CommandReturn enum
//---------------------------------------------------------------------------------
enum CommandReturn
{
	CONTINUE = 0,
	BLOCK
};

//---------------------------------------------------------------------------------
// ConVar Accessor class and registration
//
// NOTE: This is used to ensure any new ConCommands created get registered to the
//       active ICVar instance.
//---------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------
// Registers the ConVar accessor above to take in new ConCommand requests.
//---------------------------------------------------------------------------------
void InitCVars()
{
	ConVar_Register(0, &g_ConVarAccessor);
}

//---------------------------------------------------------------------------------
// Global command collections
//---------------------------------------------------------------------------------
typedef boost::unordered_map<std::string, ConCommandManager*> CommandMap;
CommandMap g_CommandMap;

//---------------------------------------------------------------------------------
// Returns a command manager given the command name. If one does not exist, it
// will create one.
//---------------------------------------------------------------------------------
ConCommandManager* GetCommand(const char* szName, const char* szHelp = NULL, int iFlags = 0)
{
	CommandMap::iterator commandMapIter = g_CommandMap.find(szName);
	if (commandMapIter == g_CommandMap.end())
	{
		g_CommandMap.insert(std::make_pair(szName, ConCommandManager::CreateCommand(szName, szHelp, iFlags)));
		commandMapIter = g_CommandMap.find(szName);
	}

	return commandMapIter->second;
}
BOOST_PYTHON_FUNCTION_OVERLOADS(GetCommand_Overloads, GetCommand, 1, 3);

//---------------------------------------------------------------------------------
// Removes a command manager instance given its command name.
//---------------------------------------------------------------------------------
void RemoveCommand(const char* szName)
{
	CommandMap::iterator commandMapIter = g_CommandMap.find(szName);
	if (commandMapIter != g_CommandMap.end())
	{
		delete commandMapIter->second;
		g_CommandMap.erase(commandMapIter);
	}
}

//---------------------------------------------------------------------------------
// Removes all command manager instances.
//---------------------------------------------------------------------------------
void ClearAllCommands()
{
	for(CommandMap::iterator commandMapIter = g_CommandMap.begin(); commandMapIter != g_CommandMap.end(); ++commandMapIter)
	{
		delete commandMapIter->second;
	}
	g_CommandMap.clear();
}

//---------------------------------------------------------------------------------
// ConCommandManager [static] CreateCommand Function
//---------------------------------------------------------------------------------
ConCommandManager* ConCommandManager::CreateCommand(const char* pName, const char* pHelpString, int flags)
{
	//We need copies of the strings, since ConCommandBase instances just copy the pointer directly
	//If we were to declare these ConCommands in global scope in a Python module, they would fail
	//to function after 'import'ing the module, despite being valid instances.
	char* pNameCopy = strdup(pName);
	char* pHelpStringCopy = NULL;

	//We look for any existing ConCommands registered with the same name.
	ConCommand* pGameCommand = g_pCVar->FindCommand(pNameCopy);
	if (pGameCommand)
	{
		//If we find one, we unregister it (in preparation for us registering our own) and keep a copy
		//of the instance internally, so we can fire it off as part of our custom Dispatch function.
		pHelpStringCopy = strdup(pGameCommand->GetHelpText());
#if( SOURCE_ENGINE >= 2 )
		flags = pGameCommand->GetFlags();
#endif
		g_pCVar->UnregisterConCommand(pGameCommand);
	}
	else
	{
		pHelpStringCopy = strdup(pHelpString);
	}

	//Create and return a new ConCommandManager instance.
	return new ConCommandManager(pGameCommand, pNameCopy, pHelpStringCopy, flags);
}

//---------------------------------------------------------------------------------
// ConCommandManager C'tor. Is kept private so they cannot be directly instanced.
//---------------------------------------------------------------------------------
ConCommandManager::ConCommandManager(ConCommand* pGameCommand, const char* pName, const char* pHelpString, int flags):
	ConCommand(pName, (FnCommandCallback_t)NULL, pHelpString, flags),
	m_pGameCommand(pGameCommand),
	m_uiGameCommandIndex(0)
{
}

//---------------------------------------------------------------------------------
// ConCommandManager D'tor.
//---------------------------------------------------------------------------------
ConCommandManager::~ConCommandManager()
{
	//Unregister our own command.
	g_pCVar->UnregisterConCommand(this);
	if (m_pGameCommand)
	{
		//And if set, register the existing command.
		g_pCVar->RegisterConCommand(m_pGameCommand);
	}
}

//---------------------------------------------------------------------------------
// ConCommandManager Init override.
//---------------------------------------------------------------------------------
void ConCommandManager::Init()
{
	ConCommand::Init();
}

//---------------------------------------------------------------------------------
// ConCommandManager Dispatch override.
//---------------------------------------------------------------------------------
void ConCommandManager::Dispatch(const CCommand &command)
{
	//Create a reference wrap around the command instance passed (as we will be passing this over the boundary in a moment).
	boost::reference_wrapper<const CCommand> pyCommand = boost::ref(command);
	unsigned int uiIndex = 0;

	//If no extra commands registered, just call the internal existing command if set.
	if (m_vecCallables.Count() == 0 && m_pGameCommand)
	{
		m_pGameCommand->Dispatch(command);
	}
	else
	{
		//Loop through the vector of callable objects.
		// for(std::vector<PyObject*>::const_iterator iterCallable = m_vecCallables.begin(); iterCallable != m_vecCallables.end(); ++iterCallable)
		for( unsigned int i = 0; i < m_vecCallables.Count(); i++ )
		{
			//Try calling the callable, which should return an integer value determining whether this loop should continue or not. Failing to return a value
			//or causing an Exception will be interpreted as a CommandReturn.CONTINUE value.
			BEGIN_BOOST_PY()
				object returnValue = call<object>(m_vecCallables[i], pyCommand);
				if (!returnValue.is_none() && extract<int>(returnValue) == (int)BLOCK)
				{
					break;
				}
			END_BOOST_PY_NORET()	

			//Call the internal command at the right moment in the vector.
			if (m_pGameCommand && uiIndex == m_uiGameCommandIndex)
			{
				m_pGameCommand->Dispatch(command);
			}
			uiIndex++;
		}
	}
}

//---------------------------------------------------------------------------------
// ConCommandManager AddToStart function. Will add a Python callable right to the
// start of the vector, meaning it will be the first to be called (unless another
// callable gets added to the front afterwards).
//---------------------------------------------------------------------------------
void ConCommandManager::AddToStart(PyObject* pCallable)
{
	m_vecCallables.AddToHead(pCallable);
	m_uiGameCommandIndex++;
	if (m_uiGameCommandIndex == m_vecCallables.Count())
	{
		m_uiGameCommandIndex--;
	}
}

//---------------------------------------------------------------------------------
// ConCommandManager AddToEnd function. The opposite of AddToStart. Will be called
// last in the vector.
//---------------------------------------------------------------------------------
void ConCommandManager::AddToEnd(PyObject* pCallable)
{
	m_vecCallables.AddToTail(pCallable);
}

//---------------------------------------------------------------------------------
// ConCommandManager Remove function. Removes the callable from the vector.
//---------------------------------------------------------------------------------
void ConCommandManager::Remove(PyObject* pCallable)
{
	unsigned int uiCallableIndex = 0;
	for(uiCallableIndex = 0; uiCallableIndex < m_vecCallables.Count(); ++uiCallableIndex)
	{
		if (m_vecCallables[uiCallableIndex] == pCallable)
		{
			m_vecCallables.Remove(uiCallableIndex);
			break;
		}
	}

	if (uiCallableIndex <= m_uiGameCommandIndex)
	{
		m_uiGameCommandIndex--;
	}
	else
	{
		m_uiGameCommandIndex++;
	}
}

//---------------------------------------------------------------------------------
// Wraps ConCommand
//---------------------------------------------------------------------------------
void Export_ConCommand( void )
{
	// ----------------------------------------------------------
	// Expose the CommandReturn enum
	// ----------------------------------------------------------
	enum_<CommandReturn>("CommandReturn")
		.value("CONTINUE", CONTINUE)
		.value("BLOCK", BLOCK)
		;

	// ----------------------------------------------------------
	// Expose the ConCommand abstract class
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS_INHERITED(ConCommand, ConCommandBase)
		CLASS_METHOD(ConCommand,
			IsCommand,
			"Returns true if this is a command (should always return true)."
		)
		CLASS_METHOD(ConCommand,
			Dispatch,
			"Dispatches the command.",
			args("command")
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Expose the ConCommandManager class
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS_INHERITED(ConCommandManager, ConCommand)
		CLASS_METHOD(ConCommandManager,
			AddToStart,
			"Adds a callable to the start of the command queue.",
			args("pCallable")
		)
		CLASS_METHOD(ConCommandManager,
			AddToEnd,
			"Adds a callable to the end of the command queue.",
			args("pCallable")
		)
		CLASS_METHOD(ConCommandManager,
			Remove,
			"Removes a callable from the command queue.",
			args("pCallable")
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Expose the CCommand class
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(CCommand)
		CLASS_METHOD(CCommand,
			ArgC,
			"Returns the number of arguments passed to the command."
		)
		CLASS_METHOD(CCommand,
			ArgS,
			"Returns all of the arguments, after the 0th argument (the command name)."
		)
		CLASS_METHOD(CCommand,
			GetCommandString,
			"Returns the full command string, including the 0th argument (the command name)."
		)
		.def("__getitem__",
			&CCommand::operator[],
			"Returns the argument at the index given.",
			args("nIndex")
		)
		CLASS_METHOD(CCommand,
			FindArg,
			"Returns the argument given an argument's name.",
			args("pName")
		)
		CLASS_METHOD(CCommand,
			FindArgInt,
			"Returns the argument given an argument's name, as an integer.",
			args("pName", "nDefaultVal")
		)
	BOOST_END_CLASS()
	
	// ----------------------------------------------------------
	// Expose GetCommand function
	// ----------------------------------------------------------
	def("GetCommand",
		GetCommand,
		GetCommand_Overloads("Gets the command manager given the specific command name. Will create a command manager if one does not yet exist.",
			args("szName", "szHelp", "iFlags")
		)[reference_existing_object_policy()]
	);
}