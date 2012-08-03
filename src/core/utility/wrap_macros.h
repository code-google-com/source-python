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
#ifndef _WRAP_MACROS_H
#define _WRAP_MACROS_H

//---------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------
#include "boost/python.hpp"

//---------------------------------------------------------------------------------
// Namespaces
//---------------------------------------------------------------------------------
using namespace boost::python;

//---------------------------------------------------------------------------------
// Surround boost python statements with this macro in order to handle exceptions.
//---------------------------------------------------------------------------------
#define BEGIN_BOOST_PY() \
	try {

#define END_BOOST_PY( ... ) \
	} catch( ... ) { \
		PyErr_Print(); \
		PyErr_Clear(); \
		return __VA_ARGS__; \
	}

#define END_BOOST_PY_NORET( ... ) \
	} catch( ... ) { \
		PyErr_Print(); \
		PyErr_Clear(); \
	}

//---------------------------------------------------------------------------------
// This macro will turn input into a string.
//---------------------------------------------------------------------------------
#define XSTRINGIFY(s) STRINGIFY(s)
#define STRINGIFY(s) #s

//---------------------------------------------------------------------------------
// Use this to begin wrapping an abstract class.
//---------------------------------------------------------------------------------
#define BOOST_ABSTRACT_CLASS( classname ) \
	class_<classname, boost::noncopyable>(XSTRINGIFY(classname), no_init)

//---------------------------------------------------------------------------------
// Use this to begin wrapping an abstract class that inherits.
//---------------------------------------------------------------------------------
#define BOOST_ABSTRACT_CLASS_INHERITED( classname, baseclass ) \
	class_<classname, bases<baseclass>, boost::noncopyable>(XSTRINGIFY(classname), no_init)

//---------------------------------------------------------------------------------
// Use this to wrap a class that inherits a base class.
//---------------------------------------------------------------------------------
#define BOOST_INHERITED_CLASS( classname, baseclass ) \
	class_<classname, bases<baseclass> >(XSTRINGIFY(classname))

//---------------------------------------------------------------------------------
// Use this to wrap an inherited class that shouldn't be copied.
//---------------------------------------------------------------------------------
#define BOOST_INHERITED_CLASS_NOCOPY( classname, baseclass, ... ) \
	class_<classname, bases<baseclass>, boost::noncopyable>(XSTRINGIFY(classname), ##__VA_ARGS__)

//---------------------------------------------------------------------------------
// Use this to wrap a regular class.
//---------------------------------------------------------------------------------
#define BOOST_CLASS( classname ) \
	class_<classname>(XSTRINGIFY(classname))

//---------------------------------------------------------------------------------
// Use this to add a constructor.
//---------------------------------------------------------------------------------
#define BOOST_CLASS_CONSTRUCTOR( ... ) \
	.def(init< ##__VA_ARGS__ >())

//---------------------------------------------------------------------------------
// Use this to wrap a class that should be instantiatable from python, but
// should never be copied.
//---------------------------------------------------------------------------------
#define BOOST_CLASS_NOCOPY( classname ) \
	class_<classname, boost::noncopyable>(XSTRINGIFY(classname))

//---------------------------------------------------------------------------------
// Use this to add a constructor to a class.
//---------------------------------------------------------------------------------
#define CLASS_CONSTRUCTOR( ... ) \
	.def(init< ##__VA_ARGS__ >())

//---------------------------------------------------------------------------------
// This finishes off a boost -> python object wrapping.
//---------------------------------------------------------------------------------
#define BOOST_END_CLASS() \
	;
	
//---------------------------------------------------------------------------------
// Use this to wrap a method. Variable arg is for any return value policies
// you might have. Since we're in the namespace, we have access to the class.
//---------------------------------------------------------------------------------
#define CLASS_METHOD( classname, methodname, ... ) \
	.def(XSTRINGIFY(methodname), &classname::methodname, ##__VA_ARGS__)

//---------------------------------------------------------------------------------
// Use this macro to bind class functions to "special" functions in python such
// as __eq__ or __len__.
//---------------------------------------------------------------------------------
#define CLASS_METHOD_SPECIAL( classname, pymethod, methodname, ... ) \
	.def(pymethod, &classname::methodname, ##__VA_ARGS__)

//---------------------------------------------------------------------------------
// Use this for class methods that you've had to typedef out (because they were
// overloaded etc etc).
//---------------------------------------------------------------------------------
#define CLASS_METHOD_TYPEDEF( methodname, function, ... ) \
	.def(XSTRINGIFY(methodname), function, ##__VA_ARGS__)

//---------------------------------------------------------------------------------
// Use this to wrap a writable class member.
//---------------------------------------------------------------------------------
#define CLASS_MEMBER( classname, varname, ... ) \
	.def_readwrite(XSTRINGIFY(varname), &classname::varname, ##__VA_ARGS__)

//---------------------------------------------------------------------------------
// Use this to wrap a method that returns an interface.
//---------------------------------------------------------------------------------
#define BOOST_FUNCTION( function, ... ) \
	def(XSTRINGIFY(function), &function, ##__VA_ARGS__)

//---------------------------------------------------------------------------------
// Use this macro to generate function overloads for classes that have methods 
// with default parameters.
//---------------------------------------------------------------------------------
#define DECLARE_CLASS_METHOD_OVERLOAD( classname, method, minargs, maxargs ) \
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(classname##_##method, method, minargs, maxargs)

//---------------------------------------------------------------------------------
// Use this macro inside a BOOST_*_CLASS block to create a class method with an
// overload. Make sure you have DECLARE_CLASS_METHOD_OVERLOAD'd the overload
// first!
//---------------------------------------------------------------------------------
#define CLASS_METHOD_OVERLOAD( classname, methodname, ... ) \
	.def(XSTRINGIFY(methodname), &classname::methodname, classname##_##methodname( __VA_ARGS__ ))

//---------------------------------------------------------------------------------
// Use this macro for boost class overloads that have a return policy.
//---------------------------------------------------------------------------------
#define CLASS_METHOD_OVERLOAD_RET( classname, methodname, docstring, args, retpol ) \
	.def(XSTRINGIFY(methodname), &classname::methodname, \
	     classname##_##methodname( args, docstring )[retpol])

//---------------------------------------------------------------------------------
// Use this macro to define a value (like a const).
//---------------------------------------------------------------------------------
#define BOOST_GLOBAL_DEFINE( varName ) \
	scope().attr(XSTRINGIFY(varName)) = varName;

//---------------------------------------------------------------------------------
// These typedefs save some typing. Use this policy for any functions that return
// a newly allocated instance of a class which you need to delete yourself.
//---------------------------------------------------------------------------------
typedef return_value_policy<manage_new_object> manage_new_object_policy;

//---------------------------------------------------------------------------------
// Use this policy for objects that someone else will free.
//---------------------------------------------------------------------------------
typedef return_value_policy<reference_existing_object> reference_existing_object_policy;

//---------------------------------------------------------------------------------
// Use this policy for functions that return const objects.
//---------------------------------------------------------------------------------
typedef return_value_policy<copy_const_reference> copy_const_reference_policy;

#endif // _WRAP_MACROS_H
