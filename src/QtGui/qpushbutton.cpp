#include "qpushbutton.hpp"

Napi::FunctionReference QPushButtonWrap::constructor;

QWIDGET_IMPL_FUNCS(QPushButton)

void SlotHandlerPushButton::buttonReleasedSlot()
{
    element->buttonReleasedCallback_.Call({});
}

Napi::Object QPushButtonWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QPushButton", {
        InstanceMethod("setText", &QPushButtonWrap::setText),
        InstanceMethod("text", &QPushButtonWrap::text),
        InstanceMethod("buttonReleasedEvent", &QPushButtonWrap::buttonReleasedEvent),
        QWIDGET_JS_DEFINES(QPushButtonWrap)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QPushButton", func);
    return exports;
}

QPushButtonWrap::QPushButtonWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QPushButtonWrap>(info), slotHandler(this)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        QWidget *parent = unwrap(info[0]);
        q_ = new QPushButtonImpl(parent, env);
    }
    else
    {
        QPushButtonImpl *q_parent = 0;
        q_ = new QPushButtonImpl(q_parent, env);
    }
    q_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
}

QPushButtonWrap::~QPushButtonWrap()
{
    q_ = NULL;
}

Napi::Value QPushButtonWrap::setText(const Napi::CallbackInfo &info)
{
    q_->setText(QString::fromStdString(info[0].ToString().Utf8Value()));
    return Napi::Value();
}

Napi::Value QPushButtonWrap::text(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::String::New(env, q_->text().toStdString());
}

Napi::Value QPushButtonWrap::buttonReleasedEvent(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    buttonReleasedCallback_ = Napi::Persistent(info[0].As<Napi::Function>());
    QObject::connect(q_, SIGNAL(released()), &slotHandler, SLOT(buttonReleasedSlot()));

    return Napi::Value();
}

#include "qpushbutton.moc"

// QWidget functions
QWIDGET_BASE_FUNCS(QPushButtonWrap)