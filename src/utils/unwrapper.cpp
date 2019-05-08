#include "unwrapper.hpp"

QWidget *unwrap(Napi::Value object)
{
    std::string constructor_name = object.ToObject().Get("constructor").ToObject().Get("name").ToString().Utf8Value();
    QWidget *parent;
    if (constructor_name == "QMainWindow")
        parent = Napi::ObjectWrap<QMainWindowWrap>::Unwrap(object.ToObject())->q_;
    if (constructor_name == "QWidget")
        parent = Napi::ObjectWrap<QWidgetWrap>::Unwrap(object.ToObject())->q_;

    return parent;
}