#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_XRankUpd & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_XRankUpd & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_XRankUpd & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_XRankUpd & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_XRankUpd isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_XRankUpd_bindings()
{
    bpl::class_<CCSUsrMsg_XRankUpd, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_XRankUpd");
    binder.def(bpl::init<const CCSUsrMsg_XRankUpd &>());

    void (CCSUsrMsg_XRankUpd::*copy_from_ptr)(const CCSUsrMsg_XRankUpd &) = \
        &CCSUsrMsg_XRankUpd::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_XRankUpd::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_XRankUpd::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_XRankUpd::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_XRankUpd::ByteSize);

    binder.def("has_mode_idx", &CCSUsrMsg_XRankUpd::has_mode_idx);
    binder.def("set_mode_idx", &CCSUsrMsg_XRankUpd::set_mode_idx);
    binder.def("clear_mode_idx", &CCSUsrMsg_XRankUpd::clear_mode_idx);
    binder.add_property("mode_idx", &CCSUsrMsg_XRankUpd::mode_idx);
    binder.def("has_controller", &CCSUsrMsg_XRankUpd::has_controller);
    binder.def("set_controller", &CCSUsrMsg_XRankUpd::set_controller);
    binder.def("clear_controller", &CCSUsrMsg_XRankUpd::clear_controller);
    binder.add_property("controller", &CCSUsrMsg_XRankUpd::controller);
    binder.def("has_ranking", &CCSUsrMsg_XRankUpd::has_ranking);
    binder.def("set_ranking", &CCSUsrMsg_XRankUpd::set_ranking);
    binder.def("clear_ranking", &CCSUsrMsg_XRankUpd::clear_ranking);
    binder.add_property("ranking", &CCSUsrMsg_XRankUpd::ranking);
;
}
