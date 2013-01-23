#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;


bpl::object py_inflictor_world_pos(CCSUsrMsg_Damage & msg)
{
    if(msg.has_inflictor_world_pos())
    {
        bpl::reference_existing_object::apply<
            const CMsgVector * &>::type convert;

        return bpl::object(bpl::handle<>(convert(msg.inflictor_world_pos())));
    }
    // return None
    return bpl::object();
}

bool py_ParseFromBytes(CCSUsrMsg_Damage & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_Damage & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_Damage & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_Damage & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_Damage isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_Damage_bindings()
{
    bpl::class_<CCSUsrMsg_Damage> binder("CCSUsrMsg_Damage");
    binder.def(bpl::init<const CCSUsrMsg_Damage &>());

    void (CCSUsrMsg_Damage::*copy_from_ptr)(const CCSUsrMsg_Damage &) = \
        &CCSUsrMsg_Damage::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_Damage::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_Damage::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_Damage::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_Damage::ByteSize);

    binder.def("has_amount", &CCSUsrMsg_Damage::has_amount);
    binder.def("set_amount", &CCSUsrMsg_Damage::set_amount);
    binder.def("clear_amount", &CCSUsrMsg_Damage::clear_amount);
    binder.add_property("amount", &CCSUsrMsg_Damage::amount);
    binder.def("has_inflictor_world_pos", &CCSUsrMsg_Damage::has_inflictor_world_pos);
    binder.add_property("inflictor_world_pos", &py_inflictor_world_pos);
    binder.def("mutable_inflictor_world_pos", &CCSUsrMsg_Damage::mutable_inflictor_world_pos,
        bpl::return_value_policy<bpl::reference_existing_object>());
    binder.def("clear_inflictor_world_pos", &CCSUsrMsg_Damage::clear_inflictor_world_pos);
;
}
