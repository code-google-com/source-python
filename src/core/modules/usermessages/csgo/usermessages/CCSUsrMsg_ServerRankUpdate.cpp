#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

 

class CCSUsrMsg_ServerRankUpdate_rank_update_proxy
{
public:

    static CCSUsrMsg_ServerRankUpdate_rank_update_proxy proxy(CCSUsrMsg_ServerRankUpdate & msg)
    { return CCSUsrMsg_ServerRankUpdate_rank_update_proxy(msg); }

    CCSUsrMsg_ServerRankUpdate_rank_update_proxy(CCSUsrMsg_ServerRankUpdate & msg)
      : _m(msg) { }

    int len()
    { return _m.rank_update_size(); }

    CCSUsrMsg_ServerRankUpdate_RankUpdate * getitem(int ind);

    void setitem(unsigned ind, CCSUsrMsg_ServerRankUpdate_RankUpdate *);

    bpl::object iter();

    void SwapElements(int ind1, int ind2)
    { _m.mutable_rank_update()->SwapElements(ind1, ind2); }

private:

    CCSUsrMsg_ServerRankUpdate & _m; 
};

class CCSUsrMsg_ServerRankUpdate_rank_update_iter
{
public:

    CCSUsrMsg_ServerRankUpdate_rank_update_iter(CCSUsrMsg_ServerRankUpdate & msg)
     : _p(msg), _ind(0) { }

    CCSUsrMsg_ServerRankUpdate_RankUpdate * next()
    {
        if(_ind == _p.len())
        {
            PyErr_SetObject(PyExc_StopIteration, Py_None);
            boost::python::throw_error_already_set();
        }
        return _p.getitem(_ind++);
    }

private:

    CCSUsrMsg_ServerRankUpdate_rank_update_proxy _p;
    int _ind;
};

bpl::object CCSUsrMsg_ServerRankUpdate_rank_update_proxy::iter()
{ return bpl::object(CCSUsrMsg_ServerRankUpdate_rank_update_iter(_m)); }


CCSUsrMsg_ServerRankUpdate_RankUpdate *
CCSUsrMsg_ServerRankUpdate_rank_update_proxy::getitem(int ind)
{
    if(ind < 0 || ind >= len())
        throw std::range_error("rank_update index range error");

    return _m.mutable_rank_update(ind);
}

CCSUsrMsg_ServerRankUpdate_RankUpdate * py_add_rank_update(
    CCSUsrMsg_ServerRankUpdate & m)
{ return m.add_rank_update(); }


bool py_ParseFromBytes(CCSUsrMsg_ServerRankUpdate & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_ServerRankUpdate & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_ServerRankUpdate & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_ServerRankUpdate & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_ServerRankUpdate isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_ServerRankUpdate_bindings()
{
    bpl::class_<CCSUsrMsg_ServerRankUpdate, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_ServerRankUpdate");
    binder.def(bpl::init<const CCSUsrMsg_ServerRankUpdate &>());

    void (CCSUsrMsg_ServerRankUpdate::*copy_from_ptr)(const CCSUsrMsg_ServerRankUpdate &) = \
        &CCSUsrMsg_ServerRankUpdate::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_ServerRankUpdate::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_ServerRankUpdate::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_ServerRankUpdate::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_ServerRankUpdate::ByteSize);



    binder.def("clear_rank_update", &CCSUsrMsg_ServerRankUpdate::clear_rank_update);
    binder.add_property("rank_update",
        &CCSUsrMsg_ServerRankUpdate_rank_update_proxy::proxy);

    bpl::class_<CCSUsrMsg_ServerRankUpdate_rank_update_iter> rank_update_iter_binder(
        "CCSUsrMsg_ServerRankUpdate_rank_update_iter", bpl::no_init);

    bpl::class_<CCSUsrMsg_ServerRankUpdate_rank_update_proxy> rank_update_proxy_binder(
        "CCSUsrMsg_ServerRankUpdate_rank_update_proxy", bpl::no_init);
    rank_update_proxy_binder.def("__len__",
        &CCSUsrMsg_ServerRankUpdate_rank_update_proxy::len);
    rank_update_proxy_binder.def("__iter__",
        &CCSUsrMsg_ServerRankUpdate_rank_update_proxy::iter);
    rank_update_proxy_binder.def("SwapElements",
        &CCSUsrMsg_ServerRankUpdate_rank_update_proxy::SwapElements);


    rank_update_proxy_binder.def("__getitem__",
        &CCSUsrMsg_ServerRankUpdate_rank_update_proxy::getitem,
        bpl::return_value_policy<bpl::reference_existing_object>());

    // __setitem__ not defined

    binder.def("add_rank_update", &py_add_rank_update,
        bpl::return_value_policy<bpl::reference_existing_object>());

    rank_update_iter_binder.def("next",
        &CCSUsrMsg_ServerRankUpdate_rank_update_iter::next,
        bpl::return_value_policy<bpl::reference_existing_object>());

;
}
