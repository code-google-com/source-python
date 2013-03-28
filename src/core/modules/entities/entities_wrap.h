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
#include "server_class.h"
#include <cstdint>

//---------------------------------------------------------------------------------
// Forward declarations
//---------------------------------------------------------------------------------
class CServerEntity;
class CServerNetworkable;
class CServerUnknown;
class CServerClass;
class CSendProp;

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
	
	// Get edict instances by index.
	CEdict( int index );

	// Get edict instances by name.
	CEdict( const char* name, bool bExact = true );

	// For engine use.
	CEdict( edict_t* edict_ptr );

	virtual int							area_num() const;
	virtual const char*					get_class_name() const;

	virtual bool						is_free() const;
	virtual	void						set_free();
	virtual void						clear_free();

	// Helper methods.
	virtual bool						is_valid() const;
	virtual int							get_index() const;

	// Send property methods.
	virtual CSendProp*					get_prop( const char* prop_name ) const;

private:
	edict_t*	m_edict_ptr;
	bool		m_is_valid;
	int			m_index;
};


//---------------------------------------------------------------------------------
// Custom SendProp wrapper.
//---------------------------------------------------------------------------------
class CSendProp
{
public:
	CSendProp( edict_t* edict, const char* prop_name );

	SendPropType	get_prop_type();

	void			set_prop_int( int value );
	void			set_prop_float( float value );

	int				get_prop_int();
	float			get_prop_float();

private:
	// Offset from the beginning of the network table that
	// this prop is located at.
	unsigned int	m_prop_offset;

	// Base entity instance.
	CBaseEntity*	m_base_entity;

	// The actual send prop object.
	SendProp*		m_send_prop;
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

//---------------------------------------------------------------------------------
// IServerEntity wrapper class.
//---------------------------------------------------------------------------------
class CServerEntity
{
public:
	CServerEntity( IServerEntity* server_entity );

	virtual int			get_model_index() const;
	virtual void		set_model_index( int index );
	virtual const char* get_model_name();

private:
	IServerEntity* m_server_entity;
};

#endif