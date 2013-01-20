#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

 

class CCSUsrMsg_RadioText_params_proxy
{
public:

    static CCSUsrMsg_RadioText_params_proxy proxy(CCSUsrMsg_RadioText & msg)
    { return CCSUsrMsg_RadioText_params_proxy(msg); }

    CCSUsrMsg_RadioText_params_proxy(CCSUsrMsg_RadioText & msg)
      : _m(msg) { }

    int len()
    { return _m.params_size(); }

    const std::string & getitem(int ind);

    void setitem(unsigned ind, const std::string &);

    bpl::object iter();

    void SwapElements(int ind1, int ind2)
    { _m.mutable_params()->SwapElements(ind1, ind2); }

private:

    CCSUsrMsg_RadioText & _m; 
};

class CCSUsrMsg_RadioText_params_iter
{
public:

    CCSUsrMsg_RadioText_params_iter(CCSUsrMsg_RadioText & msg)
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

    CCSUsrMsg_RadioText_params_proxy _p;
    int _ind;
};

bpl::object CCSUsrMsg_RadioText_params_proxy::iter()
{ return bpl::object(CCSUsrMsg_RadioText_params_iter(_m)); }


const std::string & CCSUsrMsg_RadioText_params_proxy::getitem(int ind)
{
    if(ind < 0 || ind >= len())
        throw std::range_error("params index range error");

    return _m.params(ind);
}

void CCSUsrMsg_RadioText_params_proxy::setitem(unsigned ind, const std::string & val)
{ _m.set_params(ind, val); }

void py_add_params(CCSUsrMsg_RadioText & m, const std::string & val)
{ m.add_params(val); }


bool py_ParseFromBytes(CCSUsrMsg_RadioText & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_RadioText & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_RadioText & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_RadioText & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_RadioText isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_RadioText_bindings()
{
    bpl::class_<CCSUsrMsg_RadioText> binder("CCSUsrMsg_RadioText");
    binder.def(bpl::init<const CCSUsrMsg_RadioText &>());

    void (CCSUsrMsg_RadioText::*copy_from_ptr)(const CCSUsrMsg_RadioText &) = \
        &CCSUsrMsg_RadioText::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_RadioText::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_RadioText::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_RadioText::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_RadioText::ByteSize);

    binder.def("has_msg_dst", &CCSUsrMsg_RadioText::has_msg_dst);
    binder.def("set_msg_dst", &CCSUsrMsg_RadioText::set_msg_dst);
    binder.def("clear_msg_dst", &CCSUsrMsg_RadioText::clear_msg_dst);
    binder.add_property("msg_dst", &CCSUsrMsg_RadioText::msg_dst);
    binder.def("has_client", &CCSUsrMsg_RadioText::has_client);
    binder.def("set_client", &CCSUsrMsg_RadioText::set_client);
    binder.def("clear_client", &CCSUsrMsg_RadioText::clear_client);
    binder.add_property("client", &CCSUsrMsg_RadioText::client);

    void (CCSUsrMsg_RadioText::*set_msg_name_ptr)(const std::string &) = \
        &CCSUsrMsg_RadioText::set_msg_name;

    binder.def("set_msg_name", set_msg_name_ptr);
    binder.def("has_msg_name", &CCSUsrMsg_RadioText::has_msg_name);
    binder.def("clear_msg_name", &CCSUsrMsg_RadioText::clear_msg_name);
    binder.add_property("msg_name",
        bpl::make_function(&CCSUsrMsg_RadioText::msg_name,
            bpl::return_value_policy<bpl::copy_const_reference>()));


    binder.def("clear_params", &CCSUsrMsg_RadioText::clear_params);
    binder.add_property("params",
        &CCSUsrMsg_RadioText_params_proxy::proxy);

    bpl::class_<CCSUsrMsg_RadioText_params_iter> params_iter_binder(
        "CCSUsrMsg_RadioText_params_iter", bpl::no_init);

    bpl::class_<CCSUsrMsg_RadioText_params_proxy> params_proxy_binder(
        "CCSUsrMsg_RadioText_params_proxy", bpl::no_init);
    params_proxy_binder.def("__len__",
        &CCSUsrMsg_RadioText_params_proxy::len);
    params_proxy_binder.def("__iter__",
        &CCSUsrMsg_RadioText_params_proxy::iter);
    params_proxy_binder.def("SwapElements",
        &CCSUsrMsg_RadioText_params_proxy::SwapElements);


    params_proxy_binder.def("__getitem__",
        &CCSUsrMsg_RadioText_params_proxy::getitem,
        bpl::return_value_policy<bpl::copy_const_reference>());

    params_proxy_binder.def("__setitem__",
        &CCSUsrMsg_RadioText_params_proxy::setitem);

    binder.def("add_params", &py_add_params);

    params_iter_binder.def("next",
        &CCSUsrMsg_RadioText_params_iter::next,
        bpl::return_value_policy<bpl::copy_const_reference>());

;
}
