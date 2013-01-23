#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_VoiceMask_PlayerMask & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_VoiceMask_PlayerMask & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_VoiceMask_PlayerMask & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_VoiceMask_PlayerMask & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_VoiceMask_PlayerMask isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_VoiceMask_PlayerMask_bindings()
{
    bpl::class_<CCSUsrMsg_VoiceMask_PlayerMask, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_VoiceMask_PlayerMask");
    binder.def(bpl::init<const CCSUsrMsg_VoiceMask_PlayerMask &>());

    void (CCSUsrMsg_VoiceMask_PlayerMask::*copy_from_ptr)(const CCSUsrMsg_VoiceMask_PlayerMask &) = \
        &CCSUsrMsg_VoiceMask_PlayerMask::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_VoiceMask_PlayerMask::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_VoiceMask_PlayerMask::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_VoiceMask_PlayerMask::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_VoiceMask_PlayerMask::ByteSize);

    binder.def("has_game_rules_mask", &CCSUsrMsg_VoiceMask_PlayerMask::has_game_rules_mask);
    binder.def("set_game_rules_mask", &CCSUsrMsg_VoiceMask_PlayerMask::set_game_rules_mask);
    binder.def("clear_game_rules_mask", &CCSUsrMsg_VoiceMask_PlayerMask::clear_game_rules_mask);
    binder.add_property("game_rules_mask", &CCSUsrMsg_VoiceMask_PlayerMask::game_rules_mask);
    binder.def("has_ban_masks", &CCSUsrMsg_VoiceMask_PlayerMask::has_ban_masks);
    binder.def("set_ban_masks", &CCSUsrMsg_VoiceMask_PlayerMask::set_ban_masks);
    binder.def("clear_ban_masks", &CCSUsrMsg_VoiceMask_PlayerMask::clear_ban_masks);
    binder.add_property("ban_masks", &CCSUsrMsg_VoiceMask_PlayerMask::ban_masks);
;
}
