#ifndef QPLAINTEXTEDITWRAP_H
#define QPLAINTEXTEDITWRAP_H
#include <QPlainTextEdit>
#include <QObject>
#include <QString>
#include <napi.h>
#include "qwidget.hpp"
#include "qwidget_macros.hpp"
#include "../utils/unwrapper.hpp"
#include <iostream>

QWIDGET_IMPL_DEF(QPlainTextEdit)

class QPlainTextEditWrap;
class SlotHandlerPlainTextEdit : public QObject
{

  Q_OBJECT

public:
  SlotHandlerPlainTextEdit(QPlainTextEditWrap *element) : element(element){};
  QPlainTextEditWrap *element;

public slots:
  void textChangedSlot();
};

class QPlainTextEditWrap : public Napi::ObjectWrap<QPlainTextEditWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QPlainTextEditWrap(const Napi::CallbackInfo &info);
  ~QPlainTextEditWrap();

  QPlainTextEditImpl *q_;
  Napi::FunctionReference textChangedCallback_;

private:
  static Napi::FunctionReference constructor;

  Napi::Value setText(const Napi::CallbackInfo &info);
  Napi::Value text(const Napi::CallbackInfo &info);
  Napi::Value textChangedEvent(const Napi::CallbackInfo &info);

  SlotHandlerPlainTextEdit slotHandler;

  // QWidget Funcs
  QWIDGET_DEFS
};
#endif