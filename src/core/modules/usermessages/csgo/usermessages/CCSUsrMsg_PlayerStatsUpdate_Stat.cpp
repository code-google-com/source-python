#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_PlayerStatsUpdate_Stat & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_PlayerStatsUpdate_Stat & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_PlayerStatsUpdate_Stat & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_PlayerStatsUpdate_Stat & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_PlayerStatsUpdate_Stat isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_PlayerStatsUpdate_Stat_bindings()
{
    bpl::class_<CCSUsrMsg_PlayerStatsUpdate_Stat> binder("CCSUsrMsg_PlayerStatsUpdate_Stat");
    binder.def(bpl::init<const CCSUsrMsg_PlayerStatsUpdate_Stat &>());

    void (CCSUsrMsg_PlayerStatsUpdate_Stat::*copy_from_ptr)(const CCSUsrMsg_PlayerStatsUpdate_Stat &) = \
        &CCSUsrMsg_PlayerStatsUpdate_Stat::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_PlayerStatsUpdate_Stat::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_PlayerStatsUpdate_Stat::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_PlayerStatsUpdate_Stat::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_PlayerStatsUpdate_Stat::ByteSize);

    binder.def("has_idx", &CCSUsrMsg_PlayerStatsUpdate_Stat::has_idx);
    binder.def("set_idx", &CCSUsrMsg_PlayerStatsUpdate_Stat::set_idx);
    binder.def("clear_idx", &CCSUsrMsg_PlayerStatsUpdate_Stat::clear_idx);
    binder.add_property("idx", &CCSUsrMsg_PlayerStatsUpdate_Stat::idx);
    binder.def("has_delta", &CCSUsrMsg_PlayerStatsUpdate_Stat::has_delta);
    binder.def("set_delta", &CCSUsrMsg_PlayerStatsUpdate_Stat::set_delta);
    binder.def("clear_delta", &CCSUsrMsg_PlayerStatsUpdate_Stat::clear_delta);
    binder.add_property("delta", &CCSUsrMsg_PlayerStatsUpdate_Stat::delta);
;
}
