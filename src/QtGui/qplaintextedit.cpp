#include "qplaintextedit.hpp"

Napi::FunctionReference QPlainTextEditWrap::constructor;

QWIDGET_IMPL_FUNCS(QPlainTextEdit)

void SlotHandlerPlainTextEdit::textChangedSlot()
{
    Napi::Env env = element->textChangedCallback_.Env();
    element->textChangedCallback_.Call({Napi::String::New(env, element->q_->toPlainText().toStdString())});
}

Napi::Object QPlainTextEditWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QPlainTextEdit", {
        InstanceMethod("setText", &QPlainTextEditWrap::setText),
        InstanceMethod("text", &QPlainTextEditWrap::text),
        InstanceMethod("textChangedEvent", &QPlainTextEditWrap::textChangedEvent),
        QWIDGET_JS_DEFINES(QPlainTextEditWrap)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QPlainTextEdit", func);
    return exports;
}

QPlainTextEditWrap::QPlainTextEditWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QPlainTextEditWrap>(info), slotHandler(this)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        QWidget *parent = unwrap(info[0]);
        q_ = new QPlainTextEditImpl(parent, env);
    }
    else
    {
        QPlainTextEditImpl *q_parent = 0;
        q_ = new QPlainTextEditImpl(q_parent, env);
    }
}

QPlainTextEditWrap::~QPlainTextEditWrap()
{
    q_ = NULL;
}

Napi::Value QPlainTextEditWrap::setText(const Napi::CallbackInfo &info)
{
    q_->setPlainText(QString::fromStdString(info[0].ToString().Utf8Value()));
    return Napi::Value();
}

Napi::Value QPlainTextEditWrap::text(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::String::New(env, q_->toPlainText().toStdString());
}

Napi::Value QPlainTextEditWrap::textChangedEvent(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    textChangedCallback_ = Napi::Persistent(info[0].As<Napi::Function>());
    QObject::connect(q_, SIGNAL(textChanged()), &slotHandler, SLOT(textChangedSlot()));

    return Napi::Value();
}

#include "qplaintextedit.moc"

// QWidget functions
QWIDGET_BASE_FUNCS(QPlainTextEditWrap)