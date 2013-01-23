#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_SendAudio & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_SendAudio & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_SendAudio & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_SendAudio & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_SendAudio isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_SendAudio_bindings()
{
    bpl::class_<CCSUsrMsg_SendAudio, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_SendAudio");
    binder.def(bpl::init<const CCSUsrMsg_SendAudio &>());

    void (CCSUsrMsg_SendAudio::*copy_from_ptr)(const CCSUsrMsg_SendAudio &) = \
        &CCSUsrMsg_SendAudio::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_SendAudio::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_SendAudio::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_SendAudio::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_SendAudio::ByteSize);


    void (CCSUsrMsg_SendAudio::*set_radio_sound_ptr)(const std::string &) = \
        &CCSUsrMsg_SendAudio::set_radio_sound;

    binder.def("set_radio_sound", set_radio_sound_ptr);
    binder.def("has_radio_sound", &CCSUsrMsg_SendAudio::has_radio_sound);
    binder.def("clear_radio_sound", &CCSUsrMsg_SendAudio::clear_radio_sound);
    binder.add_property("radio_sound",
        bpl::make_function(&CCSUsrMsg_SendAudio::radio_sound,
            bpl::return_value_policy<bpl::copy_const_reference>()));
;
}
