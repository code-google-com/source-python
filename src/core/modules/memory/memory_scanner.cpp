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

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <link.h>
    #include <sys/mman.h>
#endif

#include "dynload.h"
#include "memory_scanner.h"
#include "memory_tools.h"


//---------------------------------------------------------------------------------
// Constants
//---------------------------------------------------------------------------------
#define MAX_BINARY_PATH 1024
#ifdef _WIN32
    #define FILE_EXTENSION ".dll"
#elif defined(__linux__)
    #define FILE_EXTENSION ".so"
#else
    #error "Implement me!"
#endif


//-----------------------------------------------------------------------------
// BinaryFile class
//-----------------------------------------------------------------------------
CBinaryFile::CBinaryFile(unsigned long ulAddr, unsigned long ulSize)
{
    m_ulAddr = ulAddr;
    m_ulSize  = ulSize;
}

CPointer* CBinaryFile::find_signature(object szSignature, int iLength)
{
    // This is required because there's no straight way to get a string from a python
    // object from boost (without using the stl).
    unsigned char* sigstr = NULL;
    PyArg_Parse(szSignature.ptr(), "y", &sigstr);
    if (!sigstr)
        return NULL;

    // Search for a cached signature
    for (std::list<Signature_t>::iterator iter=m_Signatures.begin(); iter != m_Signatures.end(); iter++)
    {
        Signature_t sig = *iter;
        if (strcmp((const char *) sig.m_szSignature, (const char *) sigstr) == 0)
            return sig.m_pAddr;
    }

    unsigned char* base = (unsigned char *) m_ulAddr;
    unsigned char* end  = (unsigned char *) (base + m_ulSize - iLength);

    while(base < end)
    {
        int i = 0;
        for(; i < iLength; i++)
        {
            if (sigstr[i] == '\x2A')
                continue;

            if (sigstr[i] != base[i])
                break;
        }

        if (i == iLength)
        {
            // Add our signature to the cache
            CPointer* pAddr = new CPointer((unsigned long) base);
            Signature_t sig_t = {sigstr, pAddr};
            m_Signatures.push_back(sig_t);
            return pAddr;
        }
        base++;
    }
    return NULL;
}

CPointer* CBinaryFile::find_symbol(char* szSymbol)
{
#ifdef _WIN32
    unsigned long ulAddr = (unsigned long) GetProcAddress((HMODULE) m_ulAddr, szSymbol);
    return ulAddr ? new CPointer(ulAddr) : NULL;

#elif defined(__linux__)
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

    dlmap = (struct link_map *) m_ulAddr;
    symtab_hdr = NULL;
    strtab_hdr = NULL;

    dlfile = open(dlmap->l_name, O_RDONLY);
    if (dlfile == -1 || fstat(dlfile, &dlstat) == -1)
    {
        close(dlfile);
        return NULL;
    }

    /* Map library file into memory */
    file_hdr = (Elf32_Ehdr *)mmap(NULL, dlstat.st_size, PROT_READ, MAP_PRIVATE, dlfile, 0);
    map_base = (uintptr_t)file_hdr;
    if (file_hdr == MAP_FAILED)
    {
        close(dlfile);
        return NULL;
    }
    close(dlfile);

    if (file_hdr->e_shoff == 0 || file_hdr->e_shstrndx == SHN_UNDEF)
    {
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
            symtab_hdr = &hdr;

        else if (strcmp(section_name, ".strtab") == 0)
            strtab_hdr = &hdr;
    }

    /* Uh oh, we don't have a symbol table or a string table */
    if (symtab_hdr == NULL || strtab_hdr == NULL)
    {
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
            continue;

        if (strcmp(symbol, sym_name) == 0)
        {
            sym_addr = (void *)(dlmap->l_addr + sym.st_value);
            break;
        }
    }

    // Unmap the file now.
    munmap(file_hdr, dlstat.st_size);
    return sym_addr ? new CPointer((unsigned long) sym_addr) : NULL;

#else
#error "BinaryFile::find_symbol() is not implemented on this OS"
#endif
}

CPointer* CBinaryFile::find_pointer(object szSignature, int iLength, int iOffset)
{
    CPointer* ptr = find_signature(szSignature, iLength);
    return ptr ? ptr->get_ptr(iOffset) : NULL;
}

//-----------------------------------------------------------------------------
// BinaryManager class
//-----------------------------------------------------------------------------
// Small helper function
bool str_ends_with(char *szString, char *szSuffix)
{
    int stringlen = strlen(szString);
    int suffixlen = strlen(szSuffix);
    if (suffixlen >  stringlen)
        return false;

    return strncmp(szString + stringlen - suffixlen, szSuffix, suffixlen) == 0;
}

CBinaryFile* CBinaryManager::find_binary(char* szPath)
{
    char szBinaryPath[MAX_BINARY_PATH];

    // Add file extension, if missing
    if (!str_ends_with(szPath, FILE_EXTENSION))
        sprintf_s(szBinaryPath, "%s" FILE_EXTENSION, szPath);
    else
        sprintf_s(szBinaryPath, "%s", szPath);

    unsigned long ulAddr = (unsigned long) dlLoadLibrary(szPath);
    if (!ulAddr)
        return NULL;

    // Search for an existing BinaryFile object
    for (std::list<CBinaryFile *>::iterator iter=m_Binaries.begin(); iter != m_Binaries.end(); iter++)
    {
        CBinaryFile* binary = *iter;
        if (binary->get_address() == ulAddr)
        {
            // We don't need to open it several times
            dlFreeLibrary((DLLib *) ulAddr);
            return binary;
        }
    }

    unsigned long ulSize;

#ifdef _WIN32
    IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER *) ulAddr;
    IMAGE_NT_HEADERS* nt  = (IMAGE_NT_HEADERS *) ((BYTE *) dos + dos->e_lfanew);
    ulSize = nt->OptionalHeader.SizeOfImage;
    
#elif defined(__linux__)
    // TODO: Retrieve whole size
    struct stat buf;
    if (stat(path, &buf) == -1)
    {
        dlFreeLibrary((DLLib *) ulAddr);
        return NULL;
    }
    ulSize = buf.st_size;

#else
#error "BinaryManager::find_binary() is not implemented on this OS"
#endif

    // Create a new Binary object and add it to the list
    CBinaryFile* binary = new CBinaryFile(ulAddr, ulSize);
    m_Binaries.push_front(binary);
    return binary;
}

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------
CBinaryFile* find_binary(char* szPath)
{
    return s_pBinaryManager->find_binary(szPath);
}