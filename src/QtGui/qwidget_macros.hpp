#ifndef QWIDGET_MACROS_H
#define QWIDGET_MACROS_H

///////////////////////////////////////
// Common QWidget Functions
///////////////////////////////////////
#define QWIDGET_DEFS                                              \
    Napi::Value resize(const Napi::CallbackInfo &info);           \
    Napi::Value show(const Napi::CallbackInfo &info);             \
    Napi::Value close(const Napi::CallbackInfo &info);            \
    Napi::Value size(const Napi::CallbackInfo &info);             \
    Napi::Value width(const Napi::CallbackInfo &info);            \
    Napi::Value height(const Napi::CallbackInfo &info);           \
    Napi::Value objectName(const Napi::CallbackInfo &info);       \
    Napi::Value setObjectName(const Napi::CallbackInfo &info);    \
    Napi::Value parent(const Napi::CallbackInfo &info);           \
    Napi::Value update(const Napi::CallbackInfo &info);           \
    Napi::Value setMouseTracking(const Napi::CallbackInfo &info); \
    Napi::Value hasMouseTracking(const Napi::CallbackInfo &info); \
    Napi::Value setFocusPolicy(const Napi::CallbackInfo &info);   \
    Napi::Value move(const Napi::CallbackInfo &info);             \
    Napi::Value x(const Napi::CallbackInfo &info);                \
    Napi::Value y(const Napi::CallbackInfo &info);                \
    Napi::Value setStyleSheet(const Napi::CallbackInfo &info);    \
    Napi::Value hide(const Napi::CallbackInfo &info);             \
    Napi::Value del(const Napi::CallbackInfo &info);              \
    Napi::Value setParent(const Napi::CallbackInfo &info);        \
                                                                  \
    Napi::Value resizeEvent(const Napi::CallbackInfo &info);      \
    Napi::Value closeEvent(const Napi::CallbackInfo &info);

///////////////////////////////////////
// Common QWidget Functions Defines for JS
///////////////////////////////////////
#define QWIDGET_JS_DEFINES(className)                                     \
    InstanceMethod("resize", &className::resize),                         \
        InstanceMethod("show", &className::show),                         \
        InstanceMethod("close", &className::close),                       \
        InstanceMethod("size", &className::size),                         \
        InstanceMethod("width", &className::width),                       \
        InstanceMethod("height", &className::height),                     \
        InstanceMethod("objectName", &className::objectName),             \
        InstanceMethod("setObjectName", &className::setObjectName),       \
        InstanceMethod("parent", &className::parent),                     \
        InstanceMethod("update", &className::update),                     \
        InstanceMethod("setMouseTracking", &className::setMouseTracking), \
        InstanceMethod("hasMouseTracking", &className::hasMouseTracking), \
        InstanceMethod("setFocusPolicy", &className::setFocusPolicy),     \
        InstanceMethod("move", &className::move),                         \
        InstanceMethod("x", &className::x),                               \
        InstanceMethod("y", &className::y),                               \
        InstanceMethod("setStyleSheet", &className::setStyleSheet),       \
        InstanceMethod("hide", &className::hide),                         \
        InstanceMethod("del", &className::del),                           \
        InstanceMethod("setParent", &className::setParent),               \
                                                                          \
        InstanceMethod("resizeEvent", &className::resizeEvent),           \
        InstanceMethod("closeEvent", &className::closeEvent),

///////////////////////////////////////
// Subclassing for callbacks
///////////////////////////////////////
#define QWIDGET_IMPL_DEF(className)                      \
    class className##Impl : public className             \
    {                                                    \
    public:                                              \
        className##Impl(QWidget *parent, Napi::Env env); \
        Napi::FunctionReference resizeCallback_;         \
        Napi::FunctionReference closeCallback_;          \
                                                         \
        Napi::Env env;                                   \
                                                         \
    private:                                             \
        void resizeEvent(QResizeEvent *e);               \
        void closeEvent(QCloseEvent *e);                 \
    };

