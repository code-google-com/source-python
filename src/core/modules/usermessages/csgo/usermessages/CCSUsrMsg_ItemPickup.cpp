#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_ItemPickup & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_ItemPickup & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_ItemPickup & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_ItemPickup & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_ItemPickup isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_ItemPickup_bindings()
{
    bpl::class_<CCSUsrMsg_ItemPickup, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_ItemPickup");
    binder.def(bpl::init<const CCSUsrMsg_ItemPickup &>());

    void (CCSUsrMsg_ItemPickup::*copy_from_ptr)(const CCSUsrMsg_ItemPickup &) = \
        &CCSUsrMsg_ItemPickup::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_ItemPickup::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_ItemPickup::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_ItemPickup::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_ItemPickup::ByteSize);


    void (CCSUsrMsg_ItemPickup::*set_item_ptr)(const std::string &) = \
        &CCSUsrMsg_ItemPickup::set_item;

    binder.def("set_item", set_item_ptr);
    binder.def("has_item", &CCSUsrMsg_ItemPickup::has_item);
    binder.def("clear_item", &CCSUsrMsg_ItemPickup::clear_item);
    binder.add_property("item",
        bpl::make_function(&CCSUsrMsg_ItemPickup::item,
            bpl::return_value_policy<bpl::copy_const_reference>()));
;
}
