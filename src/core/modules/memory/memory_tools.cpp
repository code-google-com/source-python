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
#include <stdlib.h>
#include "memalloc.h"
#include "modules/export_main.h"
#include "memory_tools.h"

//-----------------------------------------------------------------------------
// CPointer class
//-----------------------------------------------------------------------------
CPointer::CPointer(unsigned long ulAddr /* = 0 */)
{
    m_ulAddr = ulAddr;
}

CPointer* CPointer::add(int iValue)
{
    m_ulAddr += iValue;
    return this;
}

CPointer* CPointer::sub(int iValue)
{
    return add(-iValue);
}

const char * CPointer::get_string(int iOffset /* = 0 */, bool bIsPtr /* = true */)
{
    if (!is_valid())
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")
        return NULL;
    }

    if (bIsPtr)
        return get<char *>(iOffset);

    return (char *) (m_ulAddr + iOffset);
}

void CPointer::set_string(char* szText, int iSize /* = 0 */, int iOffset /* = 0 */)
{
    if (!is_valid())
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")
        return;
    }

    if (!iSize)
    {
        iSize = g_pMemAlloc->GetSize((void *) (m_ulAddr + iOffset));
        if(!iSize)
        {
            BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Unable to retrieve size of address.")
            return;
        }
    }
        
    if ((int ) strlen(szText) > iSize)
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "String exceeds size of memory block.")
        return;
    }

    // FIXME: We can't set arrays with this method, if we only got the address of that array.
    set<char *>(szText, iOffset);
}

CPointer* CPointer::get_ptr(int iOffset /* = 0 */)
{
    if (!is_valid())
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")
        return NULL;
    }

    unsigned long ulNewAddr = *(unsigned long *) (m_ulAddr + iOffset);
    return ulNewAddr ? new CPointer(ulNewAddr) : NULL;
}

CPointer* CPointer::get_virtual_func(int iIndex, bool bPlatformCheck /* = true */)
{
    if (!is_valid())
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")
        return NULL;
    }

#ifdef __linux__
    if (bPlatformCheck)
        iIndex++;
#endif

    void** vtable = *(void ***) m_ulAddr;
    if (!vtable)
        return NULL;

    void* pNewAddr = vtable[iIndex];
    return pNewAddr ? new CPointer((unsigned long) pNewAddr) : NULL;
}