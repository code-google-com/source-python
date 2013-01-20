#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

 

class CCSUsrMsg_PlayerStatsUpdate_stats_proxy
{
public:

    static CCSUsrMsg_PlayerStatsUpdate_stats_proxy proxy(CCSUsrMsg_PlayerStatsUpdate & msg)
    { return CCSUsrMsg_PlayerStatsUpdate_stats_proxy(msg); }

    CCSUsrMsg_PlayerStatsUpdate_stats_proxy(CCSUsrMsg_PlayerStatsUpdate & msg)
      : _m(msg) { }

    int len()
    { return _m.stats_size(); }

    CCSUsrMsg_PlayerStatsUpdate_Stat * getitem(int ind);

    void setitem(unsigned ind, CCSUsrMsg_PlayerStatsUpdate_Stat *);

    bpl::object iter();

    void SwapElements(int ind1, int ind2)
    { _m.mutable_stats()->SwapElements(ind1, ind2); }

private:

    CCSUsrMsg_PlayerStatsUpdate & _m; 
};

class CCSUsrMsg_PlayerStatsUpdate_stats_iter
{
public:

    CCSUsrMsg_PlayerStatsUpdate_stats_iter(CCSUsrMsg_PlayerStatsUpdate & msg)
     : _p(msg), _ind(0) { }

    CCSUsrMsg_PlayerStatsUpdate_Stat * next()
    {
        if(_ind == _p.len())
        {
            PyErr_SetObject(PyExc_StopIteration, Py_None);
            boost::python::throw_error_already_set();
        }
        return _p.getitem(_ind++);
    }

private:

    CCSUsrMsg_PlayerStatsUpdate_stats_proxy _p;
    int _ind;
};

bpl::object CCSUsrMsg_PlayerStatsUpdate_stats_proxy::iter()
{ return bpl::object(CCSUsrMsg_PlayerStatsUpdate_stats_iter(_m)); }


CCSUsrMsg_PlayerStatsUpdate_Stat *
CCSUsrMsg_PlayerStatsUpdate_stats_proxy::getitem(int ind)
{
    if(ind < 0 || ind >= len())
        throw std::range_error("stats index range error");

    return _m.mutable_stats(ind);
}

CCSUsrMsg_PlayerStatsUpdate_Stat * py_add_stats(
    CCSUsrMsg_PlayerStatsUpdate & m)
{ return m.add_stats(); }


bool py_ParseFromBytes(CCSUsrMsg_PlayerStatsUpdate & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_PlayerStatsUpdate & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_PlayerStatsUpdate & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_PlayerStatsUpdate & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_PlayerStatsUpdate isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_PlayerStatsUpdate_bindings()
{
    bpl::class_<CCSUsrMsg_PlayerStatsUpdate> binder("CCSUsrMsg_PlayerStatsUpdate");
    binder.def(bpl::init<const CCSUsrMsg_PlayerStatsUpdate &>());

    void (CCSUsrMsg_PlayerStatsUpdate::*copy_from_ptr)(const CCSUsrMsg_PlayerStatsUpdate &) = \
        &CCSUsrMsg_PlayerStatsUpdate::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_PlayerStatsUpdate::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_PlayerStatsUpdate::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_PlayerStatsUpdate::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_PlayerStatsUpdate::ByteSize);

    binder.def("has_version", &CCSUsrMsg_PlayerStatsUpdate::has_version);
    binder.def("set_version", &CCSUsrMsg_PlayerStatsUpdate::set_version);
    binder.def("clear_version", &CCSUsrMsg_PlayerStatsUpdate::clear_version);
    binder.add_property("version", &CCSUsrMsg_PlayerStatsUpdate::version);
    binder.def("has_official_server", &CCSUsrMsg_PlayerStatsUpdate::has_official_server);
    binder.def("set_official_server", &CCSUsrMsg_PlayerStatsUpdate::set_official_server);
    binder.def("clear_official_server", &CCSUsrMsg_PlayerStatsUpdate::clear_official_server);
    binder.add_property("official_server", &CCSUsrMsg_PlayerStatsUpdate::official_server);


    binder.def("clear_stats", &CCSUsrMsg_PlayerStatsUpdate::clear_stats);
    binder.add_property("stats",
        &CCSUsrMsg_PlayerStatsUpdate_stats_proxy::proxy);

    bpl::class_<CCSUsrMsg_PlayerStatsUpdate_stats_iter> stats_iter_binder(
        "CCSUsrMsg_PlayerStatsUpdate_stats_iter", bpl::no_init);

    bpl::class_<CCSUsrMsg_PlayerStatsUpdate_stats_proxy> stats_proxy_binder(
        "CCSUsrMsg_PlayerStatsUpdate_stats_proxy", bpl::no_init);
    stats_proxy_binder.def("__len__",
        &CCSUsrMsg_PlayerStatsUpdate_stats_proxy::len);
    stats_proxy_binder.def("__iter__",
        &CCSUsrMsg_PlayerStatsUpdate_stats_proxy::iter);
    stats_proxy_binder.def("SwapElements",
        &CCSUsrMsg_PlayerStatsUpdate_stats_proxy::SwapElements);


    stats_proxy_binder.def("__getitem__",
        &CCSUsrMsg_PlayerStatsUpdate_stats_proxy::getitem,
        bpl::return_value_policy<bpl::reference_existing_object>());

    // __setitem__ not defined

    binder.def("add_stats", &py_add_stats,
        bpl::return_value_policy<bpl::reference_existing_object>());

    stats_iter_binder.def("next",
        &CCSUsrMsg_PlayerStatsUpdate_stats_iter::next,
        bpl::return_value_policy<bpl::reference_existing_object>());

    binder.def("has_user_id", &CCSUsrMsg_PlayerStatsUpdate::has_user_id);
    binder.def("set_user_id", &CCSUsrMsg_PlayerStatsUpdate::set_user_id);
    binder.def("clear_user_id", &CCSUsrMsg_PlayerStatsUpdate::clear_user_id);
    binder.add_property("user_id", &CCSUsrMsg_PlayerStatsUpdate::user_id);
    binder.def("has_crc", &CCSUsrMsg_PlayerStatsUpdate::has_crc);
    binder.def("set_crc", &CCSUsrMsg_PlayerStatsUpdate::set_crc);
    binder.def("clear_crc", &CCSUsrMsg_PlayerStatsUpdate::clear_crc);
    binder.add_property("crc", &CCSUsrMsg_PlayerStatsUpdate::crc);
;
}
