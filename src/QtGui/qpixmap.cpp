#include "qpixmap.hpp"

Napi::FunctionReference QPixmapWrap::constructor;

Napi::Object QPixmapWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QLabel", {
        InstanceMethod("load", &QPixmapWrap::load),
        InstanceMethod("loadFromData", &QPixmapWrap::loadFromData)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QPixmap", func);
    return exports;
}

QPixmapWrap::QPixmapWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QPixmapWrap>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_ = new QPixmap();
}

QPixmapWrap::~QPixmapWrap()
{
    q_ = NULL;
}

Napi::Value QPixmapWrap::load(const Napi::CallbackInfo &info)
{
    q_->load(QString::fromStdString(info[0].ToString().Utf8Value()));
    return Napi::Value();
}

Napi::Value QPixmapWrap::loadFromData(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Buffer<unsigned char> buf = info[0].As<Napi::Buffer<unsigned char>>();

    q_->loadFromData(buf.Data(), buf.Length());

    return Napi::Value();
}