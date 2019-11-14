#include "qpixmap.hpp"

Napi::FunctionReference QPixmapWrap::constructor;

Napi::Object QPixmapWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QLabel", {
        InstanceMethod("load", &QPixmapWrap::load),
        InstanceMethod("loadFromData", &QPixmapWrap::loadFromData),
        InstanceMethod("scaled", &QPixmapWrap::scaled),
        InstanceMethod("scaledToWidth", &QPixmapWrap::scaledToWidth),
        InstanceMethod("scaledToHeight", &QPixmapWrap::scaledToHeight),
        InstanceMethod("scaledTile", &QPixmapWrap::scaledTile),
        InstanceMethod("height", &QPixmapWrap::height),
        InstanceMethod("width", &QPixmapWrap::width),
        InstanceMethod("isNull", &QPixmapWrap::isNull)
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
    q_orig = new QPixmap();
}

QPixmapWrap::~QPixmapWrap()
{
    q_ = NULL;
}

Napi::Value QPixmapWrap::load(const Napi::CallbackInfo &info)
{
    q_->load(QString::fromStdString(info[0].ToString().Utf8Value()));
    q_orig->load(QString::fromStdString(info[0].ToString().Utf8Value()));
    return Napi::Value();
}

Napi::Value QPixmapWrap::loadFromData(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Buffer<unsigned char> buf = info[0].As<Napi::Buffer<unsigned char>>();

    q_->loadFromData(buf.Data(), buf.Length());
    q_orig->loadFromData(buf.Data(), buf.Length());

    return Napi::Value();
}

Napi::Value QPixmapWrap::scaled(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q2_ = q_orig->scaled(info[0].ToNumber().Int32Value(), info[1].ToNumber().Int32Value(), static_cast<Qt::AspectRatioMode>(info[2].ToNumber().Int32Value()));
    q_ = &q2_;

    return Napi::Value();
}

Napi::Value QPixmapWrap::scaledToWidth(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q2_ = q_orig->scaledToWidth(info[0].ToNumber().Int32Value());
    q_ = &q2_;

    return Napi::Value();
}

Napi::Value QPixmapWrap::scaledToHeight(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q2_ = q_orig->scaledToHeight(info[0].ToNumber().Int32Value());
    q_ = &q2_;

    return Napi::Value();
}

Napi::Value QPixmapWrap::scaledTile(const Napi::CallbackInfo &info)
{
    int image_width = q_orig->width();
    int image_height = q_orig->height();

    int wanted_width = info[0].ToNumber().Int32Value();
    int wanted_height = info[1].ToNumber().Int32Value();

    q2_ = QPixmap(wanted_width, wanted_height);

    int hori_count = ceil((float)wanted_width / (float)image_width);
    int vert_count = ceil((float)wanted_height / (float)image_height);

    for (int h = 0; h < hori_count; h++)
    {
        for (int v = 0; v < vert_count; v++)
        {
            QPainter painter(&q2_);
            painter.drawPixmap(QRectF(image_width * h, image_height * v, image_width, image_height), *q_orig,
                               QRectF(0, 0, image_width, image_height));
        }
    }

    q_ = &q2_;

    return Napi::Value();
}

Napi::Value QPixmapWrap::height(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, q_->height());
}

Napi::Value QPixmapWrap::width(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, q_->width());
}

Napi::Value QPixmapWrap::isNull(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Boolean::New(env, q_->isNull());
}