#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_HudText & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_HudText & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_HudText & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_HudText & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_HudText isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_HudText_bindings()
{
    bpl::class_<CCSUsrMsg_HudText> binder("CCSUsrMsg_HudText");
    binder.def(bpl::init<const CCSUsrMsg_HudText &>());

    void (CCSUsrMsg_HudText::*copy_from_ptr)(const CCSUsrMsg_HudText &) = \
        &CCSUsrMsg_HudText::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_HudText::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_HudText::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_HudText::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_HudText::ByteSize);


    void (CCSUsrMsg_HudText::*set_text_ptr)(const std::string &) = \
        &CCSUsrMsg_HudText::set_text;

    binder.def("set_text", set_text_ptr);
    binder.def("has_text", &CCSUsrMsg_HudText::has_text);
    binder.def("clear_text", &CCSUsrMsg_HudText::clear_text);
    binder.add_property("text",
        bpl::make_function(&CCSUsrMsg_HudText::text,
            bpl::return_value_policy<bpl::copy_const_reference>()));
;
}
