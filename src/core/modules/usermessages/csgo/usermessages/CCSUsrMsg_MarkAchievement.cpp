#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_MarkAchievement & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_MarkAchievement & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_MarkAchievement & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_MarkAchievement & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_MarkAchievement isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_MarkAchievement_bindings()
{
    bpl::class_<CCSUsrMsg_MarkAchievement> binder("CCSUsrMsg_MarkAchievement");
    binder.def(bpl::init<const CCSUsrMsg_MarkAchievement &>());

    void (CCSUsrMsg_MarkAchievement::*copy_from_ptr)(const CCSUsrMsg_MarkAchievement &) = \
        &CCSUsrMsg_MarkAchievement::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_MarkAchievement::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_MarkAchievement::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_MarkAchievement::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_MarkAchievement::ByteSize);


    void (CCSUsrMsg_MarkAchievement::*set_achievement_ptr)(const std::string &) = \
        &CCSUsrMsg_MarkAchievement::set_achievement;

    binder.def("set_achievement", set_achievement_ptr);
    binder.def("has_achievement", &CCSUsrMsg_MarkAchievement::has_achievement);
    binder.def("clear_achievement", &CCSUsrMsg_MarkAchievement::clear_achievement);
    binder.add_property("achievement",
        bpl::make_function(&CCSUsrMsg_MarkAchievement::achievement,
            bpl::return_value_policy<bpl::copy_const_reference>()));
;
}
