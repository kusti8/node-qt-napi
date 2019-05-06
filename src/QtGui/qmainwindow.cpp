#include "qmainwindow.hpp"

Napi::FunctionReference QMainWindowWrap::constructor;

Napi::Object QMainWindowWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QMainWindow", {
        QWIDGET_JS_DEFINES(QMainWindowWrap)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QMainWindow", func);
    return exports;
}

QMainWindowWrap::QMainWindowWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QMainWindowWrap>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        QMainWindowWrap *parent = Napi::ObjectWrap<QMainWindowWrap>::Unwrap(info[0].As<Napi::Object>());
        q_ = new QMainWindowImpl(parent->q_, env);
    }
    else
    {
        QMainWindowImpl *q_parent = 0;
        q_ = new QMainWindowImpl(q_parent, env);
    }
}

QMainWindowWrap::~QMainWindowWrap()
{
    delete q_;
}

// QWidget functions
QWIDGET_BASE_FUNCS(QMainWindowWrap)