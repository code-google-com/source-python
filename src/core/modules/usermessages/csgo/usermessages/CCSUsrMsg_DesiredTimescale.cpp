#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_DesiredTimescale & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_DesiredTimescale & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_DesiredTimescale & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_DesiredTimescale & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_DesiredTimescale isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_DesiredTimescale_bindings()
{
    bpl::class_<CCSUsrMsg_DesiredTimescale, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_DesiredTimescale");
    binder.def(bpl::init<const CCSUsrMsg_DesiredTimescale &>());

    void (CCSUsrMsg_DesiredTimescale::*copy_from_ptr)(const CCSUsrMsg_DesiredTimescale &) = \
        &CCSUsrMsg_DesiredTimescale::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_DesiredTimescale::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_DesiredTimescale::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_DesiredTimescale::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_DesiredTimescale::ByteSize);

    binder.def("has_desired_timescale", &CCSUsrMsg_DesiredTimescale::has_desired_timescale);
    binder.def("set_desired_timescale", &CCSUsrMsg_DesiredTimescale::set_desired_timescale);
    binder.def("clear_desired_timescale", &CCSUsrMsg_DesiredTimescale::clear_desired_timescale);
    binder.add_property("desired_timescale", &CCSUsrMsg_DesiredTimescale::desired_timescale);
    binder.def("has_duration_realtime_sec", &CCSUsrMsg_DesiredTimescale::has_duration_realtime_sec);
    binder.def("set_duration_realtime_sec", &CCSUsrMsg_DesiredTimescale::set_duration_realtime_sec);
    binder.def("clear_duration_realtime_sec", &CCSUsrMsg_DesiredTimescale::clear_duration_realtime_sec);
    binder.add_property("duration_realtime_sec", &CCSUsrMsg_DesiredTimescale::duration_realtime_sec);
    binder.def("has_interpolator_type", &CCSUsrMsg_DesiredTimescale::has_interpolator_type);
    binder.def("set_interpolator_type", &CCSUsrMsg_DesiredTimescale::set_interpolator_type);
    binder.def("clear_interpolator_type", &CCSUsrMsg_DesiredTimescale::clear_interpolator_type);
    binder.add_property("interpolator_type", &CCSUsrMsg_DesiredTimescale::interpolator_type);
    binder.def("has_start_blend_time", &CCSUsrMsg_DesiredTimescale::has_start_blend_time);
    binder.def("set_start_blend_time", &CCSUsrMsg_DesiredTimescale::set_start_blend_time);
    binder.def("clear_start_blend_time", &CCSUsrMsg_DesiredTimescale::clear_start_blend_time);
    binder.add_property("start_blend_time", &CCSUsrMsg_DesiredTimescale::start_blend_time);
;
}
