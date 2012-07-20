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
#include "boost/python.hpp"
#include "export_main.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"
#include "utility/mrecipientfilter.h"
#include "eiface.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// Usermsg module.
//---------------------------------------------------------------------------------
DECLARE_SP_MODULE(Shared)
{
	// ----------------------------------------------------------
	// Wrap the recipient filter class which is used for
	// usermessages as well as effects.
	// ----------------------------------------------------------
	BOOST_ABSTRACT_CLASS(IRecipientFilter)
		CLASS_METHOD(IRecipientFilter, IsReliable)
		CLASS_METHOD(IRecipientFilter, IsInitMessage)
		CLASS_METHOD(IRecipientFilter, GetRecipientCount)
		CLASS_METHOD(IRecipientFilter, GetRecipientIndex)
	BOOST_END_CLASS()

	BOOST_INHERITED_CLASS_NOCOPY(MRecipientFilter, IRecipientFilter)
		CLASS_METHOD(MRecipientFilter, AddAllPlayers)
		CLASS_METHOD(MRecipientFilter, AddRecipient)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// The bf_write class has a method that is overloaded.
	// ----------------------------------------------------------
	typedef bool (bf_write::*bf_write_fn)(const char*);
	bf_write_fn fnWriteString = &bf_write::WriteString;

	// ----------------------------------------------------------
	// TODO: Figure out if we need to instantiate this..
	// YNHNOTE: I don't think we do but I'll allow it for now.
	// ----------------------------------------------------------
	BOOST_CLASS_NOCOPY(bf_write)
		CLASS_METHOD(bf_write, GetDebugName)
		CLASS_METHOD(bf_write, WriteOneBit)
		CLASS_METHOD(bf_write, WriteOneBitAt)
		CLASS_METHOD(bf_write, WriteUBitLong)
		CLASS_METHOD(bf_write, WriteUBitVar)
		CLASS_METHOD(bf_write, WriteBitAngle)
		CLASS_METHOD(bf_write, WriteBitCoord)
		CLASS_METHOD(bf_write, WriteBitFloat)
		CLASS_METHOD(bf_write, WriteBitVec3Coord)
		CLASS_METHOD(bf_write, WriteBitNormal)
		CLASS_METHOD(bf_write, WriteBitVec3Normal)

		CLASS_METHOD(bf_write, WriteChar)
		CLASS_METHOD(bf_write, WriteByte)
		CLASS_METHOD(bf_write, WriteShort)
		CLASS_METHOD(bf_write, WriteWord)
		CLASS_METHOD(bf_write, WriteLong)
		CLASS_METHOD(bf_write, WriteFloat)

		CLASS_METHOD_TYPEDEF(WriteString, fnWriteString)
	BOOST_END_CLASS()
}