#include "unwrapper.hpp"

QWidget *unwrap(Napi::Value object)
{
    std::string constructor_name = object.ToObject().Get("constructor").ToObject().Get("name").ToString().Utf8Value();

    if (constructor_name == "QMainWindow")
        return Napi::ObjectWrap<QMainWindowWrap>::Unwrap(object.ToObject())->q_;
    if (constructor_name == "QWidget")
        return Napi::ObjectWrap<QWidgetWrap>::Unwrap(object.ToObject())->q_;
    if (constructor_name == "QLabel")
        return Napi::ObjectWrap<QLabelWrap>::Unwrap(object.ToObject())->q_;
    if (constructor_name == "QLineEdit")
        return Napi::ObjectWrap<QLineEditWrap>::Unwrap(object.ToObject())->q_;
    return NULL;
}