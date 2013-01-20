#include <boost/python.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "public/game/shared/csgo/protobuf/cstrike15_usermessages.pb.h"

namespace bpl = boost::python;


bpl::object py_pos(CCSUsrMsg_HudMsg & msg)
{
    if(msg.has_pos())
    {
        bpl::reference_existing_object::apply<
            const CMsgVector2D * &>::type convert;

        return bpl::object(bpl::handle<>(convert(msg.pos())));
    }
    // return None
    return bpl::object();
}


bpl::object py_clr1(CCSUsrMsg_HudMsg & msg)
{
    if(msg.has_clr1())
    {
        bpl::reference_existing_object::apply<
            const CMsgRGBA * &>::type convert;

        return bpl::object(bpl::handle<>(convert(msg.clr1())));
    }
    // return None
    return bpl::object();
}


bpl::object py_clr2(CCSUsrMsg_HudMsg & msg)
{
    if(msg.has_clr2())
    {
        bpl::reference_existing_object::apply<
            const CMsgRGBA * &>::type convert;

        return bpl::object(bpl::handle<>(convert(msg.clr2())));
    }
    // return None
    return bpl::object();
}

bool py_ParseFromBytes(CCSUsrMsg_HudMsg & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    return msg.ParseFromZeroCopyStream(&input);
}

std::string py_SerializeToBytes(CCSUsrMsg_HudMsg & msg)
{
    std::string result;
    msg.SerializeToString(&result);
    return result;
}

bool py_ParseFromText(CCSUsrMsg_HudMsg & msg, const bpl::str & s)
{
    PyObject *pUTF8 = PyUnicode_AsUTF8String(s.ptr());
    google::protobuf::io::ArrayInputStream input(
        PyBytes_AsString(pUTF8), PyBytes_Size(pUTF8));
    Py_XDECREF(pUTF8);
    
    return google::protobuf::TextFormat::Parse(&input, &msg);
}

std::string py_SerializeToText(CCSUsrMsg_HudMsg & msg)
{
    if(!msg.IsInitialized())
    {
        throw std::runtime_error("CCSUsrMsg_HudMsg isn't initialized");
    }

    std::string result;
    google::protobuf::TextFormat::PrintToString(msg, &result);
    return result;
}

