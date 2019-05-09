#ifndef QWIDGETWRAP_H
#define QWIDGETWRAP_H
#include <QWidget>
#include <QMouseEvent>
#include <napi.h>
#include <iostream>
#include "qwidget_macros.hpp"

QWIDGET_IMPL_DEF(QWidget)

#include "../utils/unwrapper.hpp"
class QWidgetWrap : public Napi::ObjectWrap<QWidgetWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QWidgetWrap(const Napi::CallbackInfo &info);
  ~QWidgetWrap();

  QWidgetImpl *q_;

private:
  static Napi::FunctionReference constructor;

  QWIDGET_DEFS
};

#endif