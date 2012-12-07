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
// Includes.
//---------------------------------------------------------------------------------
#include "../export_main.h"
#include "core/sp_python.h"
#include "utility/sp_util.h"
#include "utility/wrap_macros.h"
#include "eiface.h"
#include "networkstringtabledefs.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern INetworkStringTableContainer* networkstringtable;

//---------------------------------------------------------------------------------
// Returns the global INetworkStringTableContainer instance.
//---------------------------------------------------------------------------------
INetworkStringTableContainer* GetStringTables( void )
{
	return networkstringtable;
}

//---------------------------------------------------------------------------------
// Add a string to the specified table.
//---------------------------------------------------------------------------------
bool INetworkStringTable_AddString( INetworkStringTable* pTable, const char* string )
{
	if (pTable->GetNumStrings() >= pTable->GetMaxStrings())
		return false;
	bool bLocked = engine->LockNetworkStringTables(false);
	pTable->AddString(false, string, strlen(string)+1);
	engine->LockNetworkStringTables(bLocked);
	return true;
}

//---------------------------------------------------------------------------------
// Wrappers...
//---------------------------------------------------------------------------------
void Export_StringTables( void )
{
	BOOST_GLOBAL_ATTRIBUTE("INVALID_STRING_INDEX", INVALID_STRING_INDEX);
	
	// ----------------------------------------------------------
	// INetworkStringTableContainer
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(INetworkStringTableContainer)

		CLASS_METHOD(INetworkStringTableContainer,
			FindTable,
			"Returns the INetworkStringTable instance of the given table name.",
			args("tableName"),
			reference_existing_object_policy()
		)

		CLASS_METHOD(INetworkStringTableContainer,
			GetTable,
			"Returns the INetworkStringTable instance of the given table ID.",
			args("stringTable"),
			reference_existing_object_policy()
		)

		CLASS_METHOD(INetworkStringTableContainer,
			GetNumTables,
			"Returns the length of the container."
		)

	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// INetworkStringTable
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(INetworkStringTable)

		CLASS_METHOD(INetworkStringTable,
			GetTableName,
			"Returns the name of the table."
		)

		CLASS_METHOD(INetworkStringTable,
			GetNumStrings,
			"Returns the length of the table."
		)

		CLASS_METHOD(INetworkStringTable,
			GetMaxStrings,
			"Returns the maximum length of the table."
		)

		CLASS_METHOD_TYPEDEF(AddString,
			INetworkStringTable_AddString,
			"Add the specified string to the table.",
			args("value")
		)

		CLASS_METHOD(INetworkStringTable,
			GetString,
			"Returns the string at the given index.",
			args("stringNumber")
		)

		CLASS_METHOD(INetworkStringTable,
			FindStringIndex,
			"Returns the index of the given string.",
			args("string")
		)

	BOOST_END_CLASS()

	BOOST_FUNCTION(GetStringTables, reference_existing_object_policy());
}