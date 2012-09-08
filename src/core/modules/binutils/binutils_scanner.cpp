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
	HMODULE hModule = LoadLibrary(szModulePath);

	if( !hModule ) 
	{
		Msg("[SP] Could not load %s!\n", szModulePath);
		return NULL;
	}

	// Get memory information about the module.
	MEMORY_BASIC_INFORMATION memInfo;
	if(!VirtualQuery(hModule, &memInfo, sizeof(MEMORY_BASIC_INFORMATION)))
	{
		Msg("[SP] VirtualQuery failed on %s!\n", szModulePath);
		return NULL;
	}

	// Get at the image size too.
	IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)memInfo.AllocationBase;
	IMAGE_NT_HEADERS* ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(dosHeader + dosHeader->e_lfanew);

	// Make sure we have a valid pe file.
	if( ntHeader->Signature != IMAGE_NT_SIGNATURE )
	{
		Msg("[SP] %s is not a valid pe file!\n", szModulePath);
		return NULL;
	}

	// Create the memory data struct.
	moduledata_t* pData = new moduledata_t;
	pData->baseAddress = memInfo.AllocationBase;
	pData->size = ntHeader->OptionalHeader.SizeOfImage;
#endif

	return pData;
}

//---------------------------------------------------------------------------------
// Returns the address of a signature.
//---------------------------------------------------------------------------------
unsigned long find_signature( moduledata_t* pData, const char* szSignature, int length )
{
	if( !pData ) 
	{
		Msg("[SP] Invalid module data passed for %s!\n", szSignature);
		return NULL;
	}

	unsigned char*	start	= reinterpret_cast<unsigned char*>(pData->baseAddress);
	unsigned char*	end		= reinterpret_cast<unsigned char*>(start + pData->size);

	// Scan the entire module.
	while( start < end )
	{
		// Scan in chunks of length.
		for( int i = 0; i < length; i++ )
		{
			// If the current signature character is x2A, ignore it.
			if( szSignature[i] == '\x2A' )
				continue;

			// Break out if we have a mismatch.
			if( szSignature[i] != start[i] )
			{
				// Increment start. Note, we already checked the current
				// character, hence the +1 to get the next one.
				start += (i + 1);
				break;
			}

			// Did we find the signature?
			if( i == length ) 
				return reinterpret_cast<unsigned long>(start);
		}
	}

	// Didn't find the signature :(
	return NULL;
}