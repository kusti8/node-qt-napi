#ifndef QPIXMAPWRAP_H
#define QPIXMAPWRAP_H
#include <QPixmap>
#include <QPainter>
#include <napi.h>
#include <iostream>
#include <math.h>

#include "../utils/unwrapper.hpp"
class QPixmapWrap : public Napi::ObjectWrap<QPixmapWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QPixmapWrap(const Napi::CallbackInfo &info);
  ~QPixmapWrap();

  QPixmap *q_;
  QPixmap q2_;
  QPixmap *q_orig;

private:
  static Napi::FunctionReference constructor;

  Napi::Value load(const Napi::CallbackInfo &info);
  Napi::Value loadFromData(const Napi::CallbackInfo &info);
  Napi::Value scaled(const Napi::CallbackInfo &info);
  Napi::Value scaledToWidth(const Napi::CallbackInfo &info);
  Napi::Value scaledToHeight(const Napi::CallbackInfo &info);
  Napi::Value scaledTile(const Napi::CallbackInfo &info);
  Napi::Value height(const Napi::CallbackInfo &info);
  Napi::Value width(const Napi::CallbackInfo &info);
  Napi::Value isNull(const Napi::CallbackInfo &info);
};
#endif