#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

bool py_ParseFromBytes(CCSUsrMsg_ServerRankUpdate_RankUpdate & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_ServerRankUpdate_RankUpdate & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_ServerRankUpdate_RankUpdate & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_ServerRankUpdate_RankUpdate & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_ServerRankUpdate_RankUpdate isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_ServerRankUpdate_RankUpdate_bindings()
{
    bpl::class_<CCSUsrMsg_ServerRankUpdate_RankUpdate> binder("CCSUsrMsg_ServerRankUpdate_RankUpdate");
    binder.def(bpl::init<const CCSUsrMsg_ServerRankUpdate_RankUpdate &>());

    void (CCSUsrMsg_ServerRankUpdate_RankUpdate::*copy_from_ptr)(const CCSUsrMsg_ServerRankUpdate_RankUpdate &) = \
        &CCSUsrMsg_ServerRankUpdate_RankUpdate::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_ServerRankUpdate_RankUpdate::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_ServerRankUpdate_RankUpdate::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_ServerRankUpdate_RankUpdate::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_ServerRankUpdate_RankUpdate::ByteSize);

    binder.def("has_account_id", &CCSUsrMsg_ServerRankUpdate_RankUpdate::has_account_id);
    binder.def("set_account_id", &CCSUsrMsg_ServerRankUpdate_RankUpdate::set_account_id);
    binder.def("clear_account_id", &CCSUsrMsg_ServerRankUpdate_RankUpdate::clear_account_id);
    binder.add_property("account_id", &CCSUsrMsg_ServerRankUpdate_RankUpdate::account_id);
    binder.def("has_rank_old", &CCSUsrMsg_ServerRankUpdate_RankUpdate::has_rank_old);
    binder.def("set_rank_old", &CCSUsrMsg_ServerRankUpdate_RankUpdate::set_rank_old);
    binder.def("clear_rank_old", &CCSUsrMsg_ServerRankUpdate_RankUpdate::clear_rank_old);
    binder.add_property("rank_old", &CCSUsrMsg_ServerRankUpdate_RankUpdate::rank_old);
    binder.def("has_rank_new", &CCSUsrMsg_ServerRankUpdate_RankUpdate::has_rank_new);
    binder.def("set_rank_new", &CCSUsrMsg_ServerRankUpdate_RankUpdate::set_rank_new);
    binder.def("clear_rank_new", &CCSUsrMsg_ServerRankUpdate_RankUpdate::clear_rank_new);
    binder.add_property("rank_new", &CCSUsrMsg_ServerRankUpdate_RankUpdate::rank_new);
    binder.def("has_num_wins", &CCSUsrMsg_ServerRankUpdate_RankUpdate::has_num_wins);
    binder.def("set_num_wins", &CCSUsrMsg_ServerRankUpdate_RankUpdate::set_num_wins);
    binder.def("clear_num_wins", &CCSUsrMsg_ServerRankUpdate_RankUpdate::clear_num_wins);
    binder.add_property("num_wins", &CCSUsrMsg_ServerRankUpdate_RankUpdate::num_wins);
    binder.def("has_rank_change", &CCSUsrMsg_ServerRankUpdate_RankUpdate::has_rank_change);
    binder.def("set_rank_change", &CCSUsrMsg_ServerRankUpdate_RankUpdate::set_rank_change);
    binder.def("clear_rank_change", &CCSUsrMsg_ServerRankUpdate_RankUpdate::clear_rank_change);
    binder.add_property("rank_change", &CCSUsrMsg_ServerRankUpdate_RankUpdate::rank_change);
;
}
