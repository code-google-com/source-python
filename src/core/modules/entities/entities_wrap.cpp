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
#include "entities_props.h"
#include "entities_wrap.h"
#include "server_class.h"
#include "dt_common.h"
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
	m_is_valid = (m_edict_ptr != NULL);
}

CEdict::CEdict( int index )
{
	m_edict_ptr = PEntityOfEntIndex(index);
	m_is_valid = (m_edict_ptr != NULL);
}

CEdict::CEdict( const char* name, bool bExact /* = true */ )
{
	const int max_entities = gpGlobals->maxEntities;
	for( int i = 0; i < max_entities; i++ )
	{
		edict_t* edict = &gpGlobals->pEdicts[i];
		
		// Rule out empty edicts.
		if( !edict || edict->IsFree() ) {
			continue;
		}

		// Check the name if we want a partial match.
		if( !bExact ) 
		{
			if( V_stristr(edict->GetClassName(), name) ) 
			{
				m_edict_ptr = edict;
				m_is_valid = true;
				m_index = i;
				return;
			}
		}
		else 
		{
			// Compare names otherwise.
			if( V_strcmp(edict->GetClassName(), name) == 0 )
			{
				m_edict_ptr = edict;
				m_is_valid = true;
				m_index = i;
				return;
			}
		}
	}

	m_edict_ptr = NULL;
	m_is_valid = false;
	m_index = -1;
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

bool CEdict::is_valid() const
{
	return m_is_valid;
}

int CEdict::get_index() const
{
	return m_index;
}

CServerNetworkable* CEdict::get_networkable() const
{
	IServerNetworkable* networkable = m_edict_ptr->GetNetworkable();
	CServerNetworkable* new_networkable = new CServerNetworkable(networkable);
	return new_networkable;
}

CSendProp* CEdict::get_prop( const char* prop_name ) const
{
	return new CSendProp(m_edict_ptr, prop_name);
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
// CServerNetworkable code.
//---------------------------------------------------------------------------------
CServerNetworkable::CServerNetworkable( IServerNetworkable* server_networkable )
{
	m_server_networkable = server_networkable;
}

CHandleEntity* CServerNetworkable::get_entity_handle()
{
	IHandleEntity* handle = m_server_networkable->GetEntityHandle();
	CHandleEntity* new_handle = new CHandleEntity(handle);
	return new_handle;
}

CEdict* CServerNetworkable::get_edict()
{
	edict_t* edict = m_server_networkable->GetEdict();
	CEdict* new_edict = new CEdict(edict);
	return new_edict;
}

const char* CServerNetworkable::get_class_name()
{
	return m_server_networkable->GetClassName();
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

//---------------------------------------------------------------------------------
// CServerEntity code.
//---------------------------------------------------------------------------------
CServerEntity::CServerEntity( IServerEntity* server_entity )
{
	m_server_entity = server_entity;
}

int CServerEntity::get_model_index() const
{
	return m_server_entity->GetModelIndex();
}

void CServerEntity::set_model_index( int index )
{
	m_server_entity->SetModelIndex(index);
}

const char* CServerEntity::get_model_name()
{
	return m_server_entity->GetModelName().ToCStr();
}

//---------------------------------------------------------------------------------
// CSendProp code.
//---------------------------------------------------------------------------------
CSendProp::CSendProp( edict_t* edict, const char* prop_name )
{
	// Set default values.
	m_send_prop = NULL;
	m_prop_offset = 0;
	m_edict = edict;

	if( !m_edict )
	{
		DevMsg(1, "[SP]: m_edict was not valid!\n");
		return;
	}

	// Get the base entity. This saves us from having to call
	// this code repeatedly.
	IServerUnknown* entity_unknown = m_edict->GetUnknown();
	m_base_entity = entity_unknown->GetBaseEntity();

	// First search the hash table to see if we have a prop
	// with the same name.
	m_send_prop = PropHashTable()->get_prop(prop_name);
	
	// If we didn't find it, search the send table manually.
	if( !m_send_prop )
	{
		// Get the send table for this entity.
		ServerClass* server_class = edict->GetNetworkable()->GetServerClass();
		SendTable* send_table = server_class->m_pTable;

		// Search for the prop in the send table.
		m_send_prop = UTIL_FindSendProp(send_table, prop_name);

		if( m_send_prop )
		{
			// Cache off the prop offset so we don't have to keep
			// calling GetOffset repeatedly.
			m_prop_offset = m_send_prop->GetOffset();

			// Store the value in the prop hash table.
			PropHashTable()->insert_offset(prop_name, m_send_prop);
		}
	}
	else
	{
		// Prop was valid. Store off the offset.
		m_prop_offset = m_send_prop->GetOffset();
	}
}

SendPropType CSendProp::get_type()
{
	if( m_send_prop )
	{
		return m_send_prop->GetType();
	}

	return (SendPropType)-1;
}

void CSendProp::set_int( int value )
{
	if( m_send_prop && (get_type() == DPT_Int) )
	{
		// Set the value.
		*(int *)((char *)m_base_entity + m_prop_offset) = value;

		// Force a network update.
		m_edict->StateChanged(m_prop_offset);
	}
}

void CSendProp::set_float( float value )
{
	if( m_send_prop && (get_type() == DPT_Float) )
	{
		// Set the value.
		*(float *)((char *)m_base_entity + m_prop_offset) = value;

		// Force a network update.
		m_edict->StateChanged(m_prop_offset);
	}
}

void CSendProp::set_string( const char* value )
{
	if( m_send_prop && (get_type() == DPT_String) )
	{
		// Get the address of the string buffer.
		char* data_buffer = (char *)((char *)m_base_entity + m_prop_offset);

		// Write the string to the buffer.
		V_strncpy(data_buffer, value, DT_MAX_STRING_BUFFERSIZE);

		// Force a network update.
		m_edict->StateChanged(m_prop_offset);
	}
}

int CSendProp::get_int()
{
	if( m_send_prop && (get_type() == DPT_Int) )
	{
		return *(int *)((char *)m_base_entity + m_prop_offset);
	}

	return -1;
}

float CSendProp::get_float()
{
	if( m_send_prop && (get_type() == DPT_Float) )
	{
		return *(float *)((char *)m_base_entity + m_prop_offset);
	}

	return -1.0f;
}

const char* CSendProp::get_string()
{
	if( m_send_prop && (get_type() == DPT_String) )
	{
		return (const char *)((char *)m_base_entity + m_prop_offset);
	}

	return "";
}

