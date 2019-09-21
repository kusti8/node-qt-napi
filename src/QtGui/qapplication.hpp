#ifndef QAPPLICATIONWRAP_H
#define QAPPLICATIONWRAP_H
#include <QApplication>
#include <QObject>
#include <napi.h>
#include <iostream>

class QApplicationWrap;
class SlotHandlerApplication : public QObject
{

  Q_OBJECT

public:
  SlotHandlerApplication(QApplicationWrap *app) : app(app){};
  QApplicationWrap *app;

public slots:
  void aboutToQuitSlot();
};

class QApplicationWrap : public Napi::ObjectWrap<QApplicationWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  QApplicationWrap(const Napi::CallbackInfo &info);
  ~QApplicationWrap();

  QApplication *q_;
  Napi::FunctionReference aboutToQuitCallback_;

private:
  static Napi::FunctionReference constructor;
  Napi::Value exec(const Napi::CallbackInfo &info);
  Napi::Value processEvents(const Napi::CallbackInfo &info);
  Napi::Value sendPostedEvents(const Napi::CallbackInfo &info);
  Napi::Value quit(const Napi::CallbackInfo &info);
  Napi::Value aboutToQuitEvent(const Napi::CallbackInfo &info);
  static int argc_;
  static char **argv_;

  SlotHandlerApplication slotHandler;
};
#endif
