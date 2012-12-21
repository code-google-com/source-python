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
#include "../export_main.h"
#include "core/sp_python.h"
#include "utility/wrap_macros.h"

//---------------------------------------------------------------------------------
// Namespaces to use.
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// Allocates a memory block.
//---------------------------------------------------------------------------------
unsigned long AllocateMemory( size_t size )
{
	return (unsigned long)malloc(size);
}

//---------------------------------------------------------------------------------
// Deallocate a memory block.
//---------------------------------------------------------------------------------
void DeallocatePointer( unsigned long ptr )
{
	free((void *)ptr);
}

//---------------------------------------------------------------------------------
// Returns the address of a vtable function.
//---------------------------------------------------------------------------------
unsigned long FindVirtualFunction( unsigned long pThisPointer, int iOffset, bool bSkipPlatformCheck = false )
{
#ifdef __linux__
	if (!bSkipPlatformCheck)
	{
		iOffset ++;
	}
#endif
	return (unsigned long)((void *)((void **)*(void ***)pThisPointer)[iOffset]);
}

//---------------------------------------------------------------------------------
// Returns the value at the given memory location.
//---------------------------------------------------------------------------------
template<class T>
T GetLocVal( unsigned long ptr )
{
	return *(T *)((char *)ptr);
}

//---------------------------------------------------------------------------------
// Sets the given value at the given memory location.
//---------------------------------------------------------------------------------
template<class T>
void SetLocVal( unsigned long ptr, T value )
{
	*(T *)((char *)ptr) = value;
}

//---------------------------------------------------------------------------------
// Reallocates a memory block.
//---------------------------------------------------------------------------------
unsigned long ReallocatePointer( unsigned long ptr, size_t size )
{
	return (unsigned long)realloc((void *)ptr, size);
}

//---------------------------------------------------------------------------------
// Overloads.
//---------------------------------------------------------------------------------
BOOST_PYTHON_FUNCTION_OVERLOADS(FindVirtualFunction_Overloads,
	FindVirtualFunction, 2, 3);

//---------------------------------------------------------------------------------
// Wrappers.
//---------------------------------------------------------------------------------
void Export_MemoryTools( void )
{
	BOOST_FUNCTION(AllocateMemory,
		args("size"),
		"Allocates a memory block and returns its pointer."
	);
	
	BOOST_FUNCTION(DeallocatePointer,
		args("ptr"),
		"Deallocates a memory block."
	);
	
	def("FindVirtualFunction",
		FindVirtualFunction,
		FindVirtualFunction_Overloads(
			args("pThisPointer", "iOffset", "bSkipPlatformCheck"),
			"Returns the address of a vtable function."
		)
	);
	
	// GetLocVal...
	def("GetLocBool", &GetLocVal<bool>, args("ptr"), "Returns the value at the given memory location as a boolean.");
	def("GetLocChar", &GetLocVal<char>, args("ptr"), "Returns the value at the given memory location as a character.");
	def("GetLocDouble", &GetLocVal<double>, args("ptr"), "Returns the value at the given memory location as a double.");
	def("GetLocFloat", &GetLocVal<float>, args("ptr"), "Returns the value at the given memory location as a float.");
	def("GetLocInt", &GetLocVal<int>, args("ptr"), "Returns the value at the given memory location as an integer.");
	def("GetLocLong", &GetLocVal<long>, args("ptr"), "Returns the value at the given memory location as a long.");
	def("GetLocLongLong", &GetLocVal<long long>, args("ptr"), "Returns the value at the given memory location as a long long.");
	def("GetLocPointer", &GetLocVal<unsigned long>, args("ptr"), "Returns the value at the given memory location as a pointer.");
	def("GetLocShort", &GetLocVal<short>, args("ptr"), "Returns the value at the given memory location as a short.");
	
	// SetLocVal...
	def("SetLocBool", &SetLocVal<bool>, args("ptr", "value"), "Sets the given value at the given memory location as a boolean.");
	def("SetLocChar", &SetLocVal<char>, args("ptr", "value"), "Sets the given value at the given memory location as a character.");
	def("SetLocDouble", &SetLocVal<double>, args("ptr", "value"), "Sets the given value at the given memory location as a double.");
	def("SetLocFloat", &SetLocVal<float>, args("ptr", "value"), "Sets the given value at the given memory location as a float.");
	def("SetLocInt", &SetLocVal<int>, args("ptr", "value"), "Sets the given value at the given memory location as an integer.");
	def("SetLocLongLong", &SetLocVal<long long>, args("ptr", "value"), "Sets the given value at the given memory location as a long long.");
	def("SetLocLong", &SetLocVal<long>, args("ptr", "value"), "Sets the given value at the given memory location as a long.");
	def("SetLocPointer", &SetLocVal<unsigned long>, args("ptr", "value"), "Sets the given value at the given memory location as a pointer.");
	def("SetLocShort", &SetLocVal<short>, args("ptr", "value"), "Sets the given value at the given memory location as a short.");
	
	BOOST_FUNCTION(ReallocatePointer,
		args("ptr", "size"),
		"Reallocates a memory block."
	);
}