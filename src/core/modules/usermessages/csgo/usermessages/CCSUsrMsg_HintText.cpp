#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_HintText & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_HintText & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_HintText & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_HintText & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_HintText isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_HintText_bindings()
{
    bpl::class_<CCSUsrMsg_HintText, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_HintText");
    binder.def(bpl::init<const CCSUsrMsg_HintText &>());

    void (CCSUsrMsg_HintText::*copy_from_ptr)(const CCSUsrMsg_HintText &) = \
        &CCSUsrMsg_HintText::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_HintText::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_HintText::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_HintText::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_HintText::ByteSize);


    void (CCSUsrMsg_HintText::*set_text_ptr)(const std::string &) = \
        &CCSUsrMsg_HintText::set_text;

    binder.def("set_text", set_text_ptr);
    binder.def("has_text", &CCSUsrMsg_HintText::has_text);
    binder.def("clear_text", &CCSUsrMsg_HintText::clear_text);
    binder.add_property("text",
        bpl::make_function(&CCSUsrMsg_HintText::text,
            bpl::return_value_policy<bpl::copy_const_reference>()));
;
}
