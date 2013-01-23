#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_MatchEndConditions & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_MatchEndConditions & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_MatchEndConditions & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_MatchEndConditions & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_MatchEndConditions isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_MatchEndConditions_bindings()
{
    bpl::class_<CCSUsrMsg_MatchEndConditions, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_MatchEndConditions");
    binder.def(bpl::init<const CCSUsrMsg_MatchEndConditions &>());

    void (CCSUsrMsg_MatchEndConditions::*copy_from_ptr)(const CCSUsrMsg_MatchEndConditions &) = \
        &CCSUsrMsg_MatchEndConditions::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_MatchEndConditions::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_MatchEndConditions::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_MatchEndConditions::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_MatchEndConditions::ByteSize);

    binder.def("has_fraglimit", &CCSUsrMsg_MatchEndConditions::has_fraglimit);
    binder.def("set_fraglimit", &CCSUsrMsg_MatchEndConditions::set_fraglimit);
    binder.def("clear_fraglimit", &CCSUsrMsg_MatchEndConditions::clear_fraglimit);
    binder.add_property("fraglimit", &CCSUsrMsg_MatchEndConditions::fraglimit);
    binder.def("has_mp_maxrounds", &CCSUsrMsg_MatchEndConditions::has_mp_maxrounds);
    binder.def("set_mp_maxrounds", &CCSUsrMsg_MatchEndConditions::set_mp_maxrounds);
    binder.def("clear_mp_maxrounds", &CCSUsrMsg_MatchEndConditions::clear_mp_maxrounds);
    binder.add_property("mp_maxrounds", &CCSUsrMsg_MatchEndConditions::mp_maxrounds);
    binder.def("has_mp_winlimit", &CCSUsrMsg_MatchEndConditions::has_mp_winlimit);
    binder.def("set_mp_winlimit", &CCSUsrMsg_MatchEndConditions::set_mp_winlimit);
    binder.def("clear_mp_winlimit", &CCSUsrMsg_MatchEndConditions::clear_mp_winlimit);
    binder.add_property("mp_winlimit", &CCSUsrMsg_MatchEndConditions::mp_winlimit);
    binder.def("has_mp_timelimit", &CCSUsrMsg_MatchEndConditions::has_mp_timelimit);
    binder.def("set_mp_timelimit", &CCSUsrMsg_MatchEndConditions::set_mp_timelimit);
    binder.def("clear_mp_timelimit", &CCSUsrMsg_MatchEndConditions::clear_mp_timelimit);
    binder.add_property("mp_timelimit", &CCSUsrMsg_MatchEndConditions::mp_timelimit);
;
}
