#ifndef QMAINWINDOWWRAP_H
#define QMAINWINDOWWRAP_H
#include <QMainWindow>
#include <napi.h>
#include "qwidget.hpp"

//
// QMainWindowImpl()
// Extends QWidget to implement virtual methods from QWidget
//
class QMainWindowImpl : public QWidgetBase, public QMainWindow
{
public:
  QMainWindowImpl(QMainWindowImpl *parent, Napi::Env env) : QWidgetBase(env), QMainWindow(parent){};
};

class QMainWindowWrap : public Napi::ObjectWrap<QMainWindowWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QMainWindowWrap(const Napi::CallbackInfo &info);
  ~QMainWindowWrap();

  QMainWindowImpl *q_;

private:
  static Napi::FunctionReference constructor;

  // QWidget Funcs
  Napi::Value resize(const Napi::CallbackInfo &info);
  Napi::Value show(const Napi::CallbackInfo &info);
  Napi::Value close(const Napi::CallbackInfo &info);
  Napi::Value size(const Napi::CallbackInfo &info);
  Napi::Value width(const Napi::CallbackInfo &info);
  Napi::Value height(const Napi::CallbackInfo &info);
  Napi::Value objectName(const Napi::CallbackInfo &info);
  Napi::Value setObjectName(const Napi::CallbackInfo &info);
  Napi::Value parent(const Napi::CallbackInfo &info);
  Napi::Value update(const Napi::CallbackInfo &info);
  Napi::Value setMouseTracking(const Napi::CallbackInfo &info);
  Napi::Value hasMouseTracking(const Napi::CallbackInfo &info);
  Napi::Value setFocusPolicy(const Napi::CallbackInfo &info);
  Napi::Value move(const Napi::CallbackInfo &info);
  Napi::Value x(const Napi::CallbackInfo &info);
  Napi::Value y(const Napi::CallbackInfo &info);
};
#endif