#ifndef QLINEEDITWRAP_H
#define QLINEEDITWRAP_H
#include <QLineEdit>
#include <QObject>
#include <QString>
#include <napi.h>
#include "qwidget.hpp"
#include "qwidget_macros.hpp"
#include "../utils/unwrapper.hpp"
#include <iostream>

QWIDGET_IMPL_DEF(QLineEdit)

class QLineEditWrap;
class SlotHandlerLineEdit : public QObject
{

  Q_OBJECT

public:
  SlotHandlerLineEdit(QLineEditWrap *element) : element(element){};
  QLineEditWrap *element;

public slots:
  void textChangedSlot(const QString &text);
};

class QLineEditWrap : public Napi::ObjectWrap<QLineEditWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QLineEditWrap(const Napi::CallbackInfo &info);
  ~QLineEditWrap();

  QLineEditImpl *q_;
  Napi::FunctionReference textChangedCallback_;

private:
  static Napi::FunctionReference constructor;

  Napi::Value setText(const Napi::CallbackInfo &info);
  Napi::Value text(const Napi::CallbackInfo &info);
  Napi::Value setAlignment(const Napi::CallbackInfo &info);
  Napi::Value textChangedEvent(const Napi::CallbackInfo &info);

  SlotHandlerLineEdit slotHandler;

  // QWidget Funcs
  QWIDGET_DEFS
};
#endif