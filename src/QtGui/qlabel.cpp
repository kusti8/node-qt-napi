#include "qlabel.hpp"

Napi::FunctionReference QLabelWrap::constructor;

QWIDGET_IMPL_FUNCS(QLabel)

Napi::Object QLabelWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QLabel", {
        InstanceMethod("setText", &QLabelWrap::setText),
        InstanceMethod("text", &QLabelWrap::text),
        InstanceMethod("setPixmap", &QLabelWrap::setPixmap),
        InstanceMethod("setScaledContents", &QLabelWrap::setScaledContents),
        InstanceMethod("setAlignment", &QLabelWrap::setAlignment),
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
    q_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

QLabelWrap::~QLabelWrap()
{
    q_ = NULL;
}

Napi::Value QLabelWrap::setText(const Napi::CallbackInfo &info)
{
    q_->setText(QString::fromStdString(info[0].ToString().Utf8Value()));
    return Napi::Value();
}

Napi::Value QLabelWrap::text(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::String::New(env, q_->text().toStdString());
}

Napi::Value QLabelWrap::setPixmap(const Napi::CallbackInfo &info)
{
    QPixmap *p = Napi::ObjectWrap<QPixmapWrap>::Unwrap(info[0].ToObject())->q_;
    q_->setPixmap(*p);
    return Napi::Value();
}

Napi::Value QLabelWrap::setScaledContents(const Napi::CallbackInfo &info)
{
    q_->setScaledContents(info[0].ToBoolean().Value());
    return Napi::Value();
}

Napi::Value QLabelWrap::setAlignment(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->setAlignment(static_cast<Qt::Alignment>(info[0].ToNumber().Int32Value()));

    return Napi::Value();
}

// QWidget functions
QWIDGET_BASE_FUNCS(QLabelWrap)