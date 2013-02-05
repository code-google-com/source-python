#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;

 

class CCSUsrMsg_VoiceMask_player_masks_proxy
{
public:

    static CCSUsrMsg_VoiceMask_player_masks_proxy proxy(CCSUsrMsg_VoiceMask & msg)
    { return CCSUsrMsg_VoiceMask_player_masks_proxy(msg); }

    CCSUsrMsg_VoiceMask_player_masks_proxy(CCSUsrMsg_VoiceMask & msg)
      : _m(msg) { }

    int len()
    { return _m.player_masks_size(); }

    CCSUsrMsg_VoiceMask_PlayerMask * getitem(int ind);

    void setitem(unsigned ind, CCSUsrMsg_VoiceMask_PlayerMask *);

    bpl::object iter();

    void SwapElements(int ind1, int ind2)
    { _m.mutable_player_masks()->SwapElements(ind1, ind2); }

private:

    CCSUsrMsg_VoiceMask & _m; 
};

class CCSUsrMsg_VoiceMask_player_masks_iter
{
public:

    CCSUsrMsg_VoiceMask_player_masks_iter(CCSUsrMsg_VoiceMask & msg)
     : _p(msg), _ind(0) { }

    CCSUsrMsg_VoiceMask_PlayerMask * next()
    {
        if(_ind == _p.len())
        {
            PyErr_SetObject(PyExc_StopIteration, Py_None);
            boost::python::throw_error_already_set();
        }
        return _p.getitem(_ind++);
    }

private:

    CCSUsrMsg_VoiceMask_player_masks_proxy _p;
    int _ind;
};

bpl::object CCSUsrMsg_VoiceMask_player_masks_proxy::iter()
{ return bpl::object(CCSUsrMsg_VoiceMask_player_masks_iter(_m)); }


CCSUsrMsg_VoiceMask_PlayerMask *
CCSUsrMsg_VoiceMask_player_masks_proxy::getitem(int ind)
{
    if(ind < 0 || ind >= len())
        throw std::range_error("player_masks index range error");

    return _m.mutable_player_masks(ind);
}

CCSUsrMsg_VoiceMask_PlayerMask * py_add_player_masks(
    CCSUsrMsg_VoiceMask & m)
{ return m.add_player_masks(); }


bool py_ParseFromBytes(CCSUsrMsg_VoiceMask & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_VoiceMask & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_VoiceMask & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_VoiceMask & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_VoiceMask isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_VoiceMask_bindings()
{
    bpl::class_<CCSUsrMsg_VoiceMask, bpl::bases<google::protobuf::Message>> binder("CCSUsrMsg_VoiceMask");
    binder.def(bpl::init<const CCSUsrMsg_VoiceMask &>());

    void (CCSUsrMsg_VoiceMask::*copy_from_ptr)(const CCSUsrMsg_VoiceMask &) = \
        &CCSUsrMsg_VoiceMask::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_VoiceMask::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_VoiceMask::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_VoiceMask::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_VoiceMask::ByteSize);



    binder.def("clear_player_masks", &CCSUsrMsg_VoiceMask::clear_player_masks);
    binder.add_property("player_masks",
        &CCSUsrMsg_VoiceMask_player_masks_proxy::proxy);

    bpl::class_<CCSUsrMsg_VoiceMask_player_masks_iter> player_masks_iter_binder(
        "CCSUsrMsg_VoiceMask_player_masks_iter", bpl::no_init);

    bpl::class_<CCSUsrMsg_VoiceMask_player_masks_proxy> player_masks_proxy_binder(
        "CCSUsrMsg_VoiceMask_player_masks_proxy", bpl::no_init);
    player_masks_proxy_binder.def("__len__",
        &CCSUsrMsg_VoiceMask_player_masks_proxy::len);
    player_masks_proxy_binder.def("__iter__",
        &CCSUsrMsg_VoiceMask_player_masks_proxy::iter);
    player_masks_proxy_binder.def("SwapElements",
        &CCSUsrMsg_VoiceMask_player_masks_proxy::SwapElements);


    player_masks_proxy_binder.def("__getitem__",
        &CCSUsrMsg_VoiceMask_player_masks_proxy::getitem,
        bpl::return_value_policy<bpl::reference_existing_object>());

    // __setitem__ not defined

    binder.def("add_player_masks", &py_add_player_masks,
        bpl::return_value_policy<bpl::reference_existing_object>());

    player_masks_iter_binder.def("next",
        &CCSUsrMsg_VoiceMask_player_masks_iter::next,
        bpl::return_value_policy<bpl::reference_existing_object>());

    binder.def("has_player_mod_enable", &CCSUsrMsg_VoiceMask::has_player_mod_enable);
    binder.def("set_player_mod_enable", &CCSUsrMsg_VoiceMask::set_player_mod_enable);
    binder.def("clear_player_mod_enable", &CCSUsrMsg_VoiceMask::clear_player_mod_enable);
    binder.add_property("player_mod_enable", &CCSUsrMsg_VoiceMask::player_mod_enable);
;
}
