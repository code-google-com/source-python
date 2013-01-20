#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_VoteStart & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_VoteStart & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_VoteStart & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_VoteStart & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_VoteStart isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_VoteStart_bindings()
{
    bpl::class_<CCSUsrMsg_VoteStart> binder("CCSUsrMsg_VoteStart");
    binder.def(bpl::init<const CCSUsrMsg_VoteStart &>());

    void (CCSUsrMsg_VoteStart::*copy_from_ptr)(const CCSUsrMsg_VoteStart &) = \
        &CCSUsrMsg_VoteStart::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_VoteStart::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_VoteStart::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_VoteStart::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_VoteStart::ByteSize);

    binder.def("has_team", &CCSUsrMsg_VoteStart::has_team);
    binder.def("set_team", &CCSUsrMsg_VoteStart::set_team);
    binder.def("clear_team", &CCSUsrMsg_VoteStart::clear_team);
    binder.add_property("team", &CCSUsrMsg_VoteStart::team);
    binder.def("has_ent_idx", &CCSUsrMsg_VoteStart::has_ent_idx);
    binder.def("set_ent_idx", &CCSUsrMsg_VoteStart::set_ent_idx);
    binder.def("clear_ent_idx", &CCSUsrMsg_VoteStart::clear_ent_idx);
    binder.add_property("ent_idx", &CCSUsrMsg_VoteStart::ent_idx);
    binder.def("has_vote_type", &CCSUsrMsg_VoteStart::has_vote_type);
    binder.def("set_vote_type", &CCSUsrMsg_VoteStart::set_vote_type);
    binder.def("clear_vote_type", &CCSUsrMsg_VoteStart::clear_vote_type);
    binder.add_property("vote_type", &CCSUsrMsg_VoteStart::vote_type);

    void (CCSUsrMsg_VoteStart::*set_disp_str_ptr)(const std::string &) = \
        &CCSUsrMsg_VoteStart::set_disp_str;

    binder.def("set_disp_str", set_disp_str_ptr);
    binder.def("has_disp_str", &CCSUsrMsg_VoteStart::has_disp_str);
    binder.def("clear_disp_str", &CCSUsrMsg_VoteStart::clear_disp_str);
    binder.add_property("disp_str",
        bpl::make_function(&CCSUsrMsg_VoteStart::disp_str,
            bpl::return_value_policy<bpl::copy_const_reference>()));

    void (CCSUsrMsg_VoteStart::*set_details_str_ptr)(const std::string &) = \
        &CCSUsrMsg_VoteStart::set_details_str;

    binder.def("set_details_str", set_details_str_ptr);
    binder.def("has_details_str", &CCSUsrMsg_VoteStart::has_details_str);
    binder.def("clear_details_str", &CCSUsrMsg_VoteStart::clear_details_str);
    binder.add_property("details_str",
        bpl::make_function(&CCSUsrMsg_VoteStart::details_str,
            bpl::return_value_policy<bpl::copy_const_reference>()));

    void (CCSUsrMsg_VoteStart::*set_other_team_str_ptr)(const std::string &) = \
        &CCSUsrMsg_VoteStart::set_other_team_str;

    binder.def("set_other_team_str", set_other_team_str_ptr);
    binder.def("has_other_team_str", &CCSUsrMsg_VoteStart::has_other_team_str);
    binder.def("clear_other_team_str", &CCSUsrMsg_VoteStart::clear_other_team_str);
    binder.add_property("other_team_str",
        bpl::make_function(&CCSUsrMsg_VoteStart::other_team_str,
            bpl::return_value_policy<bpl::copy_const_reference>()));
    binder.def("has_is_yes_no_vote", &CCSUsrMsg_VoteStart::has_is_yes_no_vote);
    binder.def("set_is_yes_no_vote", &CCSUsrMsg_VoteStart::set_is_yes_no_vote);
    binder.def("clear_is_yes_no_vote", &CCSUsrMsg_VoteStart::clear_is_yes_no_vote);
    binder.add_property("is_yes_no_vote", &CCSUsrMsg_VoteStart::is_yes_no_vote);
;
}
