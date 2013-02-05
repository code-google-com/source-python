#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

 

class CCSUsrMsg_VoteSetup_potential_issues_proxy
{
public:

    static CCSUsrMsg_VoteSetup_potential_issues_proxy proxy(CCSUsrMsg_VoteSetup & msg)
    { return CCSUsrMsg_VoteSetup_potential_issues_proxy(msg); }

    CCSUsrMsg_VoteSetup_potential_issues_proxy(CCSUsrMsg_VoteSetup & msg)
      : _m(msg) { }

    int len()
    { return _m.potential_issues_size(); }

    const std::string & getitem(int ind);

    void setitem(unsigned ind, const std::string &);

    bpl::object iter();

    void SwapElements(int ind1, int ind2)
    { _m.mutable_potential_issues()->SwapElements(ind1, ind2); }

private:

    CCSUsrMsg_VoteSetup & _m; 
};

class CCSUsrMsg_VoteSetup_potential_issues_iter
{
public:

    CCSUsrMsg_VoteSetup_potential_issues_iter(CCSUsrMsg_VoteSetup & msg)
     : _p(msg), _ind(0) { }

    const std::string & next()
    {
        if(_ind == _p.len())
        {
            PyErr_SetObject(PyExc_StopIteration, Py_None);
            boost::python::throw_error_already_set();
        }
        return _p.getitem(_ind++);
    }

private:

    CCSUsrMsg_VoteSetup_potential_issues_proxy _p;
    int _ind;
};

bpl::object CCSUsrMsg_VoteSetup_potential_issues_proxy::iter()
{ return bpl::object(CCSUsrMsg_VoteSetup_potential_issues_iter(_m)); }


const std::string & CCSUsrMsg_VoteSetup_potential_issues_proxy::getitem(int ind)
{
    if(ind < 0 || ind >= len())
        throw std::range_error("potential_issues index range error");

    return _m.potential_issues(ind);
}

void CCSUsrMsg_VoteSetup_potential_issues_proxy::setitem(unsigned ind, const std::string & val)
{ _m.set_potential_issues(ind, val); }

void py_add_potential_issues(CCSUsrMsg_VoteSetup & m, const std::string & val)
{ m.add_potential_issues(val); }


bool py_ParseFromBytes(CCSUsrMsg_VoteSetup & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_VoteSetup & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_VoteSetup & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_VoteSetup & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_VoteSetup isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_VoteSetup_bindings()
{
    bpl::class_<CCSUsrMsg_VoteSetup, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_VoteSetup");
    binder.def(bpl::init<const CCSUsrMsg_VoteSetup &>());

    void (CCSUsrMsg_VoteSetup::*copy_from_ptr)(const CCSUsrMsg_VoteSetup &) = \
        &CCSUsrMsg_VoteSetup::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_VoteSetup::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_VoteSetup::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_VoteSetup::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_VoteSetup::ByteSize);



    binder.def("clear_potential_issues", &CCSUsrMsg_VoteSetup::clear_potential_issues);
    binder.add_property("potential_issues",
        &CCSUsrMsg_VoteSetup_potential_issues_proxy::proxy);

    bpl::class_<CCSUsrMsg_VoteSetup_potential_issues_iter> potential_issues_iter_binder(
        "CCSUsrMsg_VoteSetup_potential_issues_iter", bpl::no_init);

    bpl::class_<CCSUsrMsg_VoteSetup_potential_issues_proxy> potential_issues_proxy_binder(
        "CCSUsrMsg_VoteSetup_potential_issues_proxy", bpl::no_init);
    potential_issues_proxy_binder.def("__len__",
        &CCSUsrMsg_VoteSetup_potential_issues_proxy::len);
    potential_issues_proxy_binder.def("__iter__",
        &CCSUsrMsg_VoteSetup_potential_issues_proxy::iter);
    potential_issues_proxy_binder.def("SwapElements",
        &CCSUsrMsg_VoteSetup_potential_issues_proxy::SwapElements);


    potential_issues_proxy_binder.def("__getitem__",
        &CCSUsrMsg_VoteSetup_potential_issues_proxy::getitem,
        bpl::return_value_policy<bpl::copy_const_reference>());

    potential_issues_proxy_binder.def("__setitem__",
        &CCSUsrMsg_VoteSetup_potential_issues_proxy::setitem);

    binder.def("add_potential_issues", &py_add_potential_issues);

    potential_issues_iter_binder.def("next",
        &CCSUsrMsg_VoteSetup_potential_issues_iter::next,
        bpl::return_value_policy<bpl::copy_const_reference>());

;
}
