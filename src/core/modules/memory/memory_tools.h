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

#ifndef _MEMORY_TOOLS_H
#define _MEMORY_TOOLS_H

#include "memalloc.h"
#include "boost/python.hpp" 

using namespace boost::python;

//-----------------------------------------------------------------------------
// CPointer class
//-----------------------------------------------------------------------------
class CPointer
{
public:
    CPointer(unsigned long ulAddr = 0);

    template<class T>
    T get(int iOffset = 0)
    {
        return *(T *) (m_ulAddr + iOffset);
    }

    template<class T>
    void set(T value, int iOffset = 0)
    {
        unsigned long newAddr = m_ulAddr + iOffset;
        *(T *) newAddr = value;
    }
    
    const char *        get_string(int iOffset = 0, bool bIsPtr = true);
    void                set_string(char* szText, int iSize = 0, int iOffset = 0, bool bIsPtr = true);
    CPointer*           get_ptr(int iOffset = 0);
    void                set_ptr(CPointer* ptr, int iOffset = 0);

    unsigned long       get_size() { return g_pMemAlloc->GetSize((void *) m_ulAddr); }
    unsigned long       get_address() { return m_ulAddr; }

    CPointer*           add(int iValue);
    CPointer*           sub(int iValue);
    bool                is_valid() { return m_ulAddr ? true: false; }

    CPointer*           get_virtual_func(int iIndex, bool bPlatformCheck = true);
    
    void                alloc(int iSize) { m_ulAddr = (unsigned long) g_pMemAlloc->IndirectAlloc(iSize); }
    void                realloc(int iSize) { m_ulAddr = (unsigned long) g_pMemAlloc->Realloc((void *) m_ulAddr, iSize); }
    void                dealloc() { g_pMemAlloc->Free((void *) m_ulAddr); m_ulAddr = 0; }

    object              call(int iConvention, char* szParams, object args);
    object              call_trampoline(object args);

    void                hook(int iConvention, char* szParams, int iHookType, PyObject* callable);
    void                unhook(int iHookType, PyObject* callable);

private:
    unsigned long m_ulAddr;
};

#endif // _MEMORY_TOOLS_H