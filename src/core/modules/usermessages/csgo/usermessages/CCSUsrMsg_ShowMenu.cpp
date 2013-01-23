#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_ShowMenu & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_ShowMenu & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_ShowMenu & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_ShowMenu & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_ShowMenu isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_ShowMenu_bindings()
{
    bpl::class_<CCSUsrMsg_ShowMenu, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_ShowMenu");
    binder.def(bpl::init<const CCSUsrMsg_ShowMenu &>());

    void (CCSUsrMsg_ShowMenu::*copy_from_ptr)(const CCSUsrMsg_ShowMenu &) = \
        &CCSUsrMsg_ShowMenu::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_ShowMenu::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_ShowMenu::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_ShowMenu::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_ShowMenu::ByteSize);

    binder.def("has_bits_valid_slots", &CCSUsrMsg_ShowMenu::has_bits_valid_slots);
    binder.def("set_bits_valid_slots", &CCSUsrMsg_ShowMenu::set_bits_valid_slots);
    binder.def("clear_bits_valid_slots", &CCSUsrMsg_ShowMenu::clear_bits_valid_slots);
    binder.add_property("bits_valid_slots", &CCSUsrMsg_ShowMenu::bits_valid_slots);
    binder.def("has_display_time", &CCSUsrMsg_ShowMenu::has_display_time);
    binder.def("set_display_time", &CCSUsrMsg_ShowMenu::set_display_time);
    binder.def("clear_display_time", &CCSUsrMsg_ShowMenu::clear_display_time);
    binder.add_property("display_time", &CCSUsrMsg_ShowMenu::display_time);

    void (CCSUsrMsg_ShowMenu::*set_menu_string_ptr)(const std::string &) = \
        &CCSUsrMsg_ShowMenu::set_menu_string;

    binder.def("set_menu_string", set_menu_string_ptr);
    binder.def("has_menu_string", &CCSUsrMsg_ShowMenu::has_menu_string);
    binder.def("clear_menu_string", &CCSUsrMsg_ShowMenu::clear_menu_string);
    binder.add_property("menu_string",
        bpl::make_function(&CCSUsrMsg_ShowMenu::menu_string,
            bpl::return_value_policy<bpl::copy_const_reference>()));
;
}
