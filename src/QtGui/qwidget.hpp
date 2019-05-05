#ifndef QWIDGETWRAP_H
#define QWIDGETWRAP_H
#include <QWidget>
#include <QMouseEvent>
#include <napi.h>

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

private:
  void paintEvent(QPaintEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
  void keyPressEvent(QKeyEvent *e);
  void keyReleaseEvent(QKeyEvent *e);
};

class QWidgetImpl : public QWidgetBase, public QWidget
{
public:
  QWidgetImpl(QWidgetImpl *parent, Napi::Env env) : QWidgetBase(env), QWidget(parent){};
};

class QWidgetWrap : public Napi::ObjectWrap<QWidgetWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QWidgetWrap(const Napi::CallbackInfo &info);
  ~QWidgetWrap();

  QWidgetImpl *q_;

private:
  static Napi::FunctionReference constructor;

  Napi::Value resize(const Napi::CallbackInfo &info);
  Napi::Value show(const Napi::CallbackInfo &info);
  Napi::Value close(const Napi::CallbackInfo &info);
  Napi::Value size(const Napi::CallbackInfo &info);
  Napi::Value width(const Napi::CallbackInfo &info);
  Napi::Value height(const Napi::CallbackInfo &info);
  Napi::Value objectName(const Napi::CallbackInfo &info);
  Napi::Value setObjectName(const Napi::CallbackInfo &info);
  Napi::Value parent(const Napi::CallbackInfo &info);
  Napi::Value update(const Napi::CallbackInfo &info);
  Napi::Value setMouseTracking(const Napi::CallbackInfo &info);
  Napi::Value hasMouseTracking(const Napi::CallbackInfo &info);
  Napi::Value setFocusPolicy(const Napi::CallbackInfo &info);
  Napi::Value move(const Napi::CallbackInfo &info);
  Napi::Value x(const Napi::CallbackInfo &info);
  Napi::Value y(const Napi::CallbackInfo &info);
  Napi::Value setStyleSheet(const Napi::CallbackInfo &info);

  // // QUIRK
  // // Event binding. These functions bind implemented event handlers above
  // // to the given callbacks. This is necessary as in Qt such handlers
  // // are virtual and we can't dynamically implement them from JS
  // Napi::Value paintEvent(const Napi::CallbackInfo &info);
  // Napi::Value mousePressEvent(const Napi::CallbackInfo &info);
  // Napi::Value mouseReleaseEvent(const Napi::CallbackInfo &info);
  // Napi::Value mouseMoveEvent(const Napi::CallbackInfo &info);
  // Napi::Value keyPressEvent(const Napi::CallbackInfo &info);
  // Napi::Value keyReleaseEvent(const Napi::CallbackInfo &info);
};
#endif