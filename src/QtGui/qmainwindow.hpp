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
  QWIDGET_DEFS
};
#endif