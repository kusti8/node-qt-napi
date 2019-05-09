#ifndef QWIDGETWRAP_H
#define QWIDGETWRAP_H
#include <QWidget>
#include <QMouseEvent>
#include <napi.h>
#include <iostream>
#include "qwidget_macros.hpp"

//
// QWidgetImpl()
// Extends QWidget to implement virtual methods from QWidget
//
class QWidgetBase
{
public:
  QWidgetBase(Napi::Env env);
  ~QWidgetBase();
  Napi::Value paintEventCallback_;
  Napi::Value mousePressCallback_;
  Napi::Value mouseReleaseCallback_;
  Napi::Value mouseMoveCallback_;
  Napi::Value keyPressCallback_;
  Napi::Value keyReleaseCallback_;
  Napi::FunctionReference resizeCallback_;

  Napi::Env env;

private:
  void paintEvent(QPaintEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
  void resizeEvent(QResizeEvent *e);
};

class QWidgetImpl : public QWidget, public QWidgetBase
{
public:
  QWidgetImpl(QWidget *parent, Napi::Env env) : QWidget(parent), QWidgetBase(env){};
};

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