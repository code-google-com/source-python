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
#include "utility/wrap_macros.h"
#include "networkstringtabledefs.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern INetworkStringTableContainer *networkstringtable;

//---------------------------------------------------------------------------------
// Returns the global INetworkStringTableContainer instance.
//---------------------------------------------------------------------------------
INetworkStringTableContainer *GetStringTables( void )
{
	return networkstringtable;
}

//---------------------------------------------------------------------------------
// Add a string to the specified table.
//---------------------------------------------------------------------------------
int INetworkStringTable_AddString( INetworkStringTable *pTable, bool bIsServer, const char *value, int length = -1, const char *userdata = NULL )
{
	return pTable->AddString(bIsServer, value, length, &userdata);
}

//---------------------------------------------------------------------------------
// Sets the userdata of the given string index.
//---------------------------------------------------------------------------------
void INetworkStringTable_SetStringUserData( INetworkStringTable *pTable, int stringNumber, int length, const char *userdata )
{
	pTable->SetStringUserData(stringNumber, length, userdata);
}

//---------------------------------------------------------------------------------
// Returns the userdata of the given string index.
//---------------------------------------------------------------------------------
const char *INetworkStringTable_GetStringUserData( INetworkStringTable *pTable, int stringNumber, int length )
{
	return (const char *)pTable->GetStringUserData(stringNumber, &length);
}

//---------------------------------------------------------------------------------
// Overloads.
//---------------------------------------------------------------------------------
BOOST_PYTHON_FUNCTION_OVERLOADS(INetworkStringTable_AddString_Overloads, INetworkStringTable_AddString, 3, 5);
	
#if ( SOURCE_ENGINE >= 3 )
	DECLARE_CLASS_METHOD_OVERLOAD(INetworkStringTableContainer, CreateStringTable, 2, 5);
#else
	DECLARE_CLASS_METHOD_OVERLOAD(INetworkStringTableContainer, CreateStringTable, 2, 4);
	DECLARE_CLASS_METHOD_OVERLOAD(INetworkStringTableContainer, CreateStringTableEx, 2, 5);
#endif

//---------------------------------------------------------------------------------
// Wrappers...
//---------------------------------------------------------------------------------
void Export_StringTables( void )
{
	//-----------------------------------------------------------
	// Global attributes.
	//-----------------------------------------------------------
	BOOST_GLOBAL_ATTRIBUTE("INVALID_STRING_TABLE", INVALID_STRING_TABLE);
	BOOST_GLOBAL_ATTRIBUTE("INVALID_STRING_INDEX", INVALID_STRING_INDEX);

	//-----------------------------------------------------------
	// ENetworkStringtableFlags.
	//-----------------------------------------------------------
#if (SOURCE_ENGINE >= 3)
	enum_<ENetworkStringtableFlags>("ENetworkStringtableFlags")
		.value("NSF_NONE", NSF_NONE)
		.value("NSF_DICTIONARY_ENABLED", NSF_DICTIONARY_ENABLED)
		.export_values()
		;
#endif

	//-----------------------------------------------------------
	// INetworkStringTableContainer.
	//-----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(INetworkStringTableContainer)

		CLASS_METHOD_OVERLOAD_RET(INetworkStringTableContainer,
			CreateStringTable,
			"Creates a string table.",
			args("tableName", "maxentries", "userdatafixedsize", "userdatanetworkbits", "flags"),
			reference_existing_object_policy()
		)

		CLASS_METHOD(INetworkStringTableContainer,
			RemoveAllTables,
			"Removes all string tables."
		)

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

#if ( SOURCE_ENGINE <= 2 )
		CLASS_METHOD_OVERLOAD_RET(INetworkStringTableContainer,
			CreateStringTableEx,
			"Creates a string table.",
			args("tableName", "maxentries", "userdatafixedsize", "userdatanetworkbits", "bIsFilenames"),
			reference_existing_object_policy()
		)
#endif

		CLASS_METHOD(INetworkStringTableContainer,
			SetAllowClientSideAddString,
			"Allows clients to add strings to the given table.",
			args("table", "bAllowClientSideAddString")
		)

# if ( SOURCE_ENGINE >= 3 )
		CLASS_METHOD(INetworkStringTableContainer,
			CreateDictionary,
			"Creates a dictionnary based on the given map bsp file?",
			args("pchMapName")
		)
#endif

	BOOST_END_CLASS()

	//-----------------------------------------------------------
	// INetworkStringTable.
	//-----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(INetworkStringTable)

		CLASS_METHOD(INetworkStringTable,
			GetTableName,
			"Returns the name of the table."
		)

		CLASS_METHOD(INetworkStringTable,
			GetTableId,
			"Returns the index of the table."
		)
		
		CLASS_METHOD(INetworkStringTable,
			GetNumStrings,
			"Returns the length of the table."
		)

		CLASS_METHOD(INetworkStringTable,
			GetMaxStrings,
			"Returns the maximum length of the table."
		)

		CLASS_METHOD(INetworkStringTable,
			GetEntryBits,
			"Returns the maximum entries of the table."
		)

		CLASS_METHOD(INetworkStringTable,
			SetTick,
			"Set the tick on which the table has been last modified.",
			args("tick")
		)

		CLASS_METHOD(INetworkStringTable,
			ChangedSinceTick,
			"Returns True if the table has been modified since the given tick, False otherwise.",
			args("tick")
		)

		.def("AddString",
			INetworkStringTable_AddString,
			INetworkStringTable_AddString_Overloads(
				"Adds a string to the table.",
				args("bIsServer", "value", "length", "userdata")
			)
		)

		CLASS_METHOD(INetworkStringTable,
			GetString,
			"Returns the string at the given index.",
			args("stringNumber")
		)

		CLASS_METHOD_TYPEDEF(SetStringUserData,
			INetworkStringTable_SetStringUserData,
			"Sets the userdata of the given string index.",
			args("stringNumber", "length", "userdata")
		)

		CLASS_METHOD_TYPEDEF(GetStringUserData,
			INetworkStringTable_GetStringUserData,
			"Returns the userdata of the given string index.",
			args("stringNumber", "length")
		)

		CLASS_METHOD(INetworkStringTable,
			FindStringIndex,
			"Returns the index of the given string.",
			args("string")
		)

	BOOST_END_CLASS()
	
	//-----------------------------------------------------------
	// Global INetworkStringTableContainer accessor.
	//-----------------------------------------------------------
	BOOST_FUNCTION(GetStringTables, reference_existing_object_policy());
}
