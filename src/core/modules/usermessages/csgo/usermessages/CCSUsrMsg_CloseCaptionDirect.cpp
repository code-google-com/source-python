#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_CloseCaptionDirect & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_CloseCaptionDirect & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_CloseCaptionDirect & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_CloseCaptionDirect & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_CloseCaptionDirect isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_CloseCaptionDirect_bindings()
{
    bpl::class_<CCSUsrMsg_CloseCaptionDirect, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_CloseCaptionDirect");
    binder.def(bpl::init<const CCSUsrMsg_CloseCaptionDirect &>());

    void (CCSUsrMsg_CloseCaptionDirect::*copy_from_ptr)(const CCSUsrMsg_CloseCaptionDirect &) = \
        &CCSUsrMsg_CloseCaptionDirect::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_CloseCaptionDirect::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_CloseCaptionDirect::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_CloseCaptionDirect::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_CloseCaptionDirect::ByteSize);

    binder.def("has_hash", &CCSUsrMsg_CloseCaptionDirect::has_hash);
    binder.def("set_hash", &CCSUsrMsg_CloseCaptionDirect::set_hash);
    binder.def("clear_hash", &CCSUsrMsg_CloseCaptionDirect::clear_hash);
    binder.add_property("hash", &CCSUsrMsg_CloseCaptionDirect::hash);
    binder.def("has_duration", &CCSUsrMsg_CloseCaptionDirect::has_duration);
    binder.def("set_duration", &CCSUsrMsg_CloseCaptionDirect::set_duration);
    binder.def("clear_duration", &CCSUsrMsg_CloseCaptionDirect::clear_duration);
    binder.add_property("duration", &CCSUsrMsg_CloseCaptionDirect::duration);
    binder.def("has_from_player", &CCSUsrMsg_CloseCaptionDirect::has_from_player);
    binder.def("set_from_player", &CCSUsrMsg_CloseCaptionDirect::set_from_player);
    binder.def("clear_from_player", &CCSUsrMsg_CloseCaptionDirect::clear_from_player);
    binder.add_property("from_player", &CCSUsrMsg_CloseCaptionDirect::from_player);
;
}
