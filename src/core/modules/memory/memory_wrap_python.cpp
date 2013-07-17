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

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "modules/export_main.h"
#include "memory_scanner.h"
#include "memory_tools.h"
#include "dyncall.h"


void export_binaryfile();
void export_memtools();
void export_dyncall();

//-----------------------------------------------------------------------------
// Exposes the memory_c module.
//-----------------------------------------------------------------------------
DECLARE_SP_MODULE(memory_c)
{
    export_binaryfile();
    export_memtools();
    export_dyncall();
}

//-----------------------------------------------------------------------------
// Exposes CBinaryFile
//-----------------------------------------------------------------------------
void export_binaryfile()
{
    BOOST_ABSTRACT_CLASS(CBinaryFile)

        // Class methods
        CLASS_METHOD(CBinaryFile,
            find_signature,
            "Returns the address of a signature found in memory.",
            args("szSignature", "iLength"),
            manage_new_object_policy()
        )

        CLASS_METHOD(CBinaryFile,
            find_symbol,
            "Returns the address of a symbol found in memory.",
            args("szSymbol"),
            manage_new_object_policy()
        )

        CLASS_METHOD(CBinaryFile,
            find_pointer,
            "Rips out a pointer from a function.",
            args("szSignature", "iLength", "iOffset"),
            manage_new_object_policy()
        )

        // Special methods
        CLASS_METHOD_SPECIAL(CBinaryFile,
            "__getattr__",
            find_symbol,
            "Returns the address of a symbol found in memory.",
            args("szSymbol"),
            manage_new_object_policy()
        )

        CLASS_METHOD_SPECIAL(CBinaryFile,
            "__getitem__",
            find_symbol,
            "Returns the address of a symbol found in memory.",
            args("szSymbol"),
            manage_new_object_policy()
        )

        // Properties
        CLASS_PROPERTY_READ_ONLY(CBinaryFile,
            "addr",
            get_address,
            "Returns the base address of this binary."
        )

        CLASS_PROPERTY_READ_ONLY(CBinaryFile,
            "size",
            get_size,
            "Returns the size of this binary."
        )

    BOOST_END_CLASS()

    BOOST_FUNCTION(find_binary,
        "Returns a CBinaryFile object or NULL.",
        args("szPath"),
        reference_existing_object_policy()
    );
}


//-----------------------------------------------------------------------------
// Exposes CPointer
//-----------------------------------------------------------------------------
// Overloads
DECLARE_CLASS_METHOD_OVERLOAD(CPointer, get_ptr, 0, 1);
DECLARE_CLASS_METHOD_OVERLOAD(CPointer, get_virtual_func, 1, 2);

