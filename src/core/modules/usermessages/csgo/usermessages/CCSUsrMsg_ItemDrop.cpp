#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_ItemDrop & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_ItemDrop & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_ItemDrop & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_ItemDrop & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_ItemDrop isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_ItemDrop_bindings()
{
    bpl::class_<CCSUsrMsg_ItemDrop, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_ItemDrop");
    binder.def(bpl::init<const CCSUsrMsg_ItemDrop &>());

    void (CCSUsrMsg_ItemDrop::*copy_from_ptr)(const CCSUsrMsg_ItemDrop &) = \
        &CCSUsrMsg_ItemDrop::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_ItemDrop::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_ItemDrop::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_ItemDrop::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_ItemDrop::ByteSize);

    binder.def("has_itemid", &CCSUsrMsg_ItemDrop::has_itemid);
    binder.def("set_itemid", &CCSUsrMsg_ItemDrop::set_itemid);
    binder.def("clear_itemid", &CCSUsrMsg_ItemDrop::clear_itemid);
    binder.add_property("itemid", &CCSUsrMsg_ItemDrop::itemid);
    binder.def("has_death", &CCSUsrMsg_ItemDrop::has_death);
    binder.def("set_death", &CCSUsrMsg_ItemDrop::set_death);
    binder.def("clear_death", &CCSUsrMsg_ItemDrop::clear_death);
    binder.add_property("death", &CCSUsrMsg_ItemDrop::death);
;
}