void make_CCSUsrMsg_HudMsg_bindings()
{
    bpl::class_<CCSUsrMsg_HudMsg> binder("CCSUsrMsg_HudMsg");
    binder.def(bpl::init<const CCSUsrMsg_HudMsg &>());

    void (CCSUsrMsg_HudMsg::*copy_from_ptr)(const CCSUsrMsg_HudMsg &) = \
        &CCSUsrMsg_HudMsg::CopyFrom;

    // TODO(johng): My preference would be for __slots__-like behavior
    //   on wrapped Message classes. The mechanics of boost::python
    //   make this difficult.
    //
    // To prevent typos in assignment from causing inadvertant errors
    //  where fields are silently added onto the Python message instance,
    //  I've elected to implement the C++ set_$(field) api for assigment.

    // Common message methods
    binder.def("__str__", &CCSUsrMsg_HudMsg::DebugString);
    binder.def("IsInitialized", &CCSUsrMsg_HudMsg::IsInitialized);
    binder.def("Clear", &CCSUsrMsg_HudMsg::Clear);
    binder.def("CopyFrom", copy_from_ptr);
    binder.def("ParseFromBytes", &py_ParseFromBytes);
    binder.def("SerializeToBytes", &py_SerializeToBytes);
    binder.def("ParseFromText", &py_ParseFromText);
    binder.def("SerializeToText", &py_SerializeToText);
    binder.def("ByteSize", &CCSUsrMsg_HudMsg::ByteSize);

    binder.def("has_channel", &CCSUsrMsg_HudMsg::has_channel);
    binder.def("set_channel", &CCSUsrMsg_HudMsg::set_channel);
    binder.def("clear_channel", &CCSUsrMsg_HudMsg::clear_channel);
    binder.add_property("channel", &CCSUsrMsg_HudMsg::channel);
    binder.def("has_pos", &CCSUsrMsg_HudMsg::has_pos);
    binder.add_property("pos", &py_pos);
    binder.def("mutable_pos", &CCSUsrMsg_HudMsg::mutable_pos,
        bpl::return_value_policy<bpl::reference_existing_object>());
    binder.def("clear_pos", &CCSUsrMsg_HudMsg::clear_pos);
    binder.def("has_clr1", &CCSUsrMsg_HudMsg::has_clr1);
    binder.add_property("clr1", &py_clr1);
    binder.def("mutable_clr1", &CCSUsrMsg_HudMsg::mutable_clr1,
        bpl::return_value_policy<bpl::reference_existing_object>());
    binder.def("clear_clr1", &CCSUsrMsg_HudMsg::clear_clr1);
    binder.def("has_clr2", &CCSUsrMsg_HudMsg::has_clr2);
    binder.add_property("clr2", &py_clr2);
    binder.def("mutable_clr2", &CCSUsrMsg_HudMsg::mutable_clr2,
        bpl::return_value_policy<bpl::reference_existing_object>());
    binder.def("clear_clr2", &CCSUsrMsg_HudMsg::clear_clr2);
    binder.def("has_effect", &CCSUsrMsg_HudMsg::has_effect);
    binder.def("set_effect", &CCSUsrMsg_HudMsg::set_effect);
    binder.def("clear_effect", &CCSUsrMsg_HudMsg::clear_effect);
    binder.add_property("effect", &CCSUsrMsg_HudMsg::effect);
    binder.def("has_fade_in_time", &CCSUsrMsg_HudMsg::has_fade_in_time);
    binder.def("set_fade_in_time", &CCSUsrMsg_HudMsg::set_fade_in_time);
    binder.def("clear_fade_in_time", &CCSUsrMsg_HudMsg::clear_fade_in_time);
    binder.add_property("fade_in_time", &CCSUsrMsg_HudMsg::fade_in_time);
    binder.def("has_fade_out_time", &CCSUsrMsg_HudMsg::has_fade_out_time);
    binder.def("set_fade_out_time", &CCSUsrMsg_HudMsg::set_fade_out_time);
    binder.def("clear_fade_out_time", &CCSUsrMsg_HudMsg::clear_fade_out_time);
    binder.add_property("fade_out_time", &CCSUsrMsg_HudMsg::fade_out_time);
    binder.def("has_hold_time", &CCSUsrMsg_HudMsg::has_hold_time);
    binder.def("set_hold_time", &CCSUsrMsg_HudMsg::set_hold_time);
    binder.def("clear_hold_time", &CCSUsrMsg_HudMsg::clear_hold_time);
    binder.add_property("hold_time", &CCSUsrMsg_HudMsg::hold_time);
    binder.def("has_fx_time", &CCSUsrMsg_HudMsg::has_fx_time);
    binder.def("set_fx_time", &CCSUsrMsg_HudMsg::set_fx_time);
    binder.def("clear_fx_time", &CCSUsrMsg_HudMsg::clear_fx_time);
    binder.add_property("fx_time", &CCSUsrMsg_HudMsg::fx_time);

    void (CCSUsrMsg_HudMsg::*set_text_ptr)(const std::string &) = \
        &CCSUsrMsg_HudMsg::set_text;

    binder.def("set_text", set_text_ptr);
    binder.def("has_text", &CCSUsrMsg_HudMsg::has_text);
    binder.def("clear_text", &CCSUsrMsg_HudMsg::clear_text);
    binder.add_property("text",
        bpl::make_function(&CCSUsrMsg_HudMsg::text,
            bpl::return_value_policy<bpl::copy_const_reference>()));
;
}
