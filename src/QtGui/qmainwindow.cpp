#include "qmainwindow.hpp"

Napi::FunctionReference QMainWindowWrap::constructor;

QMainWindowImpl::QMainWindowImpl(QWidget *parent, Napi::Env env) : QMainWindow(parent), env(env)
{
    // Initialize callbacks as boolean values so we can test if the callback
    // has been set via ->IsFunction() below
    paintEventCallback_ = Napi::Boolean::New(env, false);
    mousePressCallback_ = Napi::Boolean::New(env, false);
    mouseReleaseCallback_ = Napi::Boolean::New(env, false);
    mouseMoveCallback_ = Napi::Boolean::New(env, false);
    keyPressCallback_ = Napi::Boolean::New(env, false);
    keyReleaseCallback_ = Napi::Boolean::New(env, false);
}

void QMainWindowImpl::paintEvent(QPaintEvent *e)
{

    if (!paintEventCallback_.IsFunction())
        return;

    std::vector<napi_value> argv = {};
    Napi::Function cb = paintEventCallback_.As<Napi::Function>();

    cb.Call(argv);
}

void QMainWindowImpl::mousePressEvent(QMouseEvent *e)
{
    e->ignore(); // ensures event bubbles up

    if (!mousePressCallback_.IsFunction())
        return;

    // std::vector<napi_value> argv = {
    //     QMouseEventWrap::NewInstance(*e)};
    std::vector<napi_value> argv = {};
    Napi::Function cb = mousePressCallback_.As<Napi::Function>();

    cb.Call(argv);
}

void QMainWindowImpl::mouseReleaseEvent(QMouseEvent *e)
{
    e->ignore(); // ensures event bubbles up

    if (!mouseReleaseCallback_.IsFunction())
        return;

    // std::vector<napi_value> argv = {
    //     QMouseEventWrap::NewInstance(*e)};
    std::vector<napi_value> argv = {};
    Napi::Function cb = mouseReleaseCallback_.As<Napi::Function>();

    cb.Call(argv);
}

void QMainWindowImpl::mouseMoveEvent(QMouseEvent *e)
{
    e->ignore(); // ensures event bubbles up

    if (!mouseMoveCallback_.IsFunction())
        return;

    // std::vector<napi_value> argv = {
    //     QMouseEventWrap::NewInstance(*e)};
    std::vector<napi_value> argv = {};
    Napi::Function cb = mouseMoveCallback_.As<Napi::Function>();

    cb.Call(argv);
}

void QMainWindowImpl::keyPressEvent(QKeyEvent *e)
{
    e->ignore(); // ensures event bubbles up

    if (!keyPressCallback_.IsFunction())
        return;

    // std::vector<napi_value> argv = {
    //     QKeyEventWrap::NewInstance(*e)};
    std::vector<napi_value> argv = {};
    Napi::Function cb = keyPressCallback_.As<Napi::Function>();

    cb.Call(argv);
}

void QMainWindowImpl::keyReleaseEvent(QKeyEvent *e)
{
    e->ignore(); // ensures event bubbles up

    if (!keyReleaseCallback_.IsFunction())
        return;

    // TODO:
    // std::vector<napi_value> argv = {
    //     QKeyEventWrap::NewInstance(*e)};
    std::vector<napi_value> argv = {};
    Napi::Function cb = keyReleaseCallback_.As<Napi::Function>();

    cb.Call(argv);
}

void QMainWindowImpl::resizeEvent(QResizeEvent *e)
{
    if (resizeCallback_.IsEmpty())
        return;

    resizeCallback_.Call({Napi::Number::New(env, e->size().width()),
                          Napi::Number::New(env, e->size().height())});
}

Napi::Object QMainWindowWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QMainWindow", {
        QWIDGET_JS_DEFINES(QMainWindowWrap)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QMainWindow", func);
    return exports;
}

QMainWindowWrap::QMainWindowWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QMainWindowWrap>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        QMainWindowWrap *parent = Napi::ObjectWrap<QMainWindowWrap>::Unwrap(info[0].As<Napi::Object>());
        q_ = new QMainWindowImpl(parent->q_, env);
    }
    else
    {
        QMainWindowImpl *q_parent = 0;
        q_ = new QMainWindowImpl(q_parent, env);
    }
}

QMainWindowWrap::~QMainWindowWrap()
{
    delete q_;
}

// QWidget functions
QWIDGET_BASE_FUNCS(QMainWindowWrap)