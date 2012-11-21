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
#include "utility/sp_util.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "icvar.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// Wraps the ConVar class.
//---------------------------------------------------------------------------------
void Export_ConVar( void )
{
	// ----------------------------------------------------------
	// Consolve variable.
	// ----------------------------------------------------------
	typedef void (ConVar::*SetValueIntFn)(int);
	typedef void (ConVar::*SetValueFloatFn)(float);
	typedef void (ConVar::*SetValueStrFn)(const char*);

	SetValueIntFn	ConVar_SetValue_Int		= &ConVar::SetValue;
	SetValueFloatFn ConVar_SetValue_Float	= &ConVar::SetValue;
	SetValueStrFn	ConVar_SetValue_Str		= &ConVar::SetValue;

#if( SOURCE_ENGINE >= 2 )
	typedef void (ConVar::*SetValueColorFn)(Color);
	SetValueColorFn ConVar_SetValue_Color	= &ConVar::SetValue;
#endif
	

	BOOST_INHERITED_CLASS_NOCOPY( ConVar, ConCommandBase, init<const char*, const char*, int>() )
		// ----------------------------------------------------------
		// Constructors
		// ----------------------------------------------------------
		CLASS_CONSTRUCTOR( const char*, const char*, int, const char* )
		CLASS_CONSTRUCTOR( const char*, const char*, int, const char*, bool, float, bool, float )

		// ----------------------------------------------------------
		// Methods
		// ----------------------------------------------------------
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
			GetFloat,
			"Returns the value of this console variable as a float."
		)

		CLASS_METHOD(ConVar,
			GetInt,
			"Returns the value of this console variable as a int."
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

#if( SOURCE_ENGINE >= 2 )
		CLASS_METHOD(ConVar,
			GetColor,
			"Returns the value of this console variable as a color."
		)

		CLASS_METHOD(ConVar,
			GetFlags,
			"Returns the flags set on this ConVar."
		)

		CLASS_METHOD_TYPEDEF(
			SetColor,
			ConVar_SetValue_Color,
			"Sets the value of the console variable as a color."
		)
#endif

	BOOST_END_CLASS()
}