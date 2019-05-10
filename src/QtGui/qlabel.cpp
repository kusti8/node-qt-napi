#include "qlabel.hpp"

Napi::FunctionReference QLabelWrap::constructor;

QWIDGET_IMPL_FUNCS(QLabel)

Napi::Object QLabelWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QLabel", {
        InstanceMethod("setText", &QLabelWrap::setText),
        QWIDGET_JS_DEFINES(QLabelWrap)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QLabel", func);
    return exports;
}

QLabelWrap::QLabelWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QLabelWrap>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        QWidget *parent = unwrap(info[0]);
        q_ = new QLabelImpl(parent, env);
    }
    else
    {
        QLabelImpl *q_parent = 0;
        q_ = new QLabelImpl(q_parent, env);
    }
}

QLabelWrap::~QLabelWrap()
{
    delete q_;
}

Napi::Value QLabelWrap::setText(const Napi::CallbackInfo &info)
{
    q_->setText(QString::fromStdString(info[0].ToString().Utf8Value()));
    return Napi::Value();
}

// QWidget functions
QWIDGET_BASE_FUNCS(QLabelWrap)