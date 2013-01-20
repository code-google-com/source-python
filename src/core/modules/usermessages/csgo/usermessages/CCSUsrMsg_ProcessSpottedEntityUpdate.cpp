#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

 

class CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy
{
public:

    static CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy proxy(CCSUsrMsg_ProcessSpottedEntityUpdate & msg)
    { return CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy(msg); }

    CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy(CCSUsrMsg_ProcessSpottedEntityUpdate & msg)
      : _m(msg) { }

    int len()
    { return _m.entity_updates_size(); }

    CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate * getitem(int ind);

    void setitem(unsigned ind, CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate *);

    bpl::object iter();

    void SwapElements(int ind1, int ind2)
    { _m.mutable_entity_updates()->SwapElements(ind1, ind2); }

private:

    CCSUsrMsg_ProcessSpottedEntityUpdate & _m; 
};

class CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_iter
{
public:

    CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_iter(CCSUsrMsg_ProcessSpottedEntityUpdate & msg)
     : _p(msg), _ind(0) { }

    CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate * next()
    {
        if(_ind == _p.len())
        {
            PyErr_SetObject(PyExc_StopIteration, Py_None);
            boost::python::throw_error_already_set();
        }
        return _p.getitem(_ind++);
    }

private:

    CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy _p;
    int _ind;
};

bpl::object CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy::iter()
{ return bpl::object(CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_iter(_m)); }


CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate *
CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy::getitem(int ind)
{
    if(ind < 0 || ind >= len())
        throw std::range_error("entity_updates index range error");

    return _m.mutable_entity_updates(ind);
}

CCSUsrMsg_ProcessSpottedEntityUpdate_SpottedEntityUpdate * py_add_entity_updates(
    CCSUsrMsg_ProcessSpottedEntityUpdate & m)
{ return m.add_entity_updates(); }


bool py_ParseFromBytes(CCSUsrMsg_ProcessSpottedEntityUpdate & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_ProcessSpottedEntityUpdate & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_ProcessSpottedEntityUpdate & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_ProcessSpottedEntityUpdate & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_ProcessSpottedEntityUpdate isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_ProcessSpottedEntityUpdate_bindings()
{
    bpl::class_<CCSUsrMsg_ProcessSpottedEntityUpdate> binder("CCSUsrMsg_ProcessSpottedEntityUpdate");
    binder.def(bpl::init<const CCSUsrMsg_ProcessSpottedEntityUpdate &>());

    void (CCSUsrMsg_ProcessSpottedEntityUpdate::*copy_from_ptr)(const CCSUsrMsg_ProcessSpottedEntityUpdate &) = \
        &CCSUsrMsg_ProcessSpottedEntityUpdate::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_ProcessSpottedEntityUpdate::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_ProcessSpottedEntityUpdate::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_ProcessSpottedEntityUpdate::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_ProcessSpottedEntityUpdate::ByteSize);

    binder.def("has_new_update", &CCSUsrMsg_ProcessSpottedEntityUpdate::has_new_update);
    binder.def("set_new_update", &CCSUsrMsg_ProcessSpottedEntityUpdate::set_new_update);
    binder.def("clear_new_update", &CCSUsrMsg_ProcessSpottedEntityUpdate::clear_new_update);
    binder.add_property("new_update", &CCSUsrMsg_ProcessSpottedEntityUpdate::new_update);


    binder.def("clear_entity_updates", &CCSUsrMsg_ProcessSpottedEntityUpdate::clear_entity_updates);
    binder.add_property("entity_updates",
        &CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy::proxy);

    bpl::class_<CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_iter> entity_updates_iter_binder(
        "CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_iter", bpl::no_init);

    bpl::class_<CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy> entity_updates_proxy_binder(
        "CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy", bpl::no_init);
    entity_updates_proxy_binder.def("__len__",
        &CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy::len);
    entity_updates_proxy_binder.def("__iter__",
        &CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy::iter);
    entity_updates_proxy_binder.def("SwapElements",
        &CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy::SwapElements);


    entity_updates_proxy_binder.def("__getitem__",
        &CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_proxy::getitem,
        bpl::return_value_policy<bpl::reference_existing_object>());

    // __setitem__ not defined

    binder.def("add_entity_updates", &py_add_entity_updates,
        bpl::return_value_policy<bpl::reference_existing_object>());

    entity_updates_iter_binder.def("next",
        &CCSUsrMsg_ProcessSpottedEntityUpdate_entity_updates_iter::next,
        bpl::return_value_policy<bpl::reference_existing_object>());

;
}
