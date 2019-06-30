#ifndef QPIXMAPWRAP_H
#define QPIXMAPWRAP_H
#include <QPixmap>
#include <napi.h>
#include <iostream>

#include "../utils/unwrapper.hpp"
class QPixmapWrap : public Napi::ObjectWrap<QPixmapWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QPixmapWrap(const Napi::CallbackInfo &info);
  ~QPixmapWrap();

  QPixmap *q_;

private:
  static Napi::FunctionReference constructor;

  Napi::Value load(const Napi::CallbackInfo &info);
  Napi::Value loadFromData(const Napi::CallbackInfo &info);
};
#endif