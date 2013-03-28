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
#include "entities_props.h"

//---------------------------------------------------------------------------------
// Global accessor.
//----------------------------------------------------------------------------------
CSendPropHashTable s_PropHashTable;
CSendPropHashTable* PropHashTable()
{
	return &s_PropHashTable;
}

//----------------------------------------------------------------------------------
// CSendPropHashtable code.
//----------------------------------------------------------------------------------
CSendPropHashTable::CSendPropHashTable() :
	m_prop_table(
		32768, 
		0, 
		0, 
		&CSendPropHashTable::hash_compare, 
		&CSendPropHashTable::hash_key
	)
{

}

CSendPropHashTable::~CSendPropHashTable()
{
	// Free the names of the props since we use strdup.
	for( int i = 0; i < m_prop_table.Count(); i++ )
	{
		CPropOffset* prop_offset = &m_prop_table[i];
		delete prop_offset->prop_name;
		prop_offset->prop_name = nullptr;
	}
}

bool CSendPropHashTable::hash_compare( const CPropOffset& a, const CPropOffset& b )
{
	return (V_strcmp(a.prop_name, b.prop_name) == 0);
}

unsigned int CSendPropHashTable::hash_key( const CPropOffset& a )
{
	const char* prop_name = a.prop_name;
	unsigned int hash = 98317;
	unsigned int c;

	while( c= *prop_name++ )
	{
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

unsigned int CSendPropHashTable::get_offset( const char* prop_name, bool& was_found )
{
	// Construct a temporary hash table element
	// to search with.
	CPropOffset prop_offset_data;
	
	prop_offset_data.prop_name = prop_name;
	prop_offset_data.prop_offset = 0;

	// Search the table.
	UtlHashHandle_t prop_offset_handle = 
		m_prop_table.Find(prop_offset_data);

	// Return the value if we found one.
	if( prop_offset_handle != m_prop_table.InvalidHandle() )
	{
		was_found = true;
		return m_prop_table.Element(prop_offset_handle).prop_offset;
	}

	// Could not find the requested prop.
	was_found = false;
	return 0;
}

void CSendPropHashTable::insert_offset( const char* name, unsigned int offset )
{
	// Construct the prop structure. Since this is basically a
	// struct, no need to deep copy.
	CPropOffset prop_data;

	// Copy the prop name since it won't hang around in memory after
	// return.
	prop_data.prop_name = strdup(name);

	// Store off the offset.
	prop_data.prop_offset = offset;

	// Put this data in the table.
	m_prop_table.Insert(prop_data);
}

void CSendPropHashTable::remove_offset( const char* prop_name )
{
	// Construct a temp structure to find the offset.
	CPropOffset prop_offset;

	prop_offset.prop_name = prop_name;
	prop_offset.prop_offset = 0;

	// Find the index of the element.
	UtlHashHandle_t prop_offset_handle = 
		m_prop_table.Find(prop_offset);

	// If we found the offset, get rid of the prop data.
	if( prop_offset_handle != m_prop_table.InvalidHandle() )
	{
		// Free the string memory first.
		CPropOffset* element = &m_prop_table[prop_offset_handle];
		delete element->prop_name;

		// Remove the data now.
		m_prop_table.Remove(prop_offset_handle);
	}
}