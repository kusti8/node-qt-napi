#include "qwidget.hpp"

Napi::FunctionReference QWidgetWrap::constructor;

QWidgetBase::QWidgetBase(Napi::Env env) : env(env)
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

QWidgetBase::~QWidgetBase()
{
}

void QWidgetBase::paintEvent(QPaintEvent *e)
{

    if (!paintEventCallback_.IsFunction())
        return;

    std::vector<napi_value> argv = {};
    Napi::Function cb = paintEventCallback_.As<Napi::Function>();

    cb.Call(argv);
}

void QWidgetBase::mousePressEvent(QMouseEvent *e)
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

void QWidgetBase::mouseReleaseEvent(QMouseEvent *e)
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

void QWidgetBase::mouseMoveEvent(QMouseEvent *e)
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

void QWidgetBase::keyPressEvent(QKeyEvent *e)
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

void QWidgetBase::keyReleaseEvent(QKeyEvent *e)
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

void QWidgetBase::resizeEvent(QResizeEvent *e)
{
    if (resizeCallback_.IsEmpty())
        return;

    resizeCallback_.Call({Napi::Number::New(env, e->size().width()),
                          Napi::Number::New(env, e->size().height())});
}

Napi::Object QWidgetWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QWidget", {
        QWIDGET_JS_DEFINES(QWidgetWrap)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QWidget", func);
    return exports;
}

QWidgetWrap::QWidgetWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QWidgetWrap>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        QWidget *parent = unwrap(info[0]);
        q_ = new QWidgetImpl(parent, env);
    }
    else
    {
        QWidgetImpl *q_parent = 0;
        q_ = new QWidgetImpl(q_parent, env);
    }
}

QWidgetWrap::~QWidgetWrap()
{
    delete q_;
}

// Qt functions
QWIDGET_BASE_FUNCS(QWidgetWrap)