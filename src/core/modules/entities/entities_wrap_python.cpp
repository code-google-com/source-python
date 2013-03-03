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
#include "entities_wrap.h"
#include "modules/export_main.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// Exposer functions.
//---------------------------------------------------------------------------------
void export_base_entity_handle();
void export_handle_entity();
void export_server_unknown();
void export_server_entity();
void export_edict();

//---------------------------------------------------------------------------------
// Entity module definition.
//---------------------------------------------------------------------------------
DECLARE_SP_MODULE(entity_c)
{
	export_base_entity_handle();
	export_handle_entity();
	export_server_unknown();
	export_server_entity();
	export_edict();
}

//---------------------------------------------------------------------------------
// Exports CBaseEntityHandle.
//---------------------------------------------------------------------------------
void export_base_entity_handle()
{
	BOOST_CLASS_CONSTRUCTOR(CBaseEntityHandle, int)
		
		CLASS_CONSTRUCTOR(CBaseHandle)

		CLASS_METHOD(CBaseEntityHandle,
			is_valid,
		)

		CLASS_METHOD(CBaseEntityHandle,
			get_entry_index
		)

		CLASS_METHOD(CBaseEntityHandle,
			get_serial_number
		)

		CLASS_METHOD(CBaseEntityHandle,
			to_int
		)

	BOOST_END_CLASS()
}

//---------------------------------------------------------------------------------
// Exports CHandleEntity
//---------------------------------------------------------------------------------
void export_handle_entity()
{
	BOOST_ABSTRACT_CLASS(CHandleEntity)
		
		CLASS_METHOD(CHandleEntity,
			get_ref_ehandle,
			manage_new_object_policy()
		)

	BOOST_END_CLASS()
}
void export_server_unknown()
{

}
void export_server_entity()
{

}
void export_edict()
{
	BOOST_CLASS_CONSTRUCTOR(CEdict, int)

		CLASS_METHOD(CEdict,
			area_num
		)

		CLASS_METHOD(CEdict,
			get_class_name,
			"Returns a string containing the class name of this entity."
		)

		CLASS_METHOD(CEdict,
			is_free,
			"Returns True if the edict instance is occupied by a valid entity."
		)

		CLASS_METHOD(CEdict,
			set_free,
			"Sets the entity as free (not-valid)."
		)

		CLASS_METHOD(CEdict,
			clear_free,
			"Clears the entity free flag."
		)	

	BOOST_END_CLASS()
}