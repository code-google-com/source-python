#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_BarTime & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_BarTime & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_BarTime & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_BarTime & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_BarTime isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_BarTime_bindings()
{
    bpl::class_<CCSUsrMsg_BarTime> binder("CCSUsrMsg_BarTime");
    binder.def(bpl::init<const CCSUsrMsg_BarTime &>());

    void (CCSUsrMsg_BarTime::*copy_from_ptr)(const CCSUsrMsg_BarTime &) = \
        &CCSUsrMsg_BarTime::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_BarTime::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_BarTime::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_BarTime::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_BarTime::ByteSize);


    void (CCSUsrMsg_BarTime::*set_time_ptr)(const std::string &) = \
        &CCSUsrMsg_BarTime::set_time;

    binder.def("set_time", set_time_ptr);
    binder.def("has_time", &CCSUsrMsg_BarTime::has_time);
    binder.def("clear_time", &CCSUsrMsg_BarTime::clear_time);
    binder.add_property("time",
        bpl::make_function(&CCSUsrMsg_BarTime::time,
            bpl::return_value_policy<bpl::copy_const_reference>()));
;
}
