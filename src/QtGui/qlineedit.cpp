#include "qlineedit.hpp"

Napi::FunctionReference QLineEditWrap::constructor;

QWIDGET_IMPL_FUNCS(QLineEdit)

void SlotHandlerLineEdit::textChangedSlot(const QString &text)
{
    Napi::Env env = element->textChangedCallback_.Env();
    element->textChangedCallback_.Call({Napi::String::New(env, text.toStdString())});
}

Napi::Object QLineEditWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QLineEdit", {
        InstanceMethod("setText", &QLineEditWrap::setText),
        InstanceMethod("text", &QLineEditWrap::text),
        InstanceMethod("setAlignment", &QLineEditWrap::setAlignment),
        InstanceMethod("textChangedEvent", &QLineEditWrap::textChangedEvent),
        QWIDGET_JS_DEFINES(QLineEditWrap)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QLineEdit", func);
    return exports;
}

QLineEditWrap::QLineEditWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QLineEditWrap>(info), slotHandler(this)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        QWidget *parent = unwrap(info[0]);
        q_ = new QLineEditImpl(parent, env);
    }
    else
    {
        QLineEditImpl *q_parent = 0;
        q_ = new QLineEditImpl(q_parent, env);
    }
}

QLineEditWrap::~QLineEditWrap()
{
    q_ = NULL;
}

Napi::Value QLineEditWrap::setText(const Napi::CallbackInfo &info)
{
    q_->setText(QString::fromStdString(info[0].ToString().Utf8Value()));
    return Napi::Value();
}

Napi::Value QLineEditWrap::text(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::String::New(env, q_->text().toStdString());
}

Napi::Value QLineEditWrap::setAlignment(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->setAlignment(static_cast<Qt::Alignment>(info[0].ToNumber().Int32Value()));

    return Napi::Value();
}

Napi::Value QLineEditWrap::textChangedEvent(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    textChangedCallback_ = Napi::Persistent(info[0].As<Napi::Function>());
    QObject::connect(q_, SIGNAL(textChanged(QString)), &slotHandler, SLOT(textChangedSlot(QString)));

    return Napi::Value();
}

#include "qlineedit.moc"

// QWidget functions
QWIDGET_BASE_FUNCS(QLineEditWrap)