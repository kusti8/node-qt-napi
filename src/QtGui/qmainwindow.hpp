#ifndef QMAINWINDOWWRAP_H
#define QMAINWINDOWWRAP_H
#include <QMainWindow>
#include <napi.h>
#include "qwidget.hpp"
#include "qwidget_macros.hpp"

QWIDGET_IMPL_DEF(QMainWindow)

#include "../utils/unwrapper.hpp"
class QMainWindowWrap : public Napi::ObjectWrap<QMainWindowWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QMainWindowWrap(const Napi::CallbackInfo &info);
  ~QMainWindowWrap();

  QMainWindowImpl *q_;

private:
  static Napi::FunctionReference constructor;

  Napi::Value getClosed(const Napi::CallbackInfo &info);

  // QWidget Funcs
  QWIDGET_DEFS
};
#endif