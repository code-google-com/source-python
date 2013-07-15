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

#ifndef _MEMORY_SCANNER_H
#define _MEMORY_SCANNER_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <list>
#include "modules/export_main.h"
#include "memory_tools.h"

struct Signature_t
{
    unsigned char* m_szSignature;
    unsigned long  m_ulAddr;
};


class CBinaryFile
{
public:
    CBinaryFile(unsigned long ulAddr, unsigned long uSize);

    CPointer* find_signature(object szSignature, int iLength);
    CPointer* find_symbol(char* szSymbol);
    CPointer* find_pointer(object szSignature, int iLength, int iOffset);

    unsigned long get_address() { return m_ulAddr; }
    unsigned long get_size() { return m_uSize; }

private:
    unsigned long          m_ulAddr;
    unsigned long          m_uSize;
    std::list<Signature_t> m_Signatures;
};


class CBinaryManager
{
public:
    CBinaryFile* find_binary(char* szPath);

private:
    std::list<CBinaryFile*> m_Binaries;
};

static CBinaryManager* s_pBinaryManager = new CBinaryManager();

CBinaryFile* find_binary(char* szPath);

#endif // _MEMORY_SCANNER_H