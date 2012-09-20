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
* People I'd like to thank for insipiring this code:
*   Lance Vorgin - Godfather of sigscanning.
*   AlliedMods - For writing great sigscanning code.
*   LDuke - For teaching me and countless others how to sigscan.
*   Preadcrab - For explaining how sigscanning works.
*/
#ifndef _BINUTILS_SCANNER_H
#define _BINUTILS_SCANNER_H

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "../export_main.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"

//---------------------------------------------------------------------------------
// In order to perform signature scanning, we need to have the base address and
// image size of the binary in memory. This structure will hold that information.
//---------------------------------------------------------------------------------
struct moduledata_t
{
	unsigned long baseAddress;
	unsigned long size;

	// Lame hack but linux requires this for find_symbol.
#if defined(__linux__)
	void* handle;

	~moduledata_t( void )
	{
		if( handle ) {
			dlclose(handle);
		}
	}
#endif
};

//---------------------------------------------------------------------------------
// This function returns the required information about a module to make it ready
// for signature scanning. NOTE: If the module name that you give this IS NOT a
// binary in the srcds/bin folder, you are REQUIRED to give a FULL PATH. You don't
// have to use an extension, the function will place the correct one on.
//---------------------------------------------------------------------------------
moduledata_t* find_moduledata(const char* szBinary);

//---------------------------------------------------------------------------------
// Finds a signature in a given module.
//---------------------------------------------------------------------------------
unsigned long find_signature( moduledata_t* pData, object signature, int length );

//---------------------------------------------------------------------------------
// Finds a symbol in a given module.
//---------------------------------------------------------------------------------
unsigned long find_symbol( moduledata_t* pData, char* symbol );

#endif 