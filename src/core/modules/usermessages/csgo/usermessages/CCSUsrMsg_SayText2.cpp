#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

 

class CCSUsrMsg_SayText2_params_proxy
{
public:

    static CCSUsrMsg_SayText2_params_proxy proxy(CCSUsrMsg_SayText2 & msg)
    { return CCSUsrMsg_SayText2_params_proxy(msg); }

    CCSUsrMsg_SayText2_params_proxy(CCSUsrMsg_SayText2 & msg)
      : _m(msg) { }

    int len()
    { return _m.params_size(); }

    const std::string & getitem(int ind);

    void setitem(unsigned ind, const std::string &);

    bpl::object iter();

    void SwapElements(int ind1, int ind2)
    { _m.mutable_params()->SwapElements(ind1, ind2); }

private:

    CCSUsrMsg_SayText2 & _m; 
};

class CCSUsrMsg_SayText2_params_iter
{
public:

    CCSUsrMsg_SayText2_params_iter(CCSUsrMsg_SayText2 & msg)
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

    CCSUsrMsg_SayText2_params_proxy _p;
    int _ind;
};

bpl::object CCSUsrMsg_SayText2_params_proxy::iter()
{ return bpl::object(CCSUsrMsg_SayText2_params_iter(_m)); }


const std::string & CCSUsrMsg_SayText2_params_proxy::getitem(int ind)
{
    if(ind < 0 || ind >= len())
        throw std::range_error("params index range error");

    return _m.params(ind);
}

void CCSUsrMsg_SayText2_params_proxy::setitem(unsigned ind, const std::string & val)
{ _m.set_params(ind, val); }

void py_add_params(CCSUsrMsg_SayText2 & m, const std::string & val)
{ m.add_params(val); }


bool py_ParseFromBytes(CCSUsrMsg_SayText2 & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_SayText2 & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_SayText2 & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_SayText2 & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_SayText2 isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_SayText2_bindings()
{
    bpl::class_<CCSUsrMsg_SayText2, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_SayText2");
    binder.def(bpl::init<const CCSUsrMsg_SayText2 &>());

    void (CCSUsrMsg_SayText2::*copy_from_ptr)(const CCSUsrMsg_SayText2 &) = \
        &CCSUsrMsg_SayText2::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_SayText2::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_SayText2::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_SayText2::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_SayText2::ByteSize);

    binder.def("has_ent_idx", &CCSUsrMsg_SayText2::has_ent_idx);
    binder.def("set_ent_idx", &CCSUsrMsg_SayText2::set_ent_idx);
    binder.def("clear_ent_idx", &CCSUsrMsg_SayText2::clear_ent_idx);
    binder.add_property("ent_idx", &CCSUsrMsg_SayText2::ent_idx);
    binder.def("has_chat", &CCSUsrMsg_SayText2::has_chat);
    binder.def("set_chat", &CCSUsrMsg_SayText2::set_chat);
    binder.def("clear_chat", &CCSUsrMsg_SayText2::clear_chat);
    binder.add_property("chat", &CCSUsrMsg_SayText2::chat);

    void (CCSUsrMsg_SayText2::*set_msg_name_ptr)(const std::string &) = \
        &CCSUsrMsg_SayText2::set_msg_name;

    binder.def("set_msg_name", set_msg_name_ptr);
    binder.def("has_msg_name", &CCSUsrMsg_SayText2::has_msg_name);
    binder.def("clear_msg_name", &CCSUsrMsg_SayText2::clear_msg_name);
    binder.add_property("msg_name",
        bpl::make_function(&CCSUsrMsg_SayText2::msg_name,
            bpl::return_value_policy<bpl::copy_const_reference>()));


    binder.def("clear_params", &CCSUsrMsg_SayText2::clear_params);
    binder.add_property("params",
        &CCSUsrMsg_SayText2_params_proxy::proxy);

    bpl::class_<CCSUsrMsg_SayText2_params_iter> params_iter_binder(
        "CCSUsrMsg_SayText2_params_iter", bpl::no_init);

    bpl::class_<CCSUsrMsg_SayText2_params_proxy> params_proxy_binder(
        "CCSUsrMsg_SayText2_params_proxy", bpl::no_init);
    params_proxy_binder.def("__len__",
        &CCSUsrMsg_SayText2_params_proxy::len);
    params_proxy_binder.def("__iter__",
        &CCSUsrMsg_SayText2_params_proxy::iter);
    params_proxy_binder.def("SwapElements",
        &CCSUsrMsg_SayText2_params_proxy::SwapElements);


    params_proxy_binder.def("__getitem__",
        &CCSUsrMsg_SayText2_params_proxy::getitem,
        bpl::return_value_policy<bpl::copy_const_reference>());

    params_proxy_binder.def("__setitem__",
        &CCSUsrMsg_SayText2_params_proxy::setitem);

    binder.def("add_params", &py_add_params);

    params_iter_binder.def("next",
        &CCSUsrMsg_SayText2_params_iter::next,
        bpl::return_value_policy<bpl::copy_const_reference>());

;
}
