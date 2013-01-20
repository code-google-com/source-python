#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_DisconnectToLobby & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_DisconnectToLobby & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_DisconnectToLobby & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_DisconnectToLobby & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_DisconnectToLobby isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_DisconnectToLobby_bindings()
{
    bpl::class_<CCSUsrMsg_DisconnectToLobby> binder("CCSUsrMsg_DisconnectToLobby");
    binder.def(bpl::init<const CCSUsrMsg_DisconnectToLobby &>());

    void (CCSUsrMsg_DisconnectToLobby::*copy_from_ptr)(const CCSUsrMsg_DisconnectToLobby &) = \
        &CCSUsrMsg_DisconnectToLobby::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_DisconnectToLobby::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_DisconnectToLobby::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_DisconnectToLobby::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_DisconnectToLobby::ByteSize);

    binder.def("has_dummy", &CCSUsrMsg_DisconnectToLobby::has_dummy);
    binder.def("set_dummy", &CCSUsrMsg_DisconnectToLobby::set_dummy);
    binder.def("clear_dummy", &CCSUsrMsg_DisconnectToLobby::clear_dummy);
    binder.add_property("dummy", &CCSUsrMsg_DisconnectToLobby::dummy);
;
}