// get_<type> methods
DECLARE_CLASS_METHOD_OVERLOAD(CPointer, get_string, 0, 2);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(get_bool_overload, CPointer::get<bool>, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(get_char_overload, CPointer::get<char>, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(get_double_overload, CPointer::get<double>, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(get_float_overload, CPointer::get<float>, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(get_int_overload, CPointer::get<int>, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(get_long_overload, CPointer::get<long>, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(get_long_long_overload, CPointer::get<long long>, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(get_short_overload, CPointer::get<short>, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(get_unsigned_long_overload, CPointer::get<unsigned long>, 0, 1)

// set_<type> methods
DECLARE_CLASS_METHOD_OVERLOAD(CPointer, set_string, 1, 3);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_bool_overload, CPointer::set<bool>, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_char_overload, CPointer::set<char>, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_double_overload, CPointer::set<double>, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_float_overload, CPointer::set<float>, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_int_overload, CPointer::set<int>, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_long_overload, CPointer::set<long>, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_long_long_overload, CPointer::set<long long>, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_short_overload, CPointer::set<short>, 1, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(set_unsigned_long_overload, CPointer::set<unsigned long>, 1, 2)

void export_memtools()
{
    BOOST_CLASS_CONSTRUCTOR(CPointer, optional<unsigned long>)

        // Class methods
        CLASS_METHOD_OVERLOAD_RET(CPointer, 
            get_ptr,
            "Returns the value at the given memory location as a CPointer instance.",
            args("iOffset"),
            manage_new_object_policy()
        )

        CLASS_METHOD_OVERLOAD_RET(CPointer, 
            get_virtual_func,
            "Returns the address (as a CPointer instance) of a virtual function at the given index.",
            args("iIndex", "bPlatformCheck"),
            manage_new_object_policy()
        )
        
        CLASS_METHOD(CPointer,
            alloc,
            "Allocates a memory block.",
            args("iSize")
        )

        CLASS_METHOD(CPointer,
            realloc,
            "Reallocates a memory block.",
            args("iSize")
        )

        CLASS_METHOD(CPointer,
            dealloc,
            "Deallocates a memory block."
        )

        CLASS_METHOD(CPointer,
            call,
            "",
            args("iConvention", "szParams", "args")
        )
        
        // get_<type> methods
        CLASS_METHOD_OVERLOAD(CPointer,
            get_string,
            "Returns the value at the given memory location as a string.",
            args("iOffset", "bIsPtr")
         )

        .def("get_bool",
            &CPointer::get<bool>,
            get_bool_overload(
                args("iOffset"),
                "Returns the value at the given memory location as a boolean.")
        )
        
        .def("get_char",
            &CPointer::get<char>,
            get_char_overload(
                args("iOffset"),
                "Returns the value at the given memory location as a char.")
        )
        
        .def("get_double",
            &CPointer::get<double>,
            get_double_overload(
                args("iOffset"),
                "Returns the value at the given memory location as a double.")
        )
        
        .def("get_float",
            &CPointer::get<float>,
            get_float_overload(
                args("iOffset"),
                "Returns the value at the given memory location as a float.")
        )
        
        .def("get_int",
            &CPointer::get<int>,
            get_int_overload(
                args("iOffset"),
                "Returns the value at the given memory location as an integer.")
        )
        
        .def("get_long",
            &CPointer::get<long>,
            get_long_overload(
                args("iOffset"),
                "Returns the value at the given memory location as a long.")
        )
        
        .def("get_long_long",
            &CPointer::get<long long>,
            get_long_long_overload(
                args("iOffset"),
                "Returns the value at the given memory location as a long long.")
        )
        
        .def("get_short",
            &CPointer::get<short>,
            get_short_overload(
                args("iOffset"),
                "Returns the value at the given memory location as a short.")
        )
        
        .def("get_unsigned_long",
            &CPointer::get<unsigned long>,
            get_unsigned_long_overload(
                args("iOffset"),
                "Returns the value at the given memory location as a unsigned long.")
        )

        // set_<type> methods
        CLASS_METHOD_OVERLOAD(CPointer,
            set_string,
            "",
            args("szText", "iSize", "iOffset")
         )

        .def("set_bool",
            &CPointer::set<bool>,
            set_bool_overload(
                args("value", "iOffset"),
                "Sets the value at the given memory location as a boolean.")
        )

        .def("set_char",
            &CPointer::set<char>,
            set_char_overload(
                args("value", "iOffset"),
                "Sets the value at the given memory location as a char.")
        )
        
        .def("set_double",
            &CPointer::set<double>,
            set_double_overload(
                args("value", "iOffset"),
                "Sets the value at the given memory location as a double.")
        )
        
        .def("set_float",
            &CPointer::set<float>,
            set_float_overload(
                args("value", "iOffset"),
                "Sets the value at the given memory location as a float.")
        )
        
        .def("set_int",
            &CPointer::set<int>,
            set_int_overload(
                args("value", "iOffset"),
                "Sets the value at the given memory location as an integer.")
        )
        
        .def("set_long",
            &CPointer::set<long>,
            set_long_overload(
                args("value", "iOffset"),
                "Sets the value at the given memory location as a long.")
        )
        
        .def("set_long_long",
            &CPointer::set<long long>,
            set_long_long_overload(
                args("value", "iOffset"),
                "Sets the value at the given memory location as a long long.")
        )
        
        .def("set_short",
            &CPointer::set<short>,
            set_short_overload(
                args("value", "iOffset"),
                "Sets the value at the given memory location as a short.")
        )
        
        .def("set_unsigned_long",
            &CPointer::set<unsigned long>,
            set_unsigned_long_overload(
                args("value", "iOffset"),
                "Sets the value at the given memory location as a unsigned long.")
        )

        // Special methods
        CLASS_METHOD_SPECIAL(CPointer, 
			"__int__",
			get_address,
			"Returns the address of this memory block."
		)

        CLASS_METHOD_SPECIAL(CPointer, 
			"__bool__",
			is_valid,
			"Returns True if the address is not NULL."
		)

        CLASS_METHOD_SPECIAL(CPointer, 
			"__add__",
			add,
			"Adds a value to the base address.",
            reference_existing_object_policy()
		)

        CLASS_METHOD_SPECIAL(CPointer, 
			"__radd__",
			add,
			"Adds a value to the base address.",
            reference_existing_object_policy()
		)

        CLASS_METHOD_SPECIAL(CPointer, 
			"__sub__",
			add,
			"Subtracts a value from the base address.",
            reference_existing_object_policy()
		)

        CLASS_METHOD_SPECIAL(CPointer, 
			"__rsub__",
			add,
			"Subtracts a value from the base address.",
            reference_existing_object_policy()
		)

        // Properties
        CLASS_PROPERTY_READ_ONLY(CPointer,
            "addr",
            get_address,
            "Returns the address of this memory block."
        )

        CLASS_PROPERTY_READ_ONLY(CPointer,
            "size",
            get_size,
            "Returns the size of this memory block."
        )

    BOOST_END_CLASS()
}

//-----------------------------------------------------------------------------
// Exposes DynCall
//-----------------------------------------------------------------------------
void export_dyncall()
{
    // Calling conventions.
    BOOST_GLOBAL_ATTRIBUTE("DC_CDECL",    DC_CALL_C_DEFAULT);
    BOOST_GLOBAL_ATTRIBUTE("DC_ELLIPSIS", DC_CALL_C_ELLIPSIS);
    BOOST_GLOBAL_ATTRIBUTE("DC_VARARGS",  DC_CALL_C_ELLIPSIS_VARARGS);

#ifdef _WIN32
    BOOST_GLOBAL_ATTRIBUTE("DC_STDCALL",  DC_CALL_C_X86_WIN32_STD);
    BOOST_GLOBAL_ATTRIBUTE("DC_FASTCALL", DC_CALL_C_X86_WIN32_FAST_MS);
    BOOST_GLOBAL_ATTRIBUTE("DC_THISCALL", DC_CALL_C_X86_WIN32_THIS_MS);

#elif defined(__linux__)
    BOOST_GLOBAL_ATTRIBUTE("DC_FASTCALL", DC_CALL_C_X86_WIN32_FAST_GNU);
    BOOST_GLOBAL_ATTRIBUTE("DC_THISCALL", DC_CALL_C_X86_WIN32_THIS_GNU);
#endif

    // Other constants that are very useful.
    BOOST_GLOBAL_ATTRIBUTE("DC_ERROR_NONE",             DC_ERROR_NONE);
    BOOST_GLOBAL_ATTRIBUTE("DC_ERROR_UNSUPPORTED_MODE", DC_ERROR_UNSUPPORTED_MODE);
    BOOST_GLOBAL_ATTRIBUTE("DEFAULT_ALIGNMENT",         DEFAULT_ALIGNMENT);
}