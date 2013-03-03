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

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "eiface.h"
#include "entities_wrap.h"
#include "server_class.h"
#include "utility/sp_util.h"

//---------------------------------------------------------------------------------
// If these aren't defined, we get linker errors about CBaseEdict.
//---------------------------------------------------------------------------------
IChangeInfoAccessor *CBaseEdict::GetChangeAccessor()
{
	return engine->GetChangeAccessor( (const edict_t *)this );
}

const IChangeInfoAccessor *CBaseEdict::GetChangeAccessor() const
{
	return engine->GetChangeAccessor( (const edict_t *)this );
}

//---------------------------------------------------------------------------------
// External variables.
//---------------------------------------------------------------------------------
extern CGlobalVars* gpGlobals;

//---------------------------------------------------------------------------------
// CEdict methods.
//---------------------------------------------------------------------------------
CEdict::CEdict( edict_t* edict_ptr )
{
	m_edict_ptr = edict_ptr;
}

CEdict::CEdict( int index )
{
	m_edict_ptr = PEntityOfEntIndex(index);
}

int CEdict::area_num() const
{
	return m_edict_ptr->AreaNum();
}

const char* CEdict::get_class_name() const
{
	return m_edict_ptr->GetClassName();
}

bool CEdict::is_free() const
{
	return m_edict_ptr->IsFree();
}

void CEdict::set_free()
{
	return m_edict_ptr->SetFree();
}

void CEdict::clear_free()
{
	m_edict_ptr->ClearFree();
}

//---------------------------------------------------------------------------------
// CBaseEntityHandle code.
//---------------------------------------------------------------------------------
CBaseEntityHandle::CBaseEntityHandle( int handle ) : m_base_handle(handle)
{
}

CBaseEntityHandle::CBaseEntityHandle( const CBaseHandle& other ) : m_base_handle(other)
{

}

bool CBaseEntityHandle::is_valid()
{
	return m_base_handle.IsValid();
}

int CBaseEntityHandle::get_entry_index() const
{
	return m_base_handle.GetEntryIndex();
}

int CBaseEntityHandle::get_serial_number() const
{
	return m_base_handle.GetSerialNumber();
}

int CBaseEntityHandle::to_int() const
{
	return m_base_handle.ToInt();
}

//---------------------------------------------------------------------------------
// CHandleEntity code.
//---------------------------------------------------------------------------------
CHandleEntity::CHandleEntity( IHandleEntity* handle_entity )
{
	m_handle_entity = handle_entity;
}

const CBaseEntityHandle* CHandleEntity::get_ref_ehandle() const
{
	const CBaseHandle& handle = m_handle_entity->GetRefEHandle();
	const CBaseEntityHandle* new_entity_handle = new CBaseEntityHandle(handle);
	return new_entity_handle;
}