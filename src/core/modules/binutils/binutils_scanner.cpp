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
*
* This code inspired by:
* https://code.google.com/p/gmodmodules/source/browse/trunk/serversecure3/serversecure3/sigscan.cpp
*/

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#if defined(_WIN32)
#	   include <windows.h>
#else
#   include <fcntl.h>
#   include <link.h>
#   include <sys/mman.h>
#endif
#include "../export_main.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "binutils_scanner.h"
#include "tier1/interface.h"
#include "tier0/dbg.h"

//---------------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------------
#define MAX_MODULE_PATH 1024

//---------------------------------------------------------------------------------
// Returns module data.
//---------------------------------------------------------------------------------
moduledata_t* FindModuleData(const char* szBinary)
{
	char szModulePath[MAX_MODULE_PATH];

#if defined(_WIN32)
	sprintf_s(szModulePath, MAX_MODULE_PATH, "%s.dll", szBinary);
	void* baseAddress = (void *)LoadLibrary(szModulePath);
#else
	sprintf(szModulePath, "%s.so", szBinary);
	void* baseAddress = (void *)dlopen(szModulePath, RTLD_NOW | RTLD_GLOBAL);
#endif
	DevMsg(1, "Loading module %s\n", szModulePath);

	// Don't continue if we couldn't load the module.
	if( !baseAddress )
 	{
		Msg("Could not load module %s!\n", szModulePath);
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
	IMAGE_NT_HEADERS* ntHeader = (IMAGE_NT_HEADERS*)((unsigned long)dosHeader + (unsigned long)dosHeader->e_lfanew);

	// Create the memory data struct.
	moduledata_t* pData = new moduledata_t;
	pData->handle	   = memInfo.AllocationBase;
	pData->size		 = ntHeader->OptionalHeader.SizeOfImage;
#else
	// Construct the required memory information.
	moduledata_t* pData			 = new moduledata_t;
	pData->handle				   = baseAddress;
	pData->size					 = 0;
#endif
	return pData;
}

//---------------------------------------------------------------------------------
// Returns the address of a signature.
//---------------------------------------------------------------------------------
unsigned long FindSignature( moduledata_t* pData, object signature, int length )
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
	unsigned char*  base	= (unsigned char*)(pData->handle);
	unsigned char*  end		= (unsigned char*)(base + pData->size);
	int				i		= 0;

	// Scan the entire module.
	while( base < end )
	{
		// Scan in chunks of length.
		for( i = 0; i < length; i++ )
		{
			// If the current signature character is x2A, ignore it.
			if( sig[i] == '\x2A' )
				continue;

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


//---------------------------------------------------------------------------------
// Finds a symbol in a given module.
//---------------------------------------------------------------------------------
unsigned long FindSymbol( moduledata_t* pData, char* symbol )
{
	if( !pData )
	{
		Msg("[SP] find_symbol got invalid pData for %s!\n", symbol);
		return NULL;
	}

#if defined(__linux__)
	if( !pData->handle )
	{
		Msg("[SP] find_symbol got invalid library handle for %s!\n", symbol);
		return NULL;
	}

	// -----------------------------------------
	// We need to use mmap now that VALVe has
	// made them all private!
	// Thank you to DamagedSoul from AlliedMods
	// for the following code.
	// It can be found at:
	// http://hg.alliedmods.net/sourcemod-central/file/dc361050274d/core/logic/MemoryUtils.cpp
	// -----------------------------------------
	struct link_map *dlmap;
	struct stat dlstat;
	int dlfile;
	uintptr_t map_base;
	Elf32_Ehdr *file_hdr;
	Elf32_Shdr *sections, *shstrtab_hdr, *symtab_hdr, *strtab_hdr;
	Elf32_Sym *symtab;
	const char *shstrtab, *strtab;
	uint16_t section_count;
	uint32_t symbol_count;

	dlmap = (struct link_map *)pData->handle;
	symtab_hdr = NULL;
	strtab_hdr = NULL;

	dlfile = open(dlmap->l_name, O_RDONLY);
	if (dlfile == -1 || fstat(dlfile, &dlstat) == -1)
	{
		Msg("dlfile == -1!\n");
		close(dlfile);
		return NULL;
	}

	/* Map library file into memory */
	file_hdr = (Elf32_Ehdr *)mmap(NULL, dlstat.st_size, PROT_READ, MAP_PRIVATE, dlfile, 0);
	map_base = (uintptr_t)file_hdr;
	if (file_hdr == MAP_FAILED)
	{
		Msg("file_hdr == MAP_FAILED!\n");
		close(dlfile);
		return NULL;
	}
	close(dlfile);

	if (file_hdr->e_shoff == 0 || file_hdr->e_shstrndx == SHN_UNDEF)
	{
		Msg("file_hdr->e_shoff == 0!\n");
		munmap(file_hdr, dlstat.st_size);
		return NULL;
	}

	sections = (Elf32_Shdr *)(map_base + file_hdr->e_shoff);
	section_count = file_hdr->e_shnum;
	/* Get ELF section header string table */
	shstrtab_hdr = &sections[file_hdr->e_shstrndx];
	shstrtab = (const char *)(map_base + shstrtab_hdr->sh_offset);

	/* Iterate sections while looking for ELF symbol table and string table */
	for (uint16_t i = 0; i < section_count; i++)
	{
		Elf32_Shdr &hdr = sections[i];
		const char *section_name = shstrtab + hdr.sh_name;

		if (strcmp(section_name, ".symtab") == 0)
		{
			symtab_hdr = &hdr;
		}
		else if (strcmp(section_name, ".strtab") == 0)
		{
			strtab_hdr = &hdr;
		}
	}

	/* Uh oh, we don't have a symbol table or a string table */
	if (symtab_hdr == NULL || strtab_hdr == NULL)
	{
		Msg("File doesn't have a symbol table!\n");
		munmap(file_hdr, dlstat.st_size);
		return NULL;
	}

	symtab = (Elf32_Sym *)(map_base + symtab_hdr->sh_offset);
	strtab = (const char *)(map_base + strtab_hdr->sh_offset);
	symbol_count = symtab_hdr->sh_size / symtab_hdr->sh_entsize;
	void* sym_addr = NULL;

	/* Iterate symbol table starting from the position we were at last time */
	for (uint32_t i = 0; i < symbol_count; i++)
	{
		Elf32_Sym &sym = symtab[i];
		unsigned char sym_type = ELF32_ST_TYPE(sym.st_info);
		const char *sym_name = strtab + sym.st_name;

		/* Skip symbols that are undefined or do not refer to functions or objects */
		if (sym.st_shndx == SHN_UNDEF || (sym_type != STT_FUNC && sym_type != STT_OBJECT))
		{
			continue;
		}

		if (strcmp(symbol, sym_name) == 0)
		{
			sym_addr = (void *)(dlmap->l_addr + sym.st_value);
			break;
		}
	}

	// Unmap the file now.
	munmap(file_hdr, dlstat.st_size);

	// Validate it
	if( !sym_addr )
	{
		DevMsg("[SP]: Could not find symbol %s!\n", symbol);
		return NULL;
	}

	// Print it out
	DevMsg(1, "************************************\n");
	DevMsg(1, "[SP]: Symbol: %s.\n", symbol);
	DevMsg(1, "[SP]: Symbol address: %d.\n", sym_addr);
	DevMsg(1, "************************************\n");

	// Return it
	return (unsigned long)(sym_addr);
#endif
	// Not implemented for windows yet.
	return NULL;
}
