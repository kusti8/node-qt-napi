#ifndef QCOMBOBOXWRAP_H
#define QCOMBOBOXWRAP_H
#include <QComboBox>
#include <QObject>
#include <QString>
#include <napi.h>
#include "qwidget.hpp"
#include "qwidget_macros.hpp"
#include "../utils/unwrapper.hpp"
#include <iostream>

QWIDGET_IMPL_DEF(QComboBox)

class QComboBoxWrap;
class SlotHandlerComboBox : public QObject
{

  Q_OBJECT

public:
  SlotHandlerComboBox(QComboBoxWrap *element) : element(element){};
  QComboBoxWrap *element;

public slots:
  void currentTextChangedSlot(const QString &text);
  void activatedSlot(const QString &text);
};

class QComboBoxWrap : public Napi::ObjectWrap<QComboBoxWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QComboBoxWrap(const Napi::CallbackInfo &info);
  ~QComboBoxWrap();

  QComboBoxImpl *q_;
  Napi::FunctionReference currentTextChangedCallback_;
  Napi::FunctionReference activatedCallback_;

private:
  static Napi::FunctionReference constructor;

  Napi::Value setCurrentText(const Napi::CallbackInfo &info);
  Napi::Value currentText(const Napi::CallbackInfo &info);
  Napi::Value setCurrentIndex(const Napi::CallbackInfo &info);
  Napi::Value currentIndex(const Napi::CallbackInfo &info);
  Napi::Value addItem(const Napi::CallbackInfo &info);
  Napi::Value insertItem(const Napi::CallbackInfo &info);
  Napi::Value removeItem(const Napi::CallbackInfo &info);
  Napi::Value isEditable(const Napi::CallbackInfo &info);
  Napi::Value setEditable(const Napi::CallbackInfo &info);
  Napi::Value currentTextChangedEvent(const Napi::CallbackInfo &info);
  Napi::Value activatedEvent(const Napi::CallbackInfo &info);

  SlotHandlerComboBox slotHandler;

  // QWidget Funcs
  QWIDGET_DEFS
};
#endif