#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_VGUIMenu_Subkey & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_VGUIMenu_Subkey & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_VGUIMenu_Subkey & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_VGUIMenu_Subkey & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_VGUIMenu_Subkey isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_VGUIMenu_Subkey_bindings()
{
    bpl::class_<CCSUsrMsg_VGUIMenu_Subkey> binder("CCSUsrMsg_VGUIMenu_Subkey");
    binder.def(bpl::init<const CCSUsrMsg_VGUIMenu_Subkey &>());

    void (CCSUsrMsg_VGUIMenu_Subkey::*copy_from_ptr)(const CCSUsrMsg_VGUIMenu_Subkey &) = \
        &CCSUsrMsg_VGUIMenu_Subkey::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_VGUIMenu_Subkey::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_VGUIMenu_Subkey::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_VGUIMenu_Subkey::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_VGUIMenu_Subkey::ByteSize);


    void (CCSUsrMsg_VGUIMenu_Subkey::*set_name_ptr)(const std::string &) = \
        &CCSUsrMsg_VGUIMenu_Subkey::set_name;

    binder.def("set_name", set_name_ptr);
    binder.def("has_name", &CCSUsrMsg_VGUIMenu_Subkey::has_name);
    binder.def("clear_name", &CCSUsrMsg_VGUIMenu_Subkey::clear_name);
    binder.add_property("name",
        bpl::make_function(&CCSUsrMsg_VGUIMenu_Subkey::name,
            bpl::return_value_policy<bpl::copy_const_reference>()));

    void (CCSUsrMsg_VGUIMenu_Subkey::*set_str_ptr)(const std::string &) = \
        &CCSUsrMsg_VGUIMenu_Subkey::set_str;

    binder.def("set_str", set_str_ptr);
    binder.def("has_str", &CCSUsrMsg_VGUIMenu_Subkey::has_str);
    binder.def("clear_str", &CCSUsrMsg_VGUIMenu_Subkey::clear_str);
    binder.add_property("str",
        bpl::make_function(&CCSUsrMsg_VGUIMenu_Subkey::str,
            bpl::return_value_policy<bpl::copy_const_reference>()));
;
}
