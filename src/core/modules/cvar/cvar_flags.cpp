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
// Exports CVAR flags (executed from this file, not cvar_main).
//---------------------------------------------------------------------------------
void Export_CvarFlags( void )
{
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_NONE", FCVAR_NONE);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_UNREGISTERED", FCVAR_UNREGISTERED);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_DEVELOPMENTONLY", FCVAR_DEVELOPMENTONLY);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_GAMEDLL", FCVAR_GAMEDLL);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_CLIENTDLL", FCVAR_CLIENTDLL);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_HIDDEN", FCVAR_HIDDEN);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_PROTECTED", FCVAR_PROTECTED);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_SPONLY", FCVAR_SPONLY);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_ARCHIVE", FCVAR_ARCHIVE);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_NOTIFY", FCVAR_NOTIFY);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_USERINFO", FCVAR_USERINFO);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_PRINTABLEONLY", FCVAR_PRINTABLEONLY);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_UNLOGGED", FCVAR_UNLOGGED);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_NEVER_AS_STRING", FCVAR_NEVER_AS_STRING);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_REPLICATED", FCVAR_REPLICATED);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_CHEAT", FCVAR_CHEAT);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_SS", FCVAR_SS);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_DEMO", FCVAR_DEMO);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_DONTRECORD", FCVAR_DONTRECORD);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_SS_ADDED", FCVAR_SS_ADDED);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_RELEASE", FCVAR_RELEASE);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_RELOAD_MATERIALS", FCVAR_RELOAD_MATERIALS);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_RELOAD_TEXTURES", FCVAR_RELOAD_TEXTURES);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_NOT_CONNECTED", FCVAR_NOT_CONNECTED);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_MATERIAL_SYSTEM_THREAD", FCVAR_MATERIAL_SYSTEM_THREAD);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_ARCHIVE_XBOX", FCVAR_ARCHIVE_XBOX);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_SERVER_CAN_EXECUTE", FCVAR_SERVER_CAN_EXECUTE);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_SERVER_CANNOT_QUERY", FCVAR_SERVER_CANNOT_QUERY);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_CLIENTCMD_CAN_EXECUTE", FCVAR_CLIENTCMD_CAN_EXECUTE);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_ACCESSIBLE_FROM_THREADS", FCVAR_ACCESSIBLE_FROM_THREADS);
	BOOST_GLOBAL_ATTRIBUTE("FCVAR_MATERIAL_THREAD_MASK", FCVAR_MATERIAL_THREAD_MASK);
}