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
#include <string>

#include "dyncall.h"
#include "dyncall_signature.h"

#include "detour_class.h"
#include "detourman_class.h"
#include "memory_hooks.h"
#include "dd_utils.h"

#include "memory_tools.h"
#include "utility/wrap_macros.h"


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
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")

    if (bIsPtr)
        return get<char *>(iOffset);

    return (char *) (m_ulAddr + iOffset);
}

void CPointer::set_string(char* szText, int iSize /* = 0 */, int iOffset /* = 0 */, bool bIsPtr /* = true */)
{
    if (!is_valid())
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")

    if (!iSize)
    {
        iSize = getMemSize((void *) (m_ulAddr + iOffset));
        if(!iSize)
            BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Unable to retrieve size of address.")
    }
        
    if ((int ) strlen(szText) > iSize)
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "String exceeds size of memory block.")

    if (bIsPtr)
        set<char *>(szText, iOffset);
    else
        strcpy((char *) (m_ulAddr + iOffset), szText);
}

CPointer* CPointer::get_ptr(int iOffset /* = 0 */)
{
    if (!is_valid())
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")

    return new CPointer(*(unsigned long *) (m_ulAddr + iOffset));
}

void CPointer::set_ptr(CPointer* ptr, int iOffset /* = 0 */)
{
    if (!is_valid())
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")

    *(unsigned long *) m_ulAddr = ptr->get_address();
}

CPointer* CPointer::get_virtual_func(int iIndex, bool bPlatformCheck /* = true */)
{
    if (!is_valid())
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Pointer is NULL.")

#ifdef __linux__
    if (bPlatformCheck)
        iIndex++;
#endif

    void** vtable = *(void ***) m_ulAddr;
    if (!vtable)
        return new CPointer();

    return new CPointer((unsigned long) vtable[iIndex]);
}

object CPointer::call(Convention eConv, char* szParams, object args)
{
    if (!is_valid())
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Function pointer is NULL.")

    dcReset(g_pCallVM);
    dcMode(g_pCallVM, eConv);
    char* ptr = szParams;
    int pos = 0;
    char ch;
    while ((ch = *ptr) != '\0' && ch != ')')
    {
        object arg = args[pos];
        switch(ch)
        {
            case DC_SIGCHAR_BOOL:      dcArgBool(g_pCallVM, extract<bool>(arg)); break;
            case DC_SIGCHAR_CHAR:      dcArgChar(g_pCallVM, extract<char>(arg)); break;
            case DC_SIGCHAR_UCHAR:     dcArgChar(g_pCallVM, extract<unsigned char>(arg)); break;
            case DC_SIGCHAR_SHORT:     dcArgShort(g_pCallVM, extract<short>(arg)); break;
            case DC_SIGCHAR_USHORT:    dcArgShort(g_pCallVM, extract<unsigned short>(arg)); break;
            case DC_SIGCHAR_INT:       dcArgInt(g_pCallVM, extract<int>(arg)); break;
            case DC_SIGCHAR_UINT:      dcArgInt(g_pCallVM, extract<unsigned int>(arg)); break;
            case DC_SIGCHAR_LONG:      dcArgLong(g_pCallVM, extract<long>(arg)); break;
            case DC_SIGCHAR_ULONG:     dcArgLong(g_pCallVM, extract<unsigned long>(arg)); break;
            case DC_SIGCHAR_LONGLONG:  dcArgLongLong(g_pCallVM, extract<long long>(arg)); break;
            case DC_SIGCHAR_ULONGLONG: dcArgLongLong(g_pCallVM, extract<unsigned long long>(arg)); break;
            case DC_SIGCHAR_FLOAT:     dcArgFloat(g_pCallVM, extract<float>(arg)); break;
            case DC_SIGCHAR_DOUBLE:    dcArgDouble(g_pCallVM, extract<double>(arg)); break;
            case DC_SIGCHAR_POINTER:   dcArgPointer(g_pCallVM, ExtractPyPtr(arg)); break;
            case DC_SIGCHAR_STRING:    dcArgPointer(g_pCallVM, (unsigned long) (void *) extract<char *>(arg)); break;
            default: BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Unknown parameter type.")
        }
        pos++; ptr++;
    }
    
    if (pos != len(args))
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "String parameter count does not equal with length of tuple.")

    if (ch == '\0')
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "String parameter has no return type.")

    switch(*++ptr)
    {
        case DC_SIGCHAR_VOID: dcCallVoid(g_pCallVM, m_ulAddr);
        case DC_SIGCHAR_BOOL:      return object(dcCallBool(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_CHAR:      return object(dcCallChar(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_UCHAR:     return object((unsigned char) dcCallChar(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_SHORT:     return object(dcCallShort(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_USHORT:    return object((unsigned short) dcCallShort(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_INT:       return object(dcCallInt(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_UINT:      return object((unsigned int) dcCallInt(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_LONG:      return object(dcCallLong(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_ULONG:     return object((unsigned long) dcCallLong(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_LONGLONG:  return object(dcCallLongLong(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_ULONGLONG: return object((unsigned long long) dcCallLongLong(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_FLOAT:     return object(dcCallFloat(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_DOUBLE:    return object(dcCallDouble(g_pCallVM, m_ulAddr));
        case DC_SIGCHAR_POINTER:   return object(CPointer(dcCallPointer(g_pCallVM, m_ulAddr)));
        case DC_SIGCHAR_STRING:    return object((const char *) dcCallPointer(g_pCallVM, m_ulAddr));
        default: BOOST_RAISE_EXCEPTION(PyExc_TypeError, "Unknown return type.")
    }
    return object();
}

object CPointer::call_trampoline(object args)
{
    CDetour* pDetour = g_DetourManager.Find_Detour((void *) m_ulAddr);
    if (!pDetour)
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Function was not hooked.")

    CFuncObj* pFuncObj = pDetour->GetFuncObj();
    std::string szParams = "";

    eCallConv conv = pFuncObj->GetConvention();
    if (conv == CONV_THISCALL)
        szParams += DC_SIGCHAR_POINTER;
    
    for(unsigned int i=0; i < pFuncObj->GetNumArgs(); i++)
        szParams += TypeEnumToChar(pFuncObj->GetArg(i)->GetType());

    szParams += ')';
    szParams += TypeEnumToChar(pFuncObj->GetRetType()->GetType());
    CPointer ptr = CPointer((unsigned long) pDetour->GetTrampoline());
    return ptr.call((Convention) conv, (char *) szParams.data(), args);
}

void CPointer::hook(Convention eConv, char* szParams, eHookType eType, PyObject* callable)
{
    CDetour* pDetour = g_DetourManager.Add_Detour((void*) m_ulAddr, szParams, (eCallConv) eConv);
    if (!pDetour)
        BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Failed to hook function.")

    ICallbackManager* mngr = pDetour->GetManager("Python", eType);
    if (!mngr)
    {
        mngr = new CCallbackManager;
        pDetour->AddManager(mngr, eType);
    }

    mngr->Add((void *) callable, eType);
}

void CPointer::unhook(eHookType eType, PyObject* callable)
{
    CDetour* pDetour = g_DetourManager.Find_Detour((void *) m_ulAddr);
    if (!pDetour)
        return;

    ICallbackManager* mngr = pDetour->GetManager("Python", eType);
    if (mngr)
        mngr->Remove((void *) callable, eType);
}

int get_error()
{
    return dcGetError(g_pCallVM);
}