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
#ifndef _ENTITIES_WRAP_H
#define _ENTITIES_WRAP_H

//---------------------------------------------------------------------------------
// Includes.
//---------------------------------------------------------------------------------
#include "edict.h"
#include <cstdint>

//---------------------------------------------------------------------------------
// Forward declarations
//---------------------------------------------------------------------------------
class CServerEntity;
class CServerNetworkable;
class CServerUnknown;

//---------------------------------------------------------------------------------
// The base class for all entities.
// Note: This class may not be instantiated directly.
//---------------------------------------------------------------------------------
class CEdict
{
public:
	// This awful hack allows us to convert pointers returned by
	// dyncall to the edict class.
	// CEdict( uintptr_t edict_ptr );
	CEdict( int index );

	// For engine use.
	CEdict( edict_t* edict_ptr );

	// virtual const CServerEntity*			get_iserverentity() const;
	// virtual const CServerNetworkable*	get_networkable() const;
	// virtual const CServerUnknown*		get_unknown() const;

	virtual int							area_num() const;
	virtual const char*					get_class_name() const;

	virtual bool						is_free() const;
	virtual	void						set_free();
	virtual void						clear_free();

private:
	edict_t* m_edict_ptr;
};


//---------------------------------------------------------------------------------
// CBaseHandleEntity wrapper class.
//---------------------------------------------------------------------------------
class CBaseEntityHandle
{
public:
	CBaseEntityHandle( int handle );
	CBaseEntityHandle( const CBaseHandle& other );

	bool	is_valid();
	
	int		get_entry_index() const;
	int		get_serial_number() const;
	
	int		to_int() const;

private:
	CBaseHandle m_base_handle;
};

//---------------------------------------------------------------------------------
// IHandleEntity wrapper class.
//---------------------------------------------------------------------------------
class CHandleEntity
{
public:
	CHandleEntity( IHandleEntity* handle_entity );

	const CBaseEntityHandle* get_ref_ehandle() const;

private:
	IHandleEntity* m_handle_entity;
};


#endif