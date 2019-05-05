#include "qapplication.hpp"

Napi::FunctionReference QApplicationWrap::constructor;

int QApplicationWrap::argc_ = 0;
char **QApplicationWrap::argv_ = NULL;

Napi::Object QApplicationWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "QApplication", {InstanceMethod("exec", &QApplicationWrap::exec), InstanceMethod("processEvents", &QApplicationWrap::processEvents)});

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QApplication", func);
    return exports;
}

QApplicationWrap::QApplicationWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QApplicationWrap>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    q_ = new QApplication(argc_, argv_);
}

QApplicationWrap::~QApplicationWrap()
{
    delete q_;
}

Napi::Value QApplicationWrap::exec(const Napi::CallbackInfo &info)
{
    q_->exec();
    return Napi::Value();
}

Napi::Value QApplicationWrap::processEvents(const Napi::CallbackInfo &info)
{
    q_->processEvents();
    return Napi::Value();
}