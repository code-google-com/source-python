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
// Utility function to find send table props.
//---------------------------------------------------------------------------------
SendProp* UTIL_FindSendProp( SendTable* send_table, const char* prop_name )
{
	for( int prop_idx = 0; prop_idx < send_table->GetNumProps(); prop_idx++ )
	{
		// Get the property at this location.
		SendProp* prop = send_table->GetProp(prop_idx);

		// Return if we found the prop.
		if( V_strcmp(prop->GetName(), prop_name) == 0 )
		{
			return prop;
		}

		// If this prop is a data table, recurse down the line.
		if( prop->GetDataTable() )
		{
			return UTIL_FindSendProp(prop->GetDataTable(), prop_name);
		}
	}

	// If we hit this line, we couldn't find the prop.
	DevMsg(2, "[SP]: UTIL_FindSendProp(%x, %s); could not find send prop!\n",
		send_table, prop_name);

	return NULL;
}

//---------------------------------------------------------------------------------
// Loops through a data table and prints out the property information, recursively
// if necessary.
//---------------------------------------------------------------------------------
void DumpServerClassProps(SendTable* pTable, int iTabLevel)
{
	if (iTabLevel > 16)
	{
		return;
	}

	static const char* szTabs = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

	int iNumProps = pTable->GetNumProps();
	Msg(" [%d properties]:\n", iNumProps);
	for(int i=0; i < iNumProps; ++i)
	{
		char* szType;
		SendProp* pProp = pTable->GetProp(i);
		switch (pProp->GetType())
		{
		case DPT_Int:
			szType = "int";
			break;
		case DPT_Float:
			szType = "float";
			break;
		case DPT_Vector:
			szType = "vector";
			break;
		case DPT_VectorXY:
			szType = "vectorXY";
			break;
		case DPT_String:
			szType = "string";
			break;
		case DPT_Array:
			szType = "array";
			break;
		case DPT_DataTable:
			szType = "datatable";
			break;
		case DPT_Int64:
			szType = "int64";
			break;
		default:
			szType = "**Unknown**";
			break;
		}

		Msg("%*.*s%s %s (offset %d) ", iTabLevel, iTabLevel, szTabs, szType, pProp->GetName(), pProp->GetOffset());
		if (pProp->GetType() == DPT_DataTable && strcmp(pProp->GetName(), "baseclass") != 0)
		{
			DumpServerClassProps(pProp->GetDataTable(), iTabLevel + 1);
		}
		else
		{
			Msg("\n");
		}
	}
}

//---------------------------------------------------------------------------------
// Helpful function to dump all of the server classes and their respective
// properties.
//---------------------------------------------------------------------------------
void DumpServerClasses()
{
	// Need this external.
	extern IServerGameDLL* servergamedll;

	// Iterate through all of the send tables.
	SendTable* pSendTable = NULL;
	ServerClass* pCurrentServerClass = servergamedll->GetAllServerClasses();
	while (pCurrentServerClass)
	{
		Msg("%s %d", pCurrentServerClass->GetName(), pCurrentServerClass->m_InstanceBaselineIndex);
		DumpServerClassProps(pCurrentServerClass->m_pTable, 1);
		pCurrentServerClass = pCurrentServerClass->m_pNext;
	}
}

//---------------------------------------------------------------------------------
// Console command to dump server props.
//---------------------------------------------------------------------------------
CON_COMMAND( sp_dump_props, "Dumps entity properties." )
{
	DumpServerClasses();
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
	// Get the base entity. This saves us from having to call
	// this code repeatedly.
	IServerUnknown* entity_unknown = edict->GetUnknown();
	m_base_entity = entity_unknown->GetBaseEntity();

	// See if we have the prop in the hash table.
	bool bFound = false;
	unsigned int prop_offset = 
		PropHashTable()->get_offset(prop_name, bFound);
	
	// If we didn't find it, search the send table manually.
	if( !bFound )
	{
		ServerClass* server_class = edict->GetNetworkable()->GetServerClass();
		SendTable* send_table = server_class->m_pTable;
		SendProp* prop = UTIL_FindSendProp(send_table, prop_name);

		if( prop )
		{
			// Store the values in the class.
			m_send_prop = prop;
			m_prop_offset = m_send_prop->GetOffset();

			// Store the value in the prop hash table.
			PropHashTable()->insert_offset(prop_name, m_prop_offset);

			// Done.
			return;
		}
	}

	// Guess we didn't find it.
	m_prop_offset = 0;
	m_prop_offset = NULL;
}

SendPropType CSendProp::get_prop_type()
{
	if( m_send_prop )
	{
		return m_send_prop->GetType();
	}

	return (SendPropType)-1;
}

void CSendProp::set_prop_int( int value )
{
	if( m_send_prop && (get_prop_type() == DPT_Int) )
	{
		*(int *)((char *)m_base_entity + m_prop_offset) = value;
	}
}

void CSendProp::set_prop_float( float value )
{
	if( m_send_prop && (get_prop_type() == DPT_Float) )
	{
		*(float *)((char *)m_base_entity + m_prop_offset) = value;
	}
}

int CSendProp::get_prop_int()
{
	if( m_send_prop && (get_prop_type() == DPT_Int) )
	{
		return *(int *)((char *)m_base_entity + m_prop_offset);
	}

	return -1;
}

float CSendProp::get_prop_float()
{
	if( m_send_prop && (get_prop_type() == DPT_Float) )
	{
		return *(float *)((char *)m_base_entity + m_prop_offset);
	}

	return -1.0f;
}