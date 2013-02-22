#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_XRankGet & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_XRankGet & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_XRankGet & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_XRankGet & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_XRankGet isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_XRankGet_bindings()
{
    bpl::class_<CCSUsrMsg_XRankGet, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_XRankGet");
    binder.def(bpl::init<const CCSUsrMsg_XRankGet &>());

    void (CCSUsrMsg_XRankGet::*copy_from_ptr)(const CCSUsrMsg_XRankGet &) = \
        &CCSUsrMsg_XRankGet::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_XRankGet::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_XRankGet::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_XRankGet::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_XRankGet::ByteSize);

    binder.def("has_mode_idx", &CCSUsrMsg_XRankGet::has_mode_idx);
    binder.def("set_mode_idx", &CCSUsrMsg_XRankGet::set_mode_idx);
    binder.def("clear_mode_idx", &CCSUsrMsg_XRankGet::clear_mode_idx);
    binder.add_property("mode_idx", &CCSUsrMsg_XRankGet::mode_idx);
    binder.def("has_controller", &CCSUsrMsg_XRankGet::has_controller);
    binder.def("set_controller", &CCSUsrMsg_XRankGet::set_controller);
    binder.def("clear_controller", &CCSUsrMsg_XRankGet::clear_controller);
    binder.add_property("controller", &CCSUsrMsg_XRankGet::controller);
;
}
