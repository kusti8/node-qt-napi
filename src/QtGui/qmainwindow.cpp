#include "qmainwindow.hpp"

Napi::FunctionReference QMainWindowWrap::constructor;

QWIDGET_IMPL_FUNCS(QMainWindow)

Napi::Object QMainWindowWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QMainWindow", {
        InstanceMethod("getClosed", &QMainWindowWrap::getClosed),
        InstanceMethod("showFullScreen", &QMainWindowWrap::showFullScreen),
        InstanceMethod("showNormal", &QMainWindowWrap::showNormal),
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
        QWidget *parent = unwrap(info[0]);
        q_ = new QMainWindowImpl(parent, env);
    }
    else
    {
        QMainWindowImpl *q_parent = 0;
        q_ = new QMainWindowImpl(q_parent, env);
    }
}

QMainWindowWrap::~QMainWindowWrap()
{
    q_ = NULL;
}

Napi::Value QMainWindowWrap::getClosed(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Boolean::New(env, q_->closed);
}

Napi::Value QMainWindowWrap::showFullScreen(const Napi::CallbackInfo &info)
{
    q_->showFullScreen();
    return Napi::Value();
}

Napi::Value QMainWindowWrap::showNormal(const Napi::CallbackInfo &info)
{
    q_->showNormal();
    return Napi::Value();
}

// QWidget functions
QWIDGET_BASE_FUNCS(QMainWindowWrap)