#include "qwidget.hpp"

Napi::FunctionReference QWidgetWrap::constructor;

QWidgetBase::QWidgetBase(Napi::Env env)
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

Napi::Object QWidgetWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QWidget", {
        InstanceMethod("resize", &QWidgetWrap::resize),
        InstanceMethod("show", &QWidgetWrap::show),
        InstanceMethod("close", &QWidgetWrap::close),
        InstanceMethod("size", &QWidgetWrap::size),
        InstanceMethod("width", &QWidgetWrap::width),
        InstanceMethod("height", &QWidgetWrap::height),
        InstanceMethod("objectName", &QWidgetWrap::objectName),
        InstanceMethod("setObjectName", &QWidgetWrap::setObjectName),
        InstanceMethod("parent", &QWidgetWrap::parent),
        InstanceMethod("update", &QWidgetWrap::update),
        InstanceMethod("setMouseTracking", &QWidgetWrap::setMouseTracking),
        InstanceMethod("hasMouseTracking", &QWidgetWrap::hasMouseTracking),
        InstanceMethod("setFocusPolicy", &QWidgetWrap::setFocusPolicy),
        InstanceMethod("move", &QWidgetWrap::move),
        InstanceMethod("x", &QWidgetWrap::x),
        InstanceMethod("y", &QWidgetWrap::y)
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
        QWidgetWrap *parent = Napi::ObjectWrap<QWidgetWrap>::Unwrap(info[0].As<Napi::Object>());
        q_ = new QWidgetImpl(parent->q_, env);
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

Napi::Value QWidgetWrap::resize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->resize(info[0].ToNumber().Int32Value(), info[1].ToNumber().Int32Value());

    return Napi::Value();
}

Napi::Value QWidgetWrap::show(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->show();

    return Napi::Value();
}

Napi::Value QWidgetWrap::close(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->close();

    return Napi::Value();
}

Napi::Value QWidgetWrap::size(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    // TODO: q_->size();

    return Napi::Value();
}

Napi::Value QWidgetWrap::width(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, q_->width());
}

Napi::Value QWidgetWrap::height(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, q_->height());
}

Napi::Value QWidgetWrap::objectName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::String::New(env, q_->objectName().toStdString());
}

Napi::Value QWidgetWrap::setObjectName(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->setObjectName(QString::fromStdString(info[0].ToString().Utf8Value()));

    return Napi::Value();
}

Napi::Value QWidgetWrap::parent(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::String::New(env, q_->parent()->objectName().toStdString());
}

Napi::Value QWidgetWrap::update(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->update();

    return Napi::Value();
}

Napi::Value QWidgetWrap::setMouseTracking(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->setMouseTracking(info[0].ToBoolean().Value());

    return Napi::Value();
}

Napi::Value QWidgetWrap::hasMouseTracking(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Boolean::New(env, q_->hasMouseTracking());
}

Napi::Value QWidgetWrap::setFocusPolicy(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->setFocusPolicy((Qt::FocusPolicy)(info[0].ToNumber().Int32Value()));

    return Napi::Value();
}

Napi::Value QWidgetWrap::move(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->move(info[0].ToNumber().Int32Value(), info[1].ToNumber().Int32Value());

    return Napi::Value();
}

Napi::Value QWidgetWrap::x(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, q_->x());
}

Napi::Value QWidgetWrap::y(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, q_->y());
}