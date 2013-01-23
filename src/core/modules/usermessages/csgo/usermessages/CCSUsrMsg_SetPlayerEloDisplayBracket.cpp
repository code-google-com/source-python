#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_SetPlayerEloDisplayBracket & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_SetPlayerEloDisplayBracket & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_SetPlayerEloDisplayBracket & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_SetPlayerEloDisplayBracket & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_SetPlayerEloDisplayBracket isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_SetPlayerEloDisplayBracket_bindings()
{
    bpl::class_<CCSUsrMsg_SetPlayerEloDisplayBracket, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_SetPlayerEloDisplayBracket");
    binder.def(bpl::init<const CCSUsrMsg_SetPlayerEloDisplayBracket &>());

    void (CCSUsrMsg_SetPlayerEloDisplayBracket::*copy_from_ptr)(const CCSUsrMsg_SetPlayerEloDisplayBracket &) = \
        &CCSUsrMsg_SetPlayerEloDisplayBracket::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_SetPlayerEloDisplayBracket::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_SetPlayerEloDisplayBracket::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_SetPlayerEloDisplayBracket::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_SetPlayerEloDisplayBracket::ByteSize);

    binder.def("has_bracket", &CCSUsrMsg_SetPlayerEloDisplayBracket::has_bracket);
    binder.def("set_bracket", &CCSUsrMsg_SetPlayerEloDisplayBracket::set_bracket);
    binder.def("clear_bracket", &CCSUsrMsg_SetPlayerEloDisplayBracket::clear_bracket);
    binder.add_property("bracket", &CCSUsrMsg_SetPlayerEloDisplayBracket::bracket);
;
}
