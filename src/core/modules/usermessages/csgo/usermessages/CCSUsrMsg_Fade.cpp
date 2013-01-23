#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;


bpl::object py_clr(CCSUsrMsg_Fade & msg)
{
    if(msg.has_clr())
    {
        bpl::reference_existing_object::apply<
            const CMsgRGBA * &>::type convert;

        return bpl::object(bpl::handle<>(convert(msg.clr())));
    }
    // return None
    return bpl::object();
}

bool py_ParseFromBytes(CCSUsrMsg_Fade & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_Fade & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_Fade & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_Fade & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_Fade isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_Fade_bindings()
{
    bpl::class_<CCSUsrMsg_Fade> binder("CCSUsrMsg_Fade");
    binder.def(bpl::init<const CCSUsrMsg_Fade &>());

    void (CCSUsrMsg_Fade::*copy_from_ptr)(const CCSUsrMsg_Fade &) = \
        &CCSUsrMsg_Fade::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_Fade::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_Fade::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_Fade::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_Fade::ByteSize);

    binder.def("has_duration", &CCSUsrMsg_Fade::has_duration);
    binder.def("set_duration", &CCSUsrMsg_Fade::set_duration);
    binder.def("clear_duration", &CCSUsrMsg_Fade::clear_duration);
    binder.add_property("duration", &CCSUsrMsg_Fade::duration);
    binder.def("has_hold_time", &CCSUsrMsg_Fade::has_hold_time);
    binder.def("set_hold_time", &CCSUsrMsg_Fade::set_hold_time);
    binder.def("clear_hold_time", &CCSUsrMsg_Fade::clear_hold_time);
    binder.add_property("hold_time", &CCSUsrMsg_Fade::hold_time);
    binder.def("has_flags", &CCSUsrMsg_Fade::has_flags);
    binder.def("set_flags", &CCSUsrMsg_Fade::set_flags);
    binder.def("clear_flags", &CCSUsrMsg_Fade::clear_flags);
    binder.add_property("flags", &CCSUsrMsg_Fade::flags);
    binder.def("has_clr", &CCSUsrMsg_Fade::has_clr);
    binder.add_property("clr", &py_clr);
    binder.def("mutable_clr", &CCSUsrMsg_Fade::mutable_clr,
        bpl::return_value_policy<bpl::reference_existing_object>());
    binder.def("clear_clr", &CCSUsrMsg_Fade::clear_clr);
;
}
