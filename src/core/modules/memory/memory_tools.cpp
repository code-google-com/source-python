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
#include "memory_tools.h"
#include "utility/wrap_macros.h"
#include "dyncall.h"
#include "dyncall_signature.h"


DCCallVM* g_pCallVM = dcNewCallVM(4096);

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
    }

    if (bIsPtr)
        return get<char *>(iOffset);

    return (char *) (m_ulAddr + iOffset);
}

void CPointer::set_string(char* szText, int iSize /* = 0 */, int iOffset /* = 0 */, bool bIsPtr /* = true */)
{
    if (!is_valid())
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")
    }

    if (!iSize)
    {
        iSize = g_pMemAlloc->GetSize((void *) (m_ulAddr + iOffset));
        if(!iSize)
        {
            BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Unable to retrieve size of address.")
        }
    }
        
    if ((int ) strlen(szText) > iSize)
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "String exceeds size of memory block.")
    }

    if (bIsPtr)
        set<char *>(szText, iOffset);
    else
        strcpy((char *) (m_ulAddr + iOffset), szText);
}

CPointer* CPointer::get_ptr(int iOffset /* = 0 */)
{
    if (!is_valid())
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")
    }

    unsigned long ulNewAddr = *(unsigned long *) (m_ulAddr + iOffset);
    return ulNewAddr ? new CPointer(ulNewAddr) : NULL;
}

CPointer* CPointer::get_virtual_func(int iIndex, bool bPlatformCheck /* = true */)
{
    if (!is_valid())
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")
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

object CPointer::call(int iConvention, char* szParams, tuple args)
{
    if (!is_valid())
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Function pointer is NULL.")
    }

    dcReset(g_pCallVM);
    dcMode(g_pCallVM, iConvention);
    char* ptr = szParams;
    int pos = 0;
    char ch;
    while ((ch = *ptr) != '\0' && ch != ')')
    {
        object arg = args[pos];
        switch(ch)
        {
            case DC_SIGCHAR_BOOL:     dcArgBool(g_pCallVM, extract<bool>(arg)); break;
            case DC_SIGCHAR_CHAR:     dcArgChar(g_pCallVM, extract<char>(arg)); break;
            case DC_SIGCHAR_SHORT:    dcArgShort(g_pCallVM, extract<short>(arg)); break;
            case DC_SIGCHAR_INT:      dcArgInt(g_pCallVM, extract<int>(arg)); break;
            case DC_SIGCHAR_LONG:     dcArgLong(g_pCallVM, extract<long>(arg)); break;
            case DC_SIGCHAR_LONGLONG: dcArgLongLong(g_pCallVM, extract<long long>(arg)); break;
            case DC_SIGCHAR_FLOAT:    dcArgFloat(g_pCallVM, extract<float>(arg)); break;
            case DC_SIGCHAR_DOUBLE:   dcArgDouble(g_pCallVM, extract<double>(arg)); break;
            case DC_SIGCHAR_POINTER:
            {
                unsigned long ulAddr;
                if (strcmp(extract<char *>(arg.attr("__class__").attr("__name__")), "CPointer") == 0)
                {
                    CPointer* pPtr = extract<CPointer *>(arg);
                    ulAddr = pPtr->get_address();
                }
                else
                    ulAddr = extract<unsigned long>(arg);

                dcArgPointer(g_pCallVM, ulAddr);
            } break;
            case DC_SIGCHAR_STRING:   dcArgPointer(g_pCallVM, (unsigned long) (void *) extract<char *>(arg)); break;
            default:
            {
                BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Unknown parameter type.")
            }
        }
        pos++; ptr++;
    }
    
    if (pos != len(args))
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "String parameter count does not equal with length of tuple.")
    }

    if (ch == '\0')
    {
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "String parameter has no return type.")
    }

    object retval = object();
    switch(*++ptr)
    {
        case DC_SIGCHAR_VOID: dcCallVoid(g_pCallVM, m_ulAddr); break;
        case DC_SIGCHAR_BOOL:     retval = object(dcCallBool(g_pCallVM, m_ulAddr)); break;
        case DC_SIGCHAR_CHAR:     retval = object(dcCallChar(g_pCallVM, m_ulAddr)); break;
        case DC_SIGCHAR_SHORT:    retval = object(dcCallShort(g_pCallVM, m_ulAddr)); break;
        case DC_SIGCHAR_INT:      retval = object(dcCallInt(g_pCallVM, m_ulAddr)); break;
        case DC_SIGCHAR_LONG:     retval = object(dcCallLong(g_pCallVM, m_ulAddr)); break;
        case DC_SIGCHAR_LONGLONG: retval = object(dcCallLongLong(g_pCallVM, m_ulAddr)); break;
        case DC_SIGCHAR_FLOAT:    retval = object(dcCallFloat(g_pCallVM, m_ulAddr)); break;
        case DC_SIGCHAR_DOUBLE:   retval = object(dcCallDouble(g_pCallVM, m_ulAddr)); break;
        case DC_SIGCHAR_POINTER:
        {
            unsigned long ulResult = dcCallPointer(g_pCallVM, m_ulAddr);
            retval = ulResult ? object(new CPointer(ulResult)) : object();
        } break;
        case DC_SIGCHAR_STRING: retval = object((const char *) dcCallPointer(g_pCallVM, m_ulAddr)); break;
        default:
        {
            BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Unknown return type.")
        }
    }
    return retval;
}