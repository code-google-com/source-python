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

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "../export_main.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "binutils_scanner.h"
#include "tier1/interface.h"
#include "tier0/dbg.h"

#if defined(_WIN32)
#	include <windows.h>
#endif

//---------------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------------
#define MAX_MODULE_PATH 1024

//---------------------------------------------------------------------------------
// Returns module data.
//---------------------------------------------------------------------------------
moduledata_t* find_moduledata(const char* szBinary)
{
	char szModulePath[MAX_MODULE_PATH];

#if defined(_WIN32)
	sprintf_s(szModulePath, MAX_MODULE_PATH, "%s.dll", szBinary);
#endif

	// Load the library.
	CreateInterfaceFn fnCreateIface = Sys_GetFactory(szBinary);
	void* baseAddress = reinterpret_cast<void*>(fnCreateIface);

	if( !baseAddress )
	{
		Msg("[SP] Could not get interface factory for %s!\n", szBinary);
		return NULL;
	}

#if defined(_WIN32)
	// Get memory information about the module.
	MEMORY_BASIC_INFORMATION memInfo;
	if(!VirtualQuery(baseAddress, &memInfo, sizeof(MEMORY_BASIC_INFORMATION)))
	{
		Msg("[SP] VirtualQuery failed on %s!\n", szModulePath);
		return NULL;
	}

	// Get at the image size too.
	IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)memInfo.AllocationBase;
	IMAGE_NT_HEADERS* ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(dosHeader + dosHeader->e_lfanew);

	// Create the memory data struct.
	moduledata_t* pData = new moduledata_t;
	pData->baseAddress = (unsigned long)memInfo.AllocationBase;
	pData->size = ntHeader->OptionalHeader.SizeOfImage;
#endif

	return pData;
}

//---------------------------------------------------------------------------------
// Returns the address of a signature.
//---------------------------------------------------------------------------------
unsigned long find_signature( moduledata_t* pData, object signature, int length )
{
	if( !pData ) 
	{
		Msg("[SP] find_signature got invalid pData!\n");
		return NULL;
	}

	// This is required because there's no straight way to get a string from a python
	// object from boost (without using the stl).
	unsigned char* sig = NULL;
	PyArg_Parse(signature.ptr(), "y", &sig);

	// Ugly casts but these can't be helped.
	unsigned char*	base	= (unsigned char*)(pData->baseAddress);
	unsigned char*	end		= (unsigned char*)(base + pData->size);
	int				i		= 0;

	unsigned char* mystring = (unsigned char*)"\x55\x8B\xEC\x8B";
	for( int k = 0; k < 4; k++ )
	{
		printf("mystring[%d]: %d\n", k, mystring[k]);
	}

	for( int k = 0; k < length; k++ )
	{
		printf("sig[%d]: %d\n", k, sig[k]);
	}

	// Scan the entire module.
	while( base < end )
	{
		// Scan in chunks of length.
		for( i = 0; i < length; i++ )
		{
			// If the current signature character is x2A, ignore it.
			if( sig[i] == '\x2A' ) 
			{
				Msg("ignoring character at %d\n", i);
				continue;
			}

			// Break out if we have a mismatch.
			if( sig[i] != base[i] )
				break;
		}

		// Did we find the signature?
		if( i == length ) 
			return reinterpret_cast<unsigned long>(base);

		// Increment the base pointer.
		base++;
	}

	// Didn't find the signature :(
	return NULL;
}