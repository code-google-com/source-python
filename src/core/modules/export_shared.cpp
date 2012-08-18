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
#include "irecipientfilter.h"
#include "utility/mrecipientfilter.h"
#include "eiface.h"
#include "Color.h"
#include "mathlib/vector.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// Class method overloads
//---------------------------------------------------------------------------------
DECLARE_CLASS_METHOD_OVERLOAD(Vector, IsZero, 0, 1)

//---------------------------------------------------------------------------------
// Usermsg module.
//---------------------------------------------------------------------------------
DECLARE_SP_MODULE(Shared)
{
	// ----------------------------------------------------------
	// Simple structs.
	// ----------------------------------------------------------
	BOOST_CLASS(Vector)
		
		// ----------------------------------------------------------
		// Constructors
		// ----------------------------------------------------------
		CLASS_CONSTRUCTOR(vec_t, vec_t, vec_t)

        // ----------------------------------------------------------
        // Class Methods
        // ----------------------------------------------------------
		CLASS_METHOD(Vector,
			Init,
			"Vector initialization",
			args("ix", "iy", "iz")
		)

		CLASS_METHOD(Vector,
			IsValid,
			"Returns true if the vector is not equal to NaN"
		)

		CLASS_METHOD(Vector,
			Zero,
			"Zeros out a vector."
		)

		CLASS_METHOD(Vector,
			Negate,
			"Negates a vector's components."
		)

		CLASS_METHOD(Vector,
			Length,
			"Returns the magnitude of the vector"
		)

		CLASS_METHOD(Vector,
			LengthSqr,
			"Returns the vector's magnitude squared."
		)

		CLASS_METHOD(Vector,
			LengthRecipFast,
			"Get one over the vector's length via fast hardware approximation"
		)

		CLASS_METHOD_OVERLOAD(Vector, 
			IsZero,
			"Returns true if this vector is (0,0,0) within tolerance",
			args("tolerance")
		)
		
		CLASS_METHOD(Vector,
			IsZeroFast,
			"Returns true if this vector is exactly (0,0,0) -- only fast if vector is coming from memory, not registers"
		)

		CLASS_METHOD(Vector,
			NormalizeInPlace,
			"Normalizes the vector"
		)

		CLASS_METHOD(Vector,
			Normalized,
			"Returns a normalized vector based on this object."
		)

		CLASS_METHOD(Vector,
			IsLengthGreaterThan,
			"Returns true if length() is greater than val",
			args("val")
		)

		CLASS_METHOD(Vector,
			IsLengthLessThan,
			"Returns true if length() is less than val",
			args("val")
		)

		CLASS_METHOD(Vector,
			WithinAABox,
			"Returns true if the vector is within the box defined by two other vectors",
			args("boxmin", "boxmax")
		)

		CLASS_METHOD(Vector,
			DistTo,
			"Returns the distance from one Vector to the class Vector",
			args("vOther")
		)

		CLASS_METHOD(Vector,
			DistToSqr,
			"Gets the distance from this vector to the other one squared",
			args("vOther")
		)

		CLASS_METHOD(Vector,
			MulAdd,
			"Multiply, add, and assign to this vector (this = a + b * scalar).",
			args("a", "b", "scalar")
		)

		CLASS_METHOD(Vector,
			Dot,
			"Does the dot product of this vector",
			args("vOther")
		)

		CLASS_METHOD(Vector,
			Length2D,
			"Returns the length of the vector in 2D space"
		)

		CLASS_METHOD(Vector,
			Length2DSqr,
			"Returns the length of the vector in 2D space squared."
		)

		// ----------------------------------------------------------
		// Class operators
		// ----------------------------------------------------------
		.def(self == self)
		.def(self != self)

		.def(self += self)
		.def(self -= self)

		.def(self *= self)
		.def(self *= float())

		.def(self /= self)
		.def(self /= float())

		.def(self += float())
		.def(self -= float())

		.def(self + self)
		.def(self - self)
		.def(self * self)
		.def(self / self)
		.def(self * float())
		.def(self / float())

        // ----------------------------------------------------------
        // Class Attributes
        // ----------------------------------------------------------
        CLASS_MEMBER(Vector,
            x,
            "Read/write value of the x coordinate for the vector."
        )

        CLASS_MEMBER(Vector,
            y,
            "Read/write value of the y coordinate for the vector."
        )

        CLASS_MEMBER(Vector,
            z,
            "Read/write value of the z coordinate for the vector."
        )

	BOOST_END_CLASS()

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
