#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate_bindings()
{
    bpl::class_<CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate");
    binder.def(bpl::init<const CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate &>());

    void (CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::*copy_from_ptr)(const CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate &) = \
        &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::ByteSize);

    binder.def("has_entity_idx", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::has_entity_idx);
    binder.def("set_entity_idx", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::set_entity_idx);
    binder.def("clear_entity_idx", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::clear_entity_idx);
    binder.add_property("entity_idx", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::entity_idx);
    binder.def("has_class_id", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::has_class_id);
    binder.def("set_class_id", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::set_class_id);
    binder.def("clear_class_id", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::clear_class_id);
    binder.add_property("class_id", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::class_id);
    binder.def("has_origin_x", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::has_origin_x);
    binder.def("set_origin_x", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::set_origin_x);
    binder.def("clear_origin_x", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::clear_origin_x);
    binder.add_property("origin_x", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::origin_x);
    binder.def("has_origin_y", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::has_origin_y);
    binder.def("set_origin_y", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::set_origin_y);
    binder.def("clear_origin_y", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::clear_origin_y);
    binder.add_property("origin_y", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::origin_y);
    binder.def("has_origin_z", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::has_origin_z);
    binder.def("set_origin_z", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::set_origin_z);
    binder.def("clear_origin_z", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::clear_origin_z);
    binder.add_property("origin_z", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::origin_z);
    binder.def("has_angle_y", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::has_angle_y);
    binder.def("set_angle_y", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::set_angle_y);
    binder.def("clear_angle_y", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::clear_angle_y);
    binder.add_property("angle_y", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::angle_y);
    binder.def("has_defuser", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::has_defuser);
    binder.def("set_defuser", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::set_defuser);
    binder.def("clear_defuser", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::clear_defuser);
    binder.add_property("defuser", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::defuser);
    binder.def("has_player_has_defuser", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::has_player_has_defuser);
    binder.def("set_player_has_defuser", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::set_player_has_defuser);
    binder.def("clear_player_has_defuser", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::clear_player_has_defuser);
    binder.add_property("player_has_defuser", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::player_has_defuser);
    binder.def("has_player_has_c4", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::has_player_has_c4);
    binder.def("set_player_has_c4", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::set_player_has_c4);
    binder.def("clear_player_has_c4", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::clear_player_has_c4);
    binder.add_property("player_has_c4", &CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate::player_has_c4);
;
}
