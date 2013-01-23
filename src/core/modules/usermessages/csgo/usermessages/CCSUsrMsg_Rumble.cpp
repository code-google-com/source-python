#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_Rumble & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_Rumble & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_Rumble & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_Rumble & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_Rumble isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_Rumble_bindings()
{
    bpl::class_<CCSUsrMsg_Rumble> binder("CCSUsrMsg_Rumble");
    binder.def(bpl::init<const CCSUsrMsg_Rumble &>());

    void (CCSUsrMsg_Rumble::*copy_from_ptr)(const CCSUsrMsg_Rumble &) = \
        &CCSUsrMsg_Rumble::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_Rumble::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_Rumble::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_Rumble::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_Rumble::ByteSize);

    binder.def("has_index", &CCSUsrMsg_Rumble::has_index);
    binder.def("set_index", &CCSUsrMsg_Rumble::set_index);
    binder.def("clear_index", &CCSUsrMsg_Rumble::clear_index);
    binder.add_property("index", &CCSUsrMsg_Rumble::index);
    binder.def("has_data", &CCSUsrMsg_Rumble::has_data);
    binder.def("set_data", &CCSUsrMsg_Rumble::set_data);
    binder.def("clear_data", &CCSUsrMsg_Rumble::clear_data);
    binder.add_property("data", &CCSUsrMsg_Rumble::data);
    binder.def("has_flags", &CCSUsrMsg_Rumble::has_flags);
    binder.def("set_flags", &CCSUsrMsg_Rumble::set_flags);
    binder.def("clear_flags", &CCSUsrMsg_Rumble::clear_flags);
    binder.add_property("flags", &CCSUsrMsg_Rumble::flags);
;
}
