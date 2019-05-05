#include "qmainwindow.hpp"

Napi::FunctionReference QMainWindowWrap::constructor;

Napi::Object QMainWindowWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QMainWindow", {
        InstanceMethod("resize", &QMainWindowWrap::resize),
        InstanceMethod("show", &QMainWindowWrap::show),
        InstanceMethod("close", &QMainWindowWrap::close),
        InstanceMethod("size", &QMainWindowWrap::size),
        InstanceMethod("width", &QMainWindowWrap::width),
        InstanceMethod("height", &QMainWindowWrap::height),
        InstanceMethod("objectName", &QMainWindowWrap::objectName),
        InstanceMethod("setObjectName", &QMainWindowWrap::setObjectName),
        InstanceMethod("parent", &QMainWindowWrap::parent),
        InstanceMethod("update", &QMainWindowWrap::update),
        InstanceMethod("setMouseTracking", &QMainWindowWrap::setMouseTracking),
        InstanceMethod("hasMouseTracking", &QMainWindowWrap::hasMouseTracking),
        InstanceMethod("setFocusPolicy", &QMainWindowWrap::setFocusPolicy),
        InstanceMethod("move", &QMainWindowWrap::move),
        InstanceMethod("x", &QMainWindowWrap::x),
        InstanceMethod("y", &QMainWindowWrap::y)
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

Napi::Value QMainWindowWrap::resize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->resize(info[0].ToNumber().Int32Value(), info[1].ToNumber().Int32Value());

    return Napi::Value();
}

Napi::Value QMainWindowWrap::show(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->show();

    return Napi::Value();
}

Napi::Value QMainWindowWrap::close(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->close();

    return Napi::Value();
}

Napi::Value QMainWindowWrap::size(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // TODO: q_->size();

    return Napi::Value();
}

Napi::Value QMainWindowWrap::width(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, q_->width());
}

Napi::Value QMainWindowWrap::height(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, q_->height());
}

Napi::Value QMainWindowWrap::objectName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::String::New(env, q_->objectName().toStdString());
}

Napi::Value QMainWindowWrap::setObjectName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->setObjectName(QString::fromStdString(info[0].ToString().Utf8Value()));

    return Napi::Value();
}

Napi::Value QMainWindowWrap::parent(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::String::New(env, q_->parent()->objectName().toStdString());
}

Napi::Value QMainWindowWrap::update(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->update();

    return Napi::Value();
}

Napi::Value QMainWindowWrap::setMouseTracking(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->setMouseTracking(info[0].ToBoolean().Value());

    return Napi::Value();
}

Napi::Value QMainWindowWrap::hasMouseTracking(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Boolean::New(env, q_->hasMouseTracking());
}

Napi::Value QMainWindowWrap::setFocusPolicy(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->setFocusPolicy((Qt::FocusPolicy)(info[0].ToNumber().Int32Value()));

    return Napi::Value();
}

Napi::Value QMainWindowWrap::move(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->move(info[0].ToNumber().Int32Value(), info[1].ToNumber().Int32Value());

    return Napi::Value();
}

Napi::Value QMainWindowWrap::x(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, q_->x());
}

Napi::Value QMainWindowWrap::y(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, q_->y());
}