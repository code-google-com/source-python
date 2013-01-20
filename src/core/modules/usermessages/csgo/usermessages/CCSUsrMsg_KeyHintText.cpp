#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

 

class CCSUsrMsg_KeyHintText_hints_proxy
{
public:

    static CCSUsrMsg_KeyHintText_hints_proxy proxy(CCSUsrMsg_KeyHintText & msg)
    { return CCSUsrMsg_KeyHintText_hints_proxy(msg); }

    CCSUsrMsg_KeyHintText_hints_proxy(CCSUsrMsg_KeyHintText & msg)
      : _m(msg) { }

    int len()
    { return _m.hints_size(); }

    const std::string & getitem(int ind);

    void setitem(unsigned ind, const std::string &);

    bpl::object iter();

    void SwapElements(int ind1, int ind2)
    { _m.mutable_hints()->SwapElements(ind1, ind2); }

private:

    CCSUsrMsg_KeyHintText & _m; 
};

class CCSUsrMsg_KeyHintText_hints_iter
{
public:

    CCSUsrMsg_KeyHintText_hints_iter(CCSUsrMsg_KeyHintText & msg)
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

    CCSUsrMsg_KeyHintText_hints_proxy _p;
    int _ind;
};

bpl::object CCSUsrMsg_KeyHintText_hints_proxy::iter()
{ return bpl::object(CCSUsrMsg_KeyHintText_hints_iter(_m)); }


const std::string & CCSUsrMsg_KeyHintText_hints_proxy::getitem(int ind)
{
    if(ind < 0 || ind >= len())
        throw std::range_error("hints index range error");

    return _m.hints(ind);
}

void CCSUsrMsg_KeyHintText_hints_proxy::setitem(unsigned ind, const std::string & val)
{ _m.set_hints(ind, val); }

void py_add_hints(CCSUsrMsg_KeyHintText & m, const std::string & val)
{ m.add_hints(val); }


bool py_ParseFromBytes(CCSUsrMsg_KeyHintText & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_KeyHintText & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_KeyHintText & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_KeyHintText & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_KeyHintText isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_KeyHintText_bindings()
{
    bpl::class_<CCSUsrMsg_KeyHintText> binder("CCSUsrMsg_KeyHintText");
    binder.def(bpl::init<const CCSUsrMsg_KeyHintText &>());

    void (CCSUsrMsg_KeyHintText::*copy_from_ptr)(const CCSUsrMsg_KeyHintText &) = \
        &CCSUsrMsg_KeyHintText::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_KeyHintText::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_KeyHintText::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_KeyHintText::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_KeyHintText::ByteSize);



    binder.def("clear_hints", &CCSUsrMsg_KeyHintText::clear_hints);
    binder.add_property("hints",
        &CCSUsrMsg_KeyHintText_hints_proxy::proxy);

    bpl::class_<CCSUsrMsg_KeyHintText_hints_iter> hints_iter_binder(
        "CCSUsrMsg_KeyHintText_hints_iter", bpl::no_init);

    bpl::class_<CCSUsrMsg_KeyHintText_hints_proxy> hints_proxy_binder(
        "CCSUsrMsg_KeyHintText_hints_proxy", bpl::no_init);
    hints_proxy_binder.def("__len__",
        &CCSUsrMsg_KeyHintText_hints_proxy::len);
    hints_proxy_binder.def("__iter__",
        &CCSUsrMsg_KeyHintText_hints_proxy::iter);
    hints_proxy_binder.def("SwapElements",
        &CCSUsrMsg_KeyHintText_hints_proxy::SwapElements);


    hints_proxy_binder.def("__getitem__",
        &CCSUsrMsg_KeyHintText_hints_proxy::getitem,
        bpl::return_value_policy<bpl::copy_const_reference>());

    hints_proxy_binder.def("__setitem__",
        &CCSUsrMsg_KeyHintText_hints_proxy::setitem);

    binder.def("add_hints", &py_add_hints);

    hints_iter_binder.def("next",
        &CCSUsrMsg_KeyHintText_hints_iter::next,
        bpl::return_value_policy<bpl::copy_const_reference>());

;
}
