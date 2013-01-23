#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_VotePass & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_VotePass & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_VotePass & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_VotePass & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_VotePass isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_VotePass_bindings()
{
    bpl::class_<CCSUsrMsg_VotePass, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_VotePass");
    binder.def(bpl::init<const CCSUsrMsg_VotePass &>());

    void (CCSUsrMsg_VotePass::*copy_from_ptr)(const CCSUsrMsg_VotePass &) = \
        &CCSUsrMsg_VotePass::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_VotePass::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_VotePass::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_VotePass::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_VotePass::ByteSize);

    binder.def("has_team", &CCSUsrMsg_VotePass::has_team);
    binder.def("set_team", &CCSUsrMsg_VotePass::set_team);
    binder.def("clear_team", &CCSUsrMsg_VotePass::clear_team);
    binder.add_property("team", &CCSUsrMsg_VotePass::team);
    binder.def("has_vote_type", &CCSUsrMsg_VotePass::has_vote_type);
    binder.def("set_vote_type", &CCSUsrMsg_VotePass::set_vote_type);
    binder.def("clear_vote_type", &CCSUsrMsg_VotePass::clear_vote_type);
    binder.add_property("vote_type", &CCSUsrMsg_VotePass::vote_type);

    void (CCSUsrMsg_VotePass::*set_disp_str_ptr)(const std::string &) = \
        &CCSUsrMsg_VotePass::set_disp_str;

    binder.def("set_disp_str", set_disp_str_ptr);
    binder.def("has_disp_str", &CCSUsrMsg_VotePass::has_disp_str);
    binder.def("clear_disp_str", &CCSUsrMsg_VotePass::clear_disp_str);
    binder.add_property("disp_str",
        bpl::make_function(&CCSUsrMsg_VotePass::disp_str,
            bpl::return_value_policy<bpl::copy_const_reference>()));

    void (CCSUsrMsg_VotePass::*set_details_str_ptr)(const std::string &) = \
        &CCSUsrMsg_VotePass::set_details_str;

    binder.def("set_details_str", set_details_str_ptr);
    binder.def("has_details_str", &CCSUsrMsg_VotePass::has_details_str);
    binder.def("clear_details_str", &CCSUsrMsg_VotePass::clear_details_str);
    binder.add_property("details_str",
        bpl::make_function(&CCSUsrMsg_VotePass::details_str,
            bpl::return_value_policy<bpl::copy_const_reference>()));
;
}