///////////////////////////////////////
// Subclassing for callbacks function implementation
///////////////////////////////////////
#define QWIDGET_IMPL_FUNCS(className)                                                              \
    className##Impl::className##Impl(QWidget *parent, Napi::Env env) : className(parent), env(env) \
    {                                                                                              \
    }                                                                                              \
                                                                                                   \
    void className##Impl::resizeEvent(QResizeEvent *e)                                             \
    {                                                                                              \
        if (resizeCallback_.IsEmpty())                                                             \
            return;                                                                                \
                                                                                                   \
        resizeCallback_.Call({Napi::Number::New(env, e->size().width()),                           \
                              Napi::Number::New(env, e->size().height())});                        \
    }                                                                                              \
                                                                                                   \
    void className##Impl::closeEvent(QCloseEvent *e)                                               \
    {                                                                                              \
        if (closeCallback_.IsEmpty())                                                              \
            return;                                                                                \
                                                                                                   \
        closeCallback_.Call({});                                                                   \
    }

///////////////////////////////////////
// Common QWidget Function Implementations
///////////////////////////////////////
#define QWIDGET_BASE_FUNCS(className)                                                 \
    Napi::Value className::resize(const Napi::CallbackInfo &info)                     \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->resize(info[0].ToNumber().Int32Value(), info[1].ToNumber().Int32Value()); \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::show(const Napi::CallbackInfo &info)                       \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->show();                                                                   \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::close(const Napi::CallbackInfo &info)                      \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->close();                                                                  \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::size(const Napi::CallbackInfo &info)                       \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->size(); /* TODO */                                                        \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::width(const Napi::CallbackInfo &info)                      \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        return Napi::Number::New(env, q_->width());                                   \
    }                                                                                 \
                                                                                      \
    Napi::Value className::height(const Napi::CallbackInfo &info)                     \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        return Napi::Number::New(env, q_->height());                                  \
    }                                                                                 \
                                                                                      \
    Napi::Value className::objectName(const Napi::CallbackInfo &info)                 \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        return Napi::String::New(env, q_->objectName().toStdString());                \
    }                                                                                 \
                                                                                      \
    Napi::Value className::setObjectName(const Napi::CallbackInfo &info)              \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->setObjectName(QString::fromStdString(info[0].ToString().Utf8Value()));    \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::parent(const Napi::CallbackInfo &info)                     \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        return Napi::String::New(env, q_->parent()->objectName().toStdString());      \
    }                                                                                 \
                                                                                      \
    Napi::Value className::update(const Napi::CallbackInfo &info)                     \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->update();                                                                 \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::setMouseTracking(const Napi::CallbackInfo &info)           \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->setMouseTracking(info[0].ToBoolean().Value());                            \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::hasMouseTracking(const Napi::CallbackInfo &info)           \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        return Napi::Boolean::New(env, q_->hasMouseTracking());                       \
    }                                                                                 \
                                                                                      \
    Napi::Value className::setFocusPolicy(const Napi::CallbackInfo &info)             \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->setFocusPolicy((Qt::FocusPolicy)(info[0].ToNumber().Int32Value()));       \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::move(const Napi::CallbackInfo &info)                       \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->move(info[0].ToNumber().Int32Value(), info[1].ToNumber().Int32Value());   \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::x(const Napi::CallbackInfo &info)                          \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        return Napi::Number::New(env, q_->x());                                       \
    }                                                                                 \
                                                                                      \
    Napi::Value className::y(const Napi::CallbackInfo &info)                          \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        return Napi::Number::New(env, q_->y());                                       \
    }                                                                                 \
                                                                                      \
    Napi::Value className::setStyleSheet(const Napi::CallbackInfo &info)              \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->setStyleSheet(QString::fromStdString(info[0].ToString().Utf8Value()));    \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::hide(const Napi::CallbackInfo &info)                       \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->hide();                                                                   \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::del(const Napi::CallbackInfo &info)                        \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        delete q_;                                                                    \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::setParent(const Napi::CallbackInfo &info)                  \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        QWidget *parent = unwrap(info[0]);                                            \
        q_->setParent(parent);                                                        \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::resizeEvent(const Napi::CallbackInfo &info)                \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->resizeCallback_ = Napi::Persistent(info[0].As<Napi::Function>());         \
                                                                                      \
        return Napi::Value();                                                         \
    }                                                                                 \
                                                                                      \
    Napi::Value className::closeEvent(const Napi::CallbackInfo &info)                 \
    {                                                                                 \
        Napi::Env env = info.Env();                                                   \
        Napi::HandleScope scope(env);                                                 \
                                                                                      \
        q_->closeCallback_ = Napi::Persistent(info[0].As<Napi::Function>());          \
                                                                                      \
        return Napi::Value();                                                         \
    }
#endif