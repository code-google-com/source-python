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
DECLARE_CLASS_METHOD_OVERLOAD(Quaternion, Init, 0, 4)
DECLARE_CLASS_METHOD_OVERLOAD(RadianEuler, Init, 0, 3)
DECLARE_CLASS_METHOD_OVERLOAD(QAngle, Init, 0, 3)

//---------------------------------------------------------------------------------
// Helper template methods for __getitem__ and __setitem__
//---------------------------------------------------------------------------------
template<class T, class U>
U GetItemIndexer(const T* self, const int i)
{
	return (*self)[i];
}

template<class T, class U>
void SetItemIndexer(T* self, const int i, const U& value)
{
	(*self)[i] = value;
}

//---------------------------------------------------------------------------------
// Usermsg module.
//---------------------------------------------------------------------------------
DECLARE_SP_MODULE(Shared)
{
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

		CLASS_METHOD_OVERLOAD(Vector, 
			IsZero,
			"Returns true if this vector is (0,0,0) within tolerance",
			args("tolerance")
		)
		


		CLASS_METHOD(Vector,
			NormalizeInPlace,
			"Normalizes the vector"
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


#if( SOURCE_ENGINE >= 2 )
		CLASS_METHOD(Vector,
			LengthRecipFast,
			"Get one over the vector's length via fast hardware approximation"
		)

		CLASS_METHOD(Vector,
			IsZeroFast,
			"Returns true if this vector is exactly (0,0,0) -- only fast if vector is coming from memory, not registers"
		)

		CLASS_METHOD(Vector,
			Normalized,
			"Returns a normalized vector based on this object."
		)
#endif

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
		.def("__getitem__", &GetItemIndexer<Vector, vec_t>, "Returns the vector element at the given index.", args("i"))
		.def("__setitem__", &SetItemIndexer<Vector, vec_t>, "Sets the vector element at the given index.", args("i", "value"))

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

	BOOST_CLASS(cplane_t)
		CLASS_MEMBER(cplane_t,
			normal,
			"The normal to the plane."
		)
		CLASS_MEMBER(cplane_t,
			dist,
			"The distance of the plane."
		)
		CLASS_MEMBER(cplane_t,
			type,
			"The type of the plane."
		)
		CLASS_MEMBER(cplane_t,
			signbits,
			"The sign bits of the plane."
		)
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Exposes Quaternion class.
	// ----------------------------------------------------------
	BOOST_CLASS(Quaternion)		
		// ----------------------------------------------------------
		// Constructors
		// ----------------------------------------------------------
		CLASS_CONSTRUCTOR(vec_t, vec_t, vec_t, vec_t)
		CLASS_CONSTRUCTOR(RadianEuler const&)

        // ----------------------------------------------------------
        // Class Methods
        // ----------------------------------------------------------
		CLASS_METHOD_OVERLOAD(Quaternion,
			Init,
			"Quaternion initialization",
			args("ix", "iy", "iz", "iw")
		)

		CLASS_METHOD(Quaternion,
			IsValid,
			"Returns true if the Quaternion is not equal to NaN"
		)

		CLASS_METHOD(Quaternion,
			Invalidate,
			"Invalidates a Quaternion."
		)

		// ----------------------------------------------------------
		// Class operators
		// ----------------------------------------------------------
		.def(self == self)
		.def(self != self)
		.def("__getitem__", &GetItemIndexer<Quaternion, vec_t>, "Returns the Quaternion element at the given index.", args("i"))
		.def("__setitem__", &SetItemIndexer<Quaternion, vec_t>, "Sets the Quaternion element at the given index.", args("i", "value"))

        // ----------------------------------------------------------
        // Class Attributes
        // ----------------------------------------------------------
        CLASS_MEMBER(Quaternion,
            x,
            "Read/write value of the x member for the Quaternion."
        )

        CLASS_MEMBER(Quaternion,
            y,
            "Read/write value of the y member for the Quaternion."
        )

        CLASS_MEMBER(Quaternion,
            z,
            "Read/write value of the z member for the Quaternion."
        )

        CLASS_MEMBER(Quaternion,
            w,
            "Read/write value of the z member for the Quaternion."
        )
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Exposes RadianEuler class.
	// ----------------------------------------------------------
	typedef vec_t (RadianEuler::*RadianEulerIndexerFn)(int) const;
	RadianEulerIndexerFn fnRadianEulerIndexer = &RadianEuler::operator[];

	BOOST_CLASS(RadianEuler)		
		// ----------------------------------------------------------
		// Constructors
		// ----------------------------------------------------------
		CLASS_CONSTRUCTOR(vec_t, vec_t, vec_t)
		CLASS_CONSTRUCTOR(Quaternion const&)
		CLASS_CONSTRUCTOR(QAngle const&)

        // ----------------------------------------------------------
        // Class Methods
        // ----------------------------------------------------------
		CLASS_METHOD_OVERLOAD(RadianEuler,
			Init,
			"RadianEuler initialization",
			args("ix", "iy", "iz")
		)

		CLASS_METHOD(RadianEuler,
			ToQAngle,
			"Returns a QAngle representation of this RadianEuler."
		)

		CLASS_METHOD(RadianEuler,
			IsValid,
			"Returns true if the RadianEuler is not equal to NaN"
		)

		CLASS_METHOD(RadianEuler,
			Invalidate,
			"Invalidates a RadianEuler."
		)

		// ----------------------------------------------------------
		// Class operators
		// ----------------------------------------------------------
		.def("__getitem__", &GetItemIndexer<RadianEuler, vec_t>, "Returns the RadianEuler element at the given index.", args("i"))
		.def("__setitem__", &SetItemIndexer<RadianEuler, vec_t>, "Sets the RadianEuler element at the given index.", args("i", "value"))

        // ----------------------------------------------------------
        // Class Attributes
        // ----------------------------------------------------------
        CLASS_MEMBER(RadianEuler,
            x,
            "Read/write value of the x member for the Quaternion."
        )

        CLASS_MEMBER(RadianEuler,
            y,
            "Read/write value of the y member for the Quaternion."
        )

        CLASS_MEMBER(RadianEuler,
            z,
            "Read/write value of the z member for the Quaternion."
        )
	BOOST_END_CLASS()

	// ----------------------------------------------------------
	// Exposes QAngle class.
	// ----------------------------------------------------------
	typedef vec_t (QAngle::*QAngleIndexerFn)(int) const;
	QAngleIndexerFn fnQAngleIndexer = &QAngle::operator[];

	BOOST_CLASS(QAngle)		
		// ----------------------------------------------------------
		// Constructors
		// ----------------------------------------------------------
		CLASS_CONSTRUCTOR(vec_t, vec_t, vec_t)

        // ----------------------------------------------------------
        // Class Methods
        // ----------------------------------------------------------
		CLASS_METHOD_OVERLOAD(QAngle,
			Init,
			"QAngle initialization",
			args("ix", "iy", "iz")
		)

		CLASS_METHOD(QAngle, 
			Random,
			"QAngle initialization with random values",
			args("minVal", "maxVal")
		)

		CLASS_METHOD(QAngle,
			IsValid,
			"Returns true if the QAngle is not equal to NaN"
		)

		CLASS_METHOD(QAngle,
			Invalidate,
			"Invalidates a QAngle."
		)

		CLASS_METHOD(QAngle,
			Length,
			"Returns the length of the QAngle's magnitude."
		)

		CLASS_METHOD(QAngle,
			LengthSqr,
			"Returns the length of the QAngle's magnitude squared."
		)

		// ----------------------------------------------------------
		// Class operators
		// ----------------------------------------------------------
		.def(self == self)
		.def(self != self)

		.def(self += self)
		.def(self -= self)

		.def(self *= float())
		.def(self /= float())

		.def("__getitem__", &GetItemIndexer<QAngle, vec_t>, "Returns the QAngle element at the given index.", args("i"))
		.def("__setitem__", &SetItemIndexer<QAngle, vec_t>, "Sets the QAngle element at the given index.", args("i", "value"))

        // ----------------------------------------------------------
        // Class Attributes
        // ----------------------------------------------------------
        CLASS_MEMBER(QAngle,
            x,
            "Read/write value of the x coordinate for the QAngle."
        )

        CLASS_MEMBER(QAngle,
            y,
            "Read/write value of the y coordinate for the QAngle."
        )

        CLASS_MEMBER(QAngle,
            z,
            "Read/write value of the z coordinate for the QAngle."
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
