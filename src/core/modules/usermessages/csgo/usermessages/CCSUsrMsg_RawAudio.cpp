#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_RawAudio & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_RawAudio & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_RawAudio & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_RawAudio & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_RawAudio isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_RawAudio_bindings()
{
    bpl::class_<CCSUsrMsg_RawAudio> binder("CCSUsrMsg_RawAudio");
    binder.def(bpl::init<const CCSUsrMsg_RawAudio &>());

    void (CCSUsrMsg_RawAudio::*copy_from_ptr)(const CCSUsrMsg_RawAudio &) = \
        &CCSUsrMsg_RawAudio::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_RawAudio::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_RawAudio::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_RawAudio::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_RawAudio::ByteSize);

    binder.def("has_pitch", &CCSUsrMsg_RawAudio::has_pitch);
    binder.def("set_pitch", &CCSUsrMsg_RawAudio::set_pitch);
    binder.def("clear_pitch", &CCSUsrMsg_RawAudio::clear_pitch);
    binder.add_property("pitch", &CCSUsrMsg_RawAudio::pitch);
    binder.def("has_entidx", &CCSUsrMsg_RawAudio::has_entidx);
    binder.def("set_entidx", &CCSUsrMsg_RawAudio::set_entidx);
    binder.def("clear_entidx", &CCSUsrMsg_RawAudio::clear_entidx);
    binder.add_property("entidx", &CCSUsrMsg_RawAudio::entidx);
    binder.def("has_duration", &CCSUsrMsg_RawAudio::has_duration);
    binder.def("set_duration", &CCSUsrMsg_RawAudio::set_duration);
    binder.def("clear_duration", &CCSUsrMsg_RawAudio::clear_duration);
    binder.add_property("duration", &CCSUsrMsg_RawAudio::duration);

    void (CCSUsrMsg_RawAudio::*set_voice_filename_ptr)(const std::string &) = \
        &CCSUsrMsg_RawAudio::set_voice_filename;

    binder.def("set_voice_filename", set_voice_filename_ptr);
    binder.def("has_voice_filename", &CCSUsrMsg_RawAudio::has_voice_filename);
    binder.def("clear_voice_filename", &CCSUsrMsg_RawAudio::clear_voice_filename);
    binder.add_property("voice_filename",
        bpl::make_function(&CCSUsrMsg_RawAudio::voice_filename,
            bpl::return_value_policy<bpl::copy_const_reference>()));
;
}
