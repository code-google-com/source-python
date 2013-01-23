#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

 

class CCSUsrMsg_VGUIMenu_subkeys_proxy
{
public:

    static CCSUsrMsg_VGUIMenu_subkeys_proxy proxy(CCSUsrMsg_VGUIMenu & msg)
    { return CCSUsrMsg_VGUIMenu_subkeys_proxy(msg); }

    CCSUsrMsg_VGUIMenu_subkeys_proxy(CCSUsrMsg_VGUIMenu & msg)
      : _m(msg) { }

    int len()
    { return _m.subkeys_size(); }

    CCSUsrMsg_VGUIMenu_Subkey * getitem(int ind);

    void setitem(unsigned ind, CCSUsrMsg_VGUIMenu_Subkey *);

    bpl::object iter();

    void SwapElements(int ind1, int ind2)
    { _m.mutable_subkeys()->SwapElements(ind1, ind2); }

private:

    CCSUsrMsg_VGUIMenu & _m; 
};

class CCSUsrMsg_VGUIMenu_subkeys_iter
{
public:

    CCSUsrMsg_VGUIMenu_subkeys_iter(CCSUsrMsg_VGUIMenu & msg)
     : _p(msg), _ind(0) { }

    CCSUsrMsg_VGUIMenu_Subkey * next()
    {
        if(_ind == _p.len())
        {
            PyErr_SetObject(PyExc_StopIteration, Py_None);
            boost::python::throw_error_already_set();
        }
        return _p.getitem(_ind++);
    }

private:

    CCSUsrMsg_VGUIMenu_subkeys_proxy _p;
    int _ind;
};

bpl::object CCSUsrMsg_VGUIMenu_subkeys_proxy::iter()
{ return bpl::object(CCSUsrMsg_VGUIMenu_subkeys_iter(_m)); }


CCSUsrMsg_VGUIMenu_Subkey *
CCSUsrMsg_VGUIMenu_subkeys_proxy::getitem(int ind)
{
    if(ind < 0 || ind >= len())
        throw std::range_error("subkeys index range error");

    return _m.mutable_subkeys(ind);
}

CCSUsrMsg_VGUIMenu_Subkey * py_add_subkeys(
    CCSUsrMsg_VGUIMenu & m)
{ return m.add_subkeys(); }


bool py_ParseFromBytes(CCSUsrMsg_VGUIMenu & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_VGUIMenu & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_VGUIMenu & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_VGUIMenu & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_VGUIMenu isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_VGUIMenu_bindings()
{
    bpl::class_<CCSUsrMsg_VGUIMenu> binder("CCSUsrMsg_VGUIMenu");
    binder.def(bpl::init<const CCSUsrMsg_VGUIMenu &>());

    void (CCSUsrMsg_VGUIMenu::*copy_from_ptr)(const CCSUsrMsg_VGUIMenu &) = \
        &CCSUsrMsg_VGUIMenu::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_VGUIMenu::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_VGUIMenu::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_VGUIMenu::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_VGUIMenu::ByteSize);


    void (CCSUsrMsg_VGUIMenu::*set_name_ptr)(const std::string &) = \
        &CCSUsrMsg_VGUIMenu::set_name;

    binder.def("set_name", set_name_ptr);
    binder.def("has_name", &CCSUsrMsg_VGUIMenu::has_name);
    binder.def("clear_name", &CCSUsrMsg_VGUIMenu::clear_name);
    binder.add_property("name",
        bpl::make_function(&CCSUsrMsg_VGUIMenu::name,
            bpl::return_value_policy<bpl::copy_const_reference>()));
    binder.def("has_show", &CCSUsrMsg_VGUIMenu::has_show);
    binder.def("set_show", &CCSUsrMsg_VGUIMenu::set_show);
    binder.def("clear_show", &CCSUsrMsg_VGUIMenu::clear_show);
    binder.add_property("show", &CCSUsrMsg_VGUIMenu::show);


    binder.def("clear_subkeys", &CCSUsrMsg_VGUIMenu::clear_subkeys);
    binder.add_property("subkeys",
        &CCSUsrMsg_VGUIMenu_subkeys_proxy::proxy);

    bpl::class_<CCSUsrMsg_VGUIMenu_subkeys_iter> subkeys_iter_binder(
        "CCSUsrMsg_VGUIMenu_subkeys_iter", bpl::no_init);

    bpl::class_<CCSUsrMsg_VGUIMenu_subkeys_proxy> subkeys_proxy_binder(
        "CCSUsrMsg_VGUIMenu_subkeys_proxy", bpl::no_init);
    subkeys_proxy_binder.def("__len__",
        &CCSUsrMsg_VGUIMenu_subkeys_proxy::len);
    subkeys_proxy_binder.def("__iter__",
        &CCSUsrMsg_VGUIMenu_subkeys_proxy::iter);
    subkeys_proxy_binder.def("SwapElements",
        &CCSUsrMsg_VGUIMenu_subkeys_proxy::SwapElements);


    subkeys_proxy_binder.def("__getitem__",
        &CCSUsrMsg_VGUIMenu_subkeys_proxy::getitem,
        bpl::return_value_policy<bpl::reference_existing_object>());

    // __setitem__ not defined

    binder.def("add_subkeys", &py_add_subkeys,
        bpl::return_value_policy<bpl::reference_existing_object>());

    subkeys_iter_binder.def("next",
        &CCSUsrMsg_VGUIMenu_subkeys_iter::next,
        bpl::return_value_policy<bpl::reference_existing_object>());

;
}
