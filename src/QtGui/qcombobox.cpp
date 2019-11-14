#include "qcombobox.hpp"

Napi::FunctionReference QComboBoxWrap::constructor;

QWIDGET_IMPL_FUNCS(QComboBox)

void SlotHandlerComboBox::currentTextChangedSlot(const QString &text)
{
    Napi::Env env = element->currentTextChangedCallback_.Env();
    element->currentTextChangedCallback_.Call({Napi::String::New(env, text.toStdString())});
}

void SlotHandlerComboBox::activatedSlot(const QString &text)
{
    Napi::Env env = element->activatedCallback_.Env();
    element->activatedCallback_.Call({Napi::String::New(env, text.toStdString())});
}

Napi::Object QComboBoxWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QComboBox", {
        InstanceMethod("setCurrentText", &QComboBoxWrap::setCurrentText),
        InstanceMethod("currentText", &QComboBoxWrap::currentText),
        InstanceMethod("setCurrentIndex", &QComboBoxWrap::setCurrentIndex),
        InstanceMethod("currentIndex", &QComboBoxWrap::currentIndex),
        InstanceMethod("addItem", &QComboBoxWrap::addItem),
        InstanceMethod("insertItem", &QComboBoxWrap::insertItem),
        InstanceMethod("removeItem", &QComboBoxWrap::removeItem),
        InstanceMethod("isEditable", &QComboBoxWrap::isEditable),
        InstanceMethod("setEditable", &QComboBoxWrap::setEditable),
        InstanceMethod("currentTextChangedEvent", &QComboBoxWrap::currentTextChangedEvent),
        InstanceMethod("activatedEvent", &QComboBoxWrap::activatedEvent),
        QWIDGET_JS_DEFINES(QComboBoxWrap)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QComboBox", func);
    return exports;
}

QComboBoxWrap::QComboBoxWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QComboBoxWrap>(info), slotHandler(this)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        QWidget *parent = unwrap(info[0]);
        q_ = new QComboBoxImpl(parent, env);
    }
    else
    {
        QComboBoxImpl *q_parent = 0;
        q_ = new QComboBoxImpl(q_parent, env);
    }
}

QComboBoxWrap::~QComboBoxWrap()
{
    q_ = NULL;
}

Napi::Value QComboBoxWrap::setCurrentText(const Napi::CallbackInfo &info)
{
    q_->setCurrentText(QString::fromStdString(info[0].ToString().Utf8Value()));
    return Napi::Value();
}

Napi::Value QComboBoxWrap::currentText(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::String::New(env, q_->currentText().toStdString());
}

Napi::Value QComboBoxWrap::setCurrentIndex(const Napi::CallbackInfo &info)
{
    q_->setCurrentIndex(info[0].ToNumber().Int32Value());
    return Napi::Value();
}

Napi::Value QComboBoxWrap::currentIndex(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, q_->currentIndex());
}

Napi::Value QComboBoxWrap::addItem(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->addItem(QString::fromStdString(info[0].ToString().Utf8Value()));

    return Napi::Value();
}

Napi::Value QComboBoxWrap::insertItem(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->insertItem(info[1].ToNumber().Int32Value(), QString::fromStdString(info[1].ToString().Utf8Value()));

    return Napi::Value();
}

Napi::Value QComboBoxWrap::removeItem(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->removeItem(info[0].ToNumber().Int32Value());

    return Napi::Value();
}

Napi::Value QComboBoxWrap::isEditable(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Boolean::New(env, q_->isEditable());
}

Napi::Value QComboBoxWrap::setEditable(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    q_->setEditable(info[0].ToBoolean());

    return Napi::Value();
}

Napi::Value QComboBoxWrap::currentTextChangedEvent(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    currentTextChangedCallback_ = Napi::Persistent(info[0].As<Napi::Function>());
    QObject::connect(q_, SIGNAL(currentTextChanged(const QString &)), &slotHandler, SLOT(currentTextChangedSlot(const QString &)));

    return Napi::Value();
}

Napi::Value QComboBoxWrap::activatedEvent(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    activatedCallback_ = Napi::Persistent(info[0].As<Napi::Function>());
    QObject::connect(q_, SIGNAL(activated(const QString &)), &slotHandler, SLOT(activatedSlot(const QString &)));

    return Napi::Value();
}

#include "qcombobox.moc"

// QWidget functions
QWIDGET_BASE_FUNCS(QComboBoxWrap)