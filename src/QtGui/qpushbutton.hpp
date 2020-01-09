#ifndef QPUSHBUTTONWRAP_H
#define QPUSHBUTTONWRAP_H
#include <QPushButton>
#include <QObject>
#include <napi.h>
#include "qwidget.hpp"
#include "qwidget_macros.hpp"
#include "../utils/unwrapper.hpp"
#include <iostream>

QWIDGET_IMPL_DEF(QPushButton)

class QPushButtonWrap;
class SlotHandlerPushButton : public QObject
{

  Q_OBJECT

public:
  SlotHandlerPushButton(QPushButtonWrap *element) : element(element){};
  QPushButtonWrap *element;

public slots:
  void buttonReleasedSlot();
};

class QPushButtonWrap : public Napi::ObjectWrap<QPushButtonWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QPushButtonWrap(const Napi::CallbackInfo &info);
  ~QPushButtonWrap();

  QPushButtonImpl *q_;

  Napi::FunctionReference buttonReleasedCallback_;

private:
  static Napi::FunctionReference constructor;

  Napi::Value setText(const Napi::CallbackInfo &info);
  Napi::Value text(const Napi::CallbackInfo &info);
  Napi::Value buttonReleasedEvent(const Napi::CallbackInfo &info);

  SlotHandlerPushButton slotHandler;

  // QWidget Funcs
  QWIDGET_DEFS
};
#endif