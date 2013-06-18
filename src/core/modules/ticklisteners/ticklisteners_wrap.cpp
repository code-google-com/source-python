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
#include "ticklisteners_wrap.h"

CUtlVector<PyObject*> vecCallables;

//-----------------------------------------------------------------------------
// Adds a callable to the end of the CTickListenerManager vector.
//-----------------------------------------------------------------------------
void CTickListenerManager::add_listener(PyObject* pCallable)
{
	if( !vecCallables.HasElement(pCallable))
	{
		vecCallables.AddToTail(pCallable);
	}
}

//-----------------------------------------------------------------------------
// Removes all instances of a callable from the CTickListenerManager vector.
//-----------------------------------------------------------------------------
void CTickListenerManager::remove_listener(PyObject* pCallable)
{
	vecCallables.FindAndRemove(pCallable);
}

//-----------------------------------------------------------------------------
// Returns whether or not the given callable is registered.
//-----------------------------------------------------------------------------
bool CTickListenerManager::is_registered(PyObject* pCallable)
{
	return vecCallables.HasElement(pCallable);
}

//-----------------------------------------------------------------------------
// Returns the number of registered callbacks.
//-----------------------------------------------------------------------------
int CTickListenerManager::count()
{
	return vecCallables.Count();
}

//-----------------------------------------------------------------------------
// Returns the callback from the given index.
//-----------------------------------------------------------------------------
PyObject* CTickListenerManager::get_value_from_index(int iIndex)
{
	if(iIndex > vecCallables.Count() - 1)
	{
		return NULL;
	}
	return vecCallables[iIndex];
}

//-----------------------------------------------------------------------------
// Calls all registered tick listeners.
//-----------------------------------------------------------------------------
void CTickListenerManager::call_tick_listeners()
{
	for(int i = 0; i < vecCallables.Count(); i++)
	{
		BEGIN_BOOST_PY()
			call<void>(vecCallables[i]);
		END_BOOST_PY_NORET()
	}
}
