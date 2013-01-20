#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_VoteFailed & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_VoteFailed & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_VoteFailed & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_VoteFailed & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_VoteFailed isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_VoteFailed_bindings()
{
    bpl::class_<CCSUsrMsg_VoteFailed> binder("CCSUsrMsg_VoteFailed");
    binder.def(bpl::init<const CCSUsrMsg_VoteFailed &>());

    void (CCSUsrMsg_VoteFailed::*copy_from_ptr)(const CCSUsrMsg_VoteFailed &) = \
        &CCSUsrMsg_VoteFailed::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_VoteFailed::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_VoteFailed::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_VoteFailed::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_VoteFailed::ByteSize);

    binder.def("has_team", &CCSUsrMsg_VoteFailed::has_team);
    binder.def("set_team", &CCSUsrMsg_VoteFailed::set_team);
    binder.def("clear_team", &CCSUsrMsg_VoteFailed::clear_team);
    binder.add_property("team", &CCSUsrMsg_VoteFailed::team);
    binder.def("has_reason", &CCSUsrMsg_VoteFailed::has_reason);
    binder.def("set_reason", &CCSUsrMsg_VoteFailed::set_reason);
    binder.def("clear_reason", &CCSUsrMsg_VoteFailed::clear_reason);
    binder.add_property("reason", &CCSUsrMsg_VoteFailed::reason);
;
}
