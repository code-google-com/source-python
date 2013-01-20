#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_Shake & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_Shake & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_Shake & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_Shake & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_Shake isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_Shake_bindings()
{
    bpl::class_<CCSUsrMsg_Shake> binder("CCSUsrMsg_Shake");
    binder.def(bpl::init<const CCSUsrMsg_Shake &>());

    void (CCSUsrMsg_Shake::*copy_from_ptr)(const CCSUsrMsg_Shake &) = \
        &CCSUsrMsg_Shake::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_Shake::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_Shake::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_Shake::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_Shake::ByteSize);

    binder.def("has_command", &CCSUsrMsg_Shake::has_command);
    binder.def("set_command", &CCSUsrMsg_Shake::set_command);
    binder.def("clear_command", &CCSUsrMsg_Shake::clear_command);
    binder.add_property("command", &CCSUsrMsg_Shake::command);
    binder.def("has_local_amplitude", &CCSUsrMsg_Shake::has_local_amplitude);
    binder.def("set_local_amplitude", &CCSUsrMsg_Shake::set_local_amplitude);
    binder.def("clear_local_amplitude", &CCSUsrMsg_Shake::clear_local_amplitude);
    binder.add_property("local_amplitude", &CCSUsrMsg_Shake::local_amplitude);
    binder.def("has_frequency", &CCSUsrMsg_Shake::has_frequency);
    binder.def("set_frequency", &CCSUsrMsg_Shake::set_frequency);
    binder.def("clear_frequency", &CCSUsrMsg_Shake::clear_frequency);
    binder.add_property("frequency", &CCSUsrMsg_Shake::frequency);
    binder.def("has_duration", &CCSUsrMsg_Shake::has_duration);
    binder.def("set_duration", &CCSUsrMsg_Shake::set_duration);
    binder.def("clear_duration", &CCSUsrMsg_Shake::clear_duration);
    binder.add_property("duration", &CCSUsrMsg_Shake::duration);
;
}
