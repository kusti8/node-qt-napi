#include "qwidget.hpp"

Napi::FunctionReference QWidgetWrap::constructor;

QWIDGET_IMPL_FUNCS(QWidget)

Napi::Object QWidgetWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QWidget", {
        QWIDGET_JS_DEFINES(QWidgetWrap)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QWidget", func);
    return exports;
}

QWidgetWrap::QWidgetWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QWidgetWrap>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        QWidget *parent = unwrap(info[0]);
        q_ = new QWidgetImpl(parent, env);
    }
    else
    {
        QWidgetImpl *q_parent = 0;
        q_ = new QWidgetImpl(q_parent, env);
    }
}

QWidgetWrap::~QWidgetWrap()
{
    q_ = NULL;
}

// Qt functions
QWIDGET_BASE_FUNCS(QWidgetWrap)