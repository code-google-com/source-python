#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_SetEloBracketInfo & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_SetEloBracketInfo & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_SetEloBracketInfo & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_SetEloBracketInfo & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_SetEloBracketInfo isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_SetEloBracketInfo_bindings()
{
    bpl::class_<CCSUsrMsg_SetEloBracketInfo> binder("CCSUsrMsg_SetEloBracketInfo");
    binder.def(bpl::init<const CCSUsrMsg_SetEloBracketInfo &>());

    void (CCSUsrMsg_SetEloBracketInfo::*copy_from_ptr)(const CCSUsrMsg_SetEloBracketInfo &) = \
        &CCSUsrMsg_SetEloBracketInfo::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_SetEloBracketInfo::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_SetEloBracketInfo::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_SetEloBracketInfo::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_SetEloBracketInfo::ByteSize);

    binder.def("has_game_mode", &CCSUsrMsg_SetEloBracketInfo::has_game_mode);
    binder.def("set_game_mode", &CCSUsrMsg_SetEloBracketInfo::set_game_mode);
    binder.def("clear_game_mode", &CCSUsrMsg_SetEloBracketInfo::clear_game_mode);
    binder.add_property("game_mode", &CCSUsrMsg_SetEloBracketInfo::game_mode);
    binder.def("has_display_bracket", &CCSUsrMsg_SetEloBracketInfo::has_display_bracket);
    binder.def("set_display_bracket", &CCSUsrMsg_SetEloBracketInfo::set_display_bracket);
    binder.def("clear_display_bracket", &CCSUsrMsg_SetEloBracketInfo::clear_display_bracket);
    binder.add_property("display_bracket", &CCSUsrMsg_SetEloBracketInfo::display_bracket);
    binder.def("has_prev_bracket", &CCSUsrMsg_SetEloBracketInfo::has_prev_bracket);
    binder.def("set_prev_bracket", &CCSUsrMsg_SetEloBracketInfo::set_prev_bracket);
    binder.def("clear_prev_bracket", &CCSUsrMsg_SetEloBracketInfo::clear_prev_bracket);
    binder.add_property("prev_bracket", &CCSUsrMsg_SetEloBracketInfo::prev_bracket);
    binder.def("has_num_games_in_bracket", &CCSUsrMsg_SetEloBracketInfo::has_num_games_in_bracket);
    binder.def("set_num_games_in_bracket", &CCSUsrMsg_SetEloBracketInfo::set_num_games_in_bracket);
    binder.def("clear_num_games_in_bracket", &CCSUsrMsg_SetEloBracketInfo::clear_num_games_in_bracket);
    binder.add_property("num_games_in_bracket", &CCSUsrMsg_SetEloBracketInfo::num_games_in_bracket);
;
}
