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
*
*/

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "../export_main.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "dyncall.h"
#include "dyncall_callvm.h"
#include "dbg.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------------------
DCCallVM* g_pCallVM = NULL;

//---------------------------------------------------------------------------------
// Returns the dyncall vm.
//---------------------------------------------------------------------------------
DCCallVM* dcGetVM( void )
{
	return g_pCallVM;
}

//---------------------------------------------------------------------------------
// Wrapper to allow strings
//---------------------------------------------------------------------------------
void dcArgString( DCCallVM* vm, char* str )
{
 dcArgPointer( vm, (DCpointer)str );
}

//---------------------------------------------------------------------------------
// Exports dyncall to python.
//---------------------------------------------------------------------------------
void Export_DynCall( void )
{
	// Dyncall virtual machine class.
	BOOST_CLASS(DCCallVM)
	BOOST_END_CLASS()

	// Calling conventions.
	BOOST_GLOBAL_ATTRIBUTE("DC_CALL_C_DEFAULT",				DC_CALL_C_DEFAULT);
	BOOST_GLOBAL_ATTRIBUTE("DC_CALL_C_ELLIPSIS",			DC_CALL_C_ELLIPSIS);
	BOOST_GLOBAL_ATTRIBUTE("DC_CALL_C_ELLIPSIS_VARARGS",	DC_CALL_C_ELLIPSIS_VARARGS);
	BOOST_GLOBAL_ATTRIBUTE("DC_CALL_C_X86_WIN32_STD",		DC_CALL_C_X86_WIN32_STD);
	BOOST_GLOBAL_ATTRIBUTE("DC_CALL_C_X86_WIN32_FAST_MS",	DC_CALL_C_X86_WIN32_FAST_MS);
	BOOST_GLOBAL_ATTRIBUTE("DC_CALL_C_X86_WIN32_FAST_GNU",	DC_CALL_C_X86_WIN32_FAST_GNU);
	BOOST_GLOBAL_ATTRIBUTE("DC_CALL_C_X86_WIN32_THIS_MS",	DC_CALL_C_X86_WIN32_THIS_MS);
	BOOST_GLOBAL_ATTRIBUTE("DC_CALL_C_X86_WIN32_THIS_GNU",	DC_CALL_C_X86_WIN32_THIS_GNU);

	// Other constants that are very useful.
	BOOST_GLOBAL_ATTRIBUTE("DC_ERROR_NONE",					DC_ERROR_NONE);
	BOOST_GLOBAL_ATTRIBUTE("DC_ERROR_UNSUPPORTED_MODE",		DC_ERROR_UNSUPPORTED_MODE);
	BOOST_GLOBAL_ATTRIBUTE("DEFAULT_ALIGNMENT",				DEFAULT_ALIGNMENT);

	// Dyncall functions.
	BOOST_FUNCTION(dcGetVM,
		"Returns the static dyncall virtual machine instance.",
		reference_existing_object_policy()
	);

	BOOST_FUNCTION(dcReset,
		"Resets the state of the dyncall virtual machine.",
		args("vm")
	);

	BOOST_FUNCTION(dcMode,
		"Sets the calling convention of the dyncall virtual machine.",
		args("vm", "convention")
	);

	BOOST_FUNCTION(dcGetError,
		"Returns the last error that occured in the virtual machine"
	);

	// Dyncall virtual machine functions for arguments.
	BOOST_FUNCTION(dcArgBool);
	BOOST_FUNCTION(dcArgChar);
	BOOST_FUNCTION(dcArgShort);
	BOOST_FUNCTION(dcArgInt);
	BOOST_FUNCTION(dcArgLong);
	BOOST_FUNCTION(dcArgLongLong);
	BOOST_FUNCTION(dcArgFloat);
	BOOST_FUNCTION(dcArgDouble);
	//BOOST_FUNCTION(dcArgStruct);
	BOOST_FUNCTION(dcArgPointer);
	BOOST_FUNCTION(dcArgString);

	// Dyncall virtual machine functions for calling functions.
	BOOST_FUNCTION(dcCallVoid);
	BOOST_FUNCTION(dcCallBool);
	BOOST_FUNCTION(dcCallChar);
	BOOST_FUNCTION(dcCallShort);
	BOOST_FUNCTION(dcCallInt);
	BOOST_FUNCTION(dcCallLong);
	BOOST_FUNCTION(dcCallLongLong);
	BOOST_FUNCTION(dcCallFloat);
	BOOST_FUNCTION(dcCallDouble);
	//BOOST_FUNCTION(dcCallStruct);
	BOOST_FUNCTION(dcCallPointer);
}
