#ifndef QLABELWRAP_H
#define QLABELWRAP_H
#include <QLabel>
#include <napi.h>
#include "qwidget.hpp"
#include "qwidget_macros.hpp"

QWIDGET_IMPL_DEF(QLabel)

#include "../utils/unwrapper.hpp"
class QLabelWrap : public Napi::ObjectWrap<QLabelWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QLabelWrap(const Napi::CallbackInfo &info);
  ~QLabelWrap();

  QLabelImpl *q_;

private:
  static Napi::FunctionReference constructor;

  Napi::Value setText(const Napi::CallbackInfo &info);

  // QWidget Funcs
  QWIDGET_DEFS
};
#endif