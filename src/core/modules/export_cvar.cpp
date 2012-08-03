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
#include "utility/sp_util.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "icvar.h"
#include "convar.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// External variables to use.
//---------------------------------------------------------------------------------
extern ICvar* cvar;

//---------------------------------------------------------------------------------
// Accessor for the convar interface.
//---------------------------------------------------------------------------------
ICvar* GetCvar( void ) 
{
	return cvar;
}

//---------------------------------------------------------------------------------
// The cvar module.
//---------------------------------------------------------------------------------
DECLARE_SP_MODULE(Cvar)
{
	// ----------------------------------------------------------
	// Accessors for global variables.
	// ----------------------------------------------------------
	BOOST_FUNCTION(GetCvar, reference_existing_object_policy());

	// ----------------------------------------------------------
	// The ICvar interface.
	// ----------------------------------------------------------
	typedef ConVar*		(ICvar::*FindVarFn)(const char*);
	typedef ConCommand* (ICvar::*FindCommandFn)(const char*);

	FindVarFn		ICvar_FindVar = &ICvar::FindVar;
	FindCommandFn	ICvar_FindCommand = &ICvar::FindCommand;

	BOOST_ABSTRACT_CLASS( ICvar )

		CLASS_METHOD_TYPEDEF(
			FindVar,
			ICvar_FindVar,
			"Returns a ConVar instance based on the given name. Returns None if not found.",
			reference_existing_object_policy()
		)

		CLASS_METHOD_TYPEDEF(
			FindCommand,
			ICvar_FindCommand,
			"Returns a ConCommand instance based on the given name. Returns None if not found.",
			reference_existing_object_policy()
		)

	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Console variable/command base.
	// ----------------------------------------------------------
	BOOST_CLASS( ConCommandBase )
		BOOST_CLASS_CONSTRUCTOR(const char*, const char*, int)

		CLASS_METHOD(ConCommandBase,
			IsCommand,
			"Returns true if the ConCommandBase instance is a command."
		)

		CLASS_METHOD(ConCommandBase,
			IsFlagSet,
			"Returns true if the flag given is set on the ConCommandBase instance.",
			args("flag")
		)

		CLASS_METHOD(ConCommandBase,
			AddFlags,
			"Adds the given flags to the ConCommandBase instance.",
			args("flags")
		)

		CLASS_METHOD(ConCommandBase,
			RemoveFlags,
			"Removes the given flags from the ConCommandBase instance.",
			args("flags")
		)

		CLASS_METHOD(ConCommandBase,
			GetFlags,
			"Returns the flags set on this ConCommandBase."
		)

		CLASS_METHOD(ConCommandBase,
			GetName,
			"Returns the name of this ConCommandBase instance."
		)

	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Consolve variable.
	// ----------------------------------------------------------
	typedef void (ConVar::*SetValueIntFn)(int);
	typedef void (ConVar::*SetValueFloatFn)(float);
	typedef void (ConVar::*SetValueStrFn)(const char*);
	typedef void (ConVar::*SetValueColorFn)(Color);

	SetValueIntFn	ConVar_SetValue_Int		= &ConVar::SetValue;
	SetValueFloatFn ConVar_SetValue_Float	= &ConVar::SetValue;
	SetValueStrFn	ConVar_SetValue_Str		= &ConVar::SetValue;
	SetValueColorFn ConVar_SetValue_Color	= &ConVar::SetValue;

	BOOST_INHERITED_CLASS_NOCOPY( ConVar, ConCommandBase, init<const char*, const char*, int>() )
		CLASS_CONSTRUCTOR( const char*, const char*, int, const char* )
		CLASS_CONSTRUCTOR( const char*, const char*, int, const char*, bool, float, bool, float )

		CLASS_METHOD(ConVar,
			IsFlagSet,
			"Returns true if the flag given is set on the ConCommandBase instance.",
			args("flag")
		)

		CLASS_METHOD(ConVar,
			GetHelpText,
			"Returns the help text for this convar."
		)

		CLASS_METHOD(ConVar,
			GetName,
			"Returns the name of this convar."
		)

		CLASS_METHOD(ConVar,
			AddFlags,
			"Adds the given flags to the ConVar instance.",
			args("flags")
		)

		CLASS_METHOD(ConVar,
			GetFlags,
			"Returns the flags set on this ConVar."
		)

		CLASS_METHOD(ConVar,
			GetFloat,
			"Returns the value of this console variable as a float."
		)

		CLASS_METHOD(ConVar,
			GetInt,
			"Returns the value of this console variable as a int."
		)

		CLASS_METHOD(ConVar,
			GetColor,
			"Returns the value of this console variable as a color."
		)

		CLASS_METHOD(ConVar,
			GetBool,
			"Returns the value of this console variable as a bool."
		)

		CLASS_METHOD(ConVar,
			GetString,
			"Returns the value of this console variable as a string."
		)

		CLASS_METHOD_TYPEDEF(
			SetInt,
			ConVar_SetValue_Int,
			"Sets the value of the console variable as a int."
		)

		CLASS_METHOD_TYPEDEF(
			SetFloat,
			ConVar_SetValue_Float,
			"Sets the value of the console variable as a float."
		)

		CLASS_METHOD_TYPEDEF(
			SetString,
			ConVar_SetValue_Str,
			"Sets the value of the console variable as a string."
		)

		CLASS_METHOD_TYPEDEF(
			SetColor,
			ConVar_SetValue_Color,
			"Sets the value of the console variable as a color."
		)

#if defined(CVAR_TODO)
		CLASS_METHOD(ConVar,
			HasMin,
			"Returns true if the ConVar has a minimum limit."
		)

		CLASS_METHOD(ConVar,
			HasMax,
			"Returns true if the ConVar has a maximum limit."
		)

		CLASS_METHOD(ConVar,
			GetMinValue,
			"Returns the minimum value of the ConVar as a float."
		)

		CLASS_METHOD(ConVar,
			GetMaxValue,
			"Returns the maximum value of the ConVar as a float."
		)
#endif

	BOOST_END_CLASS()
}