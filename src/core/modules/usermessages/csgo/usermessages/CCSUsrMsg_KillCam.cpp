#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_KillCam & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_KillCam & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_KillCam & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_KillCam & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_KillCam isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_KillCam_bindings()
{
    bpl::class_<CCSUsrMsg_KillCam, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_KillCam");
    binder.def(bpl::init<const CCSUsrMsg_KillCam &>());

    void (CCSUsrMsg_KillCam::*copy_from_ptr)(const CCSUsrMsg_KillCam &) = \
        &CCSUsrMsg_KillCam::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_KillCam::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_KillCam::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_KillCam::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_KillCam::ByteSize);

    binder.def("has_obs_mode", &CCSUsrMsg_KillCam::has_obs_mode);
    binder.def("set_obs_mode", &CCSUsrMsg_KillCam::set_obs_mode);
    binder.def("clear_obs_mode", &CCSUsrMsg_KillCam::clear_obs_mode);
    binder.add_property("obs_mode", &CCSUsrMsg_KillCam::obs_mode);
    binder.def("has_first_target", &CCSUsrMsg_KillCam::has_first_target);
    binder.def("set_first_target", &CCSUsrMsg_KillCam::set_first_target);
    binder.def("clear_first_target", &CCSUsrMsg_KillCam::clear_first_target);
    binder.add_property("first_target", &CCSUsrMsg_KillCam::first_target);
    binder.def("has_second_target", &CCSUsrMsg_KillCam::has_second_target);
    binder.def("set_second_target", &CCSUsrMsg_KillCam::set_second_target);
    binder.def("clear_second_target", &CCSUsrMsg_KillCam::clear_second_target);
    binder.add_property("second_target", &CCSUsrMsg_KillCam::second_target);
;
}
