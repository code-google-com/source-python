#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_WarmupHasEnded & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_WarmupHasEnded & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_WarmupHasEnded & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_WarmupHasEnded & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_WarmupHasEnded isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_WarmupHasEnded_bindings()
{
    bpl::class_<CCSUsrMsg_WarmupHasEnded, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_WarmupHasEnded");
    binder.def(bpl::init<const CCSUsrMsg_WarmupHasEnded &>());

    void (CCSUsrMsg_WarmupHasEnded::*copy_from_ptr)(const CCSUsrMsg_WarmupHasEnded &) = \
        &CCSUsrMsg_WarmupHasEnded::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_WarmupHasEnded::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_WarmupHasEnded::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_WarmupHasEnded::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_WarmupHasEnded::ByteSize);

    binder.def("has_dummy", &CCSUsrMsg_WarmupHasEnded::has_dummy);
    binder.def("set_dummy", &CCSUsrMsg_WarmupHasEnded::set_dummy);
    binder.def("clear_dummy", &CCSUsrMsg_WarmupHasEnded::clear_dummy);
    binder.add_property("dummy", &CCSUsrMsg_WarmupHasEnded::dummy);
;
}
