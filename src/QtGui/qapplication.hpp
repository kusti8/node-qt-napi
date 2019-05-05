#ifndef QAPPLICATIONWRAP_H
#define QAPPLICATIONWRAP_H
#include <QApplication>
#include <napi.h>

class QApplicationWrap : public Napi::ObjectWrap<QApplicationWrap>
{
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    QApplicationWrap(const Napi::CallbackInfo &info);
    ~QApplicationWrap();

  private:
    static Napi::FunctionReference constructor;
    Napi::Value exec(const Napi::CallbackInfo &info);
    Napi::Value processEvents(const Napi::CallbackInfo &info);

    QApplication *q_;
    static int argc_;
    static char **argv_;
};
#endif