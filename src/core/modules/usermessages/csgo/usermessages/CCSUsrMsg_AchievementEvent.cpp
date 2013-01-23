#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_AchievementEvent & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_AchievementEvent & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_AchievementEvent & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_AchievementEvent & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_AchievementEvent isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_AchievementEvent_bindings()
{
    bpl::class_<CCSUsrMsg_AchievementEvent, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_AchievementEvent");
    binder.def(bpl::init<const CCSUsrMsg_AchievementEvent &>());

    void (CCSUsrMsg_AchievementEvent::*copy_from_ptr)(const CCSUsrMsg_AchievementEvent &) = \
        &CCSUsrMsg_AchievementEvent::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_AchievementEvent::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_AchievementEvent::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_AchievementEvent::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_AchievementEvent::ByteSize);

    binder.def("has_achievement", &CCSUsrMsg_AchievementEvent::has_achievement);
    binder.def("set_achievement", &CCSUsrMsg_AchievementEvent::set_achievement);
    binder.def("clear_achievement", &CCSUsrMsg_AchievementEvent::clear_achievement);
    binder.add_property("achievement", &CCSUsrMsg_AchievementEvent::achievement);
    binder.def("has_count", &CCSUsrMsg_AchievementEvent::has_count);
    binder.def("set_count", &CCSUsrMsg_AchievementEvent::set_count);
    binder.def("clear_count", &CCSUsrMsg_AchievementEvent::clear_count);
    binder.add_property("count", &CCSUsrMsg_AchievementEvent::count);
    binder.def("has_user_id", &CCSUsrMsg_AchievementEvent::has_user_id);
    binder.def("set_user_id", &CCSUsrMsg_AchievementEvent::set_user_id);
    binder.def("clear_user_id", &CCSUsrMsg_AchievementEvent::clear_user_id);
    binder.add_property("user_id", &CCSUsrMsg_AchievementEvent::user_id);
;
}
