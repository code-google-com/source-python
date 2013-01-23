#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_SayText & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_SayText & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_SayText & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_SayText & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_SayText isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_SayText_bindings()
{
    bpl::class_<CCSUsrMsg_SayText, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_SayText");
    binder.def(bpl::init<const CCSUsrMsg_SayText &>());

    void (CCSUsrMsg_SayText::*copy_from_ptr)(const CCSUsrMsg_SayText &) = \
        &CCSUsrMsg_SayText::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_SayText::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_SayText::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_SayText::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_SayText::ByteSize);

    binder.def("has_ent_idx", &CCSUsrMsg_SayText::has_ent_idx);
    binder.def("set_ent_idx", &CCSUsrMsg_SayText::set_ent_idx);
    binder.def("clear_ent_idx", &CCSUsrMsg_SayText::clear_ent_idx);
    binder.add_property("ent_idx", &CCSUsrMsg_SayText::ent_idx);

    void (CCSUsrMsg_SayText::*set_text_ptr)(const std::string &) = \
        &CCSUsrMsg_SayText::set_text;

    binder.def("set_text", set_text_ptr);
    binder.def("has_text", &CCSUsrMsg_SayText::has_text);
    binder.def("clear_text", &CCSUsrMsg_SayText::clear_text);
    binder.add_property("text",
        bpl::make_function(&CCSUsrMsg_SayText::text,
            bpl::return_value_policy<bpl::copy_const_reference>()));
    binder.def("has_chat", &CCSUsrMsg_SayText::has_chat);
    binder.def("set_chat", &CCSUsrMsg_SayText::set_chat);
    binder.def("clear_chat", &CCSUsrMsg_SayText::clear_chat);
    binder.add_property("chat", &CCSUsrMsg_SayText::chat);
;
}
