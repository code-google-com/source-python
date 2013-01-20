#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_SendLastKillerDamageToClient & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_SendLastKillerDamageToClient & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_SendLastKillerDamageToClient & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_SendLastKillerDamageToClient & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_SendLastKillerDamageToClient isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_SendLastKillerDamageToClient_bindings()
{
    bpl::class_<CCSUsrMsg_SendLastKillerDamageToClient> binder("CCSUsrMsg_SendLastKillerDamageToClient");
    binder.def(bpl::init<const CCSUsrMsg_SendLastKillerDamageToClient &>());

    void (CCSUsrMsg_SendLastKillerDamageToClient::*copy_from_ptr)(const CCSUsrMsg_SendLastKillerDamageToClient &) = \
        &CCSUsrMsg_SendLastKillerDamageToClient::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_SendLastKillerDamageToClient::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_SendLastKillerDamageToClient::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_SendLastKillerDamageToClient::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_SendLastKillerDamageToClient::ByteSize);

    binder.def("has_num_hits_given", &CCSUsrMsg_SendLastKillerDamageToClient::has_num_hits_given);
    binder.def("set_num_hits_given", &CCSUsrMsg_SendLastKillerDamageToClient::set_num_hits_given);
    binder.def("clear_num_hits_given", &CCSUsrMsg_SendLastKillerDamageToClient::clear_num_hits_given);
    binder.add_property("num_hits_given", &CCSUsrMsg_SendLastKillerDamageToClient::num_hits_given);
    binder.def("has_damage_given", &CCSUsrMsg_SendLastKillerDamageToClient::has_damage_given);
    binder.def("set_damage_given", &CCSUsrMsg_SendLastKillerDamageToClient::set_damage_given);
    binder.def("clear_damage_given", &CCSUsrMsg_SendLastKillerDamageToClient::clear_damage_given);
    binder.add_property("damage_given", &CCSUsrMsg_SendLastKillerDamageToClient::damage_given);
    binder.def("has_num_hits_taken", &CCSUsrMsg_SendLastKillerDamageToClient::has_num_hits_taken);
    binder.def("set_num_hits_taken", &CCSUsrMsg_SendLastKillerDamageToClient::set_num_hits_taken);
    binder.def("clear_num_hits_taken", &CCSUsrMsg_SendLastKillerDamageToClient::clear_num_hits_taken);
    binder.add_property("num_hits_taken", &CCSUsrMsg_SendLastKillerDamageToClient::num_hits_taken);
    binder.def("has_damage_taken", &CCSUsrMsg_SendLastKillerDamageToClient::has_damage_taken);
    binder.def("set_damage_taken", &CCSUsrMsg_SendLastKillerDamageToClient::set_damage_taken);
    binder.def("clear_damage_taken", &CCSUsrMsg_SendLastKillerDamageToClient::clear_damage_taken);
    binder.add_property("damage_taken", &CCSUsrMsg_SendLastKillerDamageToClient::damage_taken);
;
}
