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

#include <malloc.h>
#include "memalloc.h"
#include "utility/wrap_macros.h"
#include "hook_types.h"
#include "dyncall.h"
#include "boost/python.hpp" 
using namespace boost::python;


//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
inline size_t getMemSize(void* ptr)
{
#ifdef _WIN32
    return g_pMemAlloc->GetSize(ptr);
#elif defined(__linux__)
    return malloc_usable_size(ptr);
#else
    #error "Implement me!"
#endif
}

inline void* allocate(size_t size)
{
#ifdef _WIN32
    return g_pMemAlloc->IndirectAlloc(size);
#elif defined(__linux__)
    return malloc(size);
#else
    #error "Implement me!"
#endif
}

inline void* reallocate(void* ptr, size_t size)
{
#ifdef _WIN32
    return g_pMemAlloc->Realloc(ptr, size);
#elif defined(__linux__)
    return realloc(ptr, size);
#else
    #error "Implement me!"
#endif
}

inline void deallocate(void* ptr)
{
#ifdef _WIN32
    g_pMemAlloc->Free(ptr);
#elif defined(__linux__)
    free(ptr);
#else
    #error "Implement me!"
#endif
}

//-----------------------------------------------------------------------------
// Convention enum
//-----------------------------------------------------------------------------
enum Convention
{
    _CONV_CDECL = DC_CALL_C_DEFAULT,
#ifdef _WIN32
    _CONV_STDCALL = DC_CALL_C_X86_WIN32_STD,
    _CONV_FASTCALL = DC_CALL_C_X86_WIN32_FAST_MS,
    _CONV_THISCALL = DC_CALL_C_X86_WIN32_THIS_MS
#else
    _CONV_FASTCALL = DC_CALL_C_X86_WIN32_FAST_GNU,
    _CONV_THISCALL = DC_CALL_C_X86_WIN32_THIS_GNU
#endif
};

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
        if (!is_valid())
            BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")

        return *(T *) (m_ulAddr + iOffset);
    }

    template<class T>
    void set(T value, int iOffset = 0)
    {
        if (!is_valid())
            BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")

        unsigned long newAddr = m_ulAddr + iOffset;
        *(T *) newAddr = value;
    }
    
    const char *        get_string(int iOffset = 0, bool bIsPtr = true);
    void                set_string(char* szText, int iSize = 0, int iOffset = 0, bool bIsPtr = true);
    CPointer*           get_ptr(int iOffset = 0);
    void                set_ptr(CPointer* ptr, int iOffset = 0);

    unsigned long       get_size() { return getMemSize((void *) m_ulAddr); }
    unsigned long       get_address() { return m_ulAddr; }

    CPointer*           add(int iValue);
    CPointer*           sub(int iValue);
    bool                is_valid() { return m_ulAddr ? true: false; }

    CPointer*           get_virtual_func(int iIndex, bool bPlatformCheck = true);
    
    void                alloc(int iSize) { m_ulAddr = (unsigned long) allocate(iSize); }
    void                realloc(int iSize) { m_ulAddr = (unsigned long) reallocate((void *) m_ulAddr, iSize); }
    void                dealloc() { deallocate((void *) m_ulAddr); m_ulAddr = 0; }

    object              call(Convention eConv, char* szParams, object args);
    object              call_trampoline(object args);

    void                hook(Convention eConv, char* szParams, eHookType eType, PyObject* callable);
    void                unhook(eHookType eType, PyObject* callable);

private:
    unsigned long m_ulAddr;
};

int get_error();

inline unsigned long ExtractPyPtr(object obj)
{
    if (strcmp(extract<char *>(obj.attr("__class__").attr("__name__")), "CPointer") == 0)
    {
        CPointer* pPtr = extract<CPointer *>(obj);
        return pPtr->get_address();
    }
    return extract<unsigned long>(obj);
}

#endif // _MEMORY_TOOLS_H