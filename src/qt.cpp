#include <napi.h>
#include "QtGui/qapplication.hpp"
#include "QtGui/qwidget.hpp"
#include "QtGui/qmainwindow.hpp"
#include "QtGui/qlabel.hpp"
#include "QtGui/qlineedit.hpp"
#include "QtGui/qpixmap.hpp"
#include "QtGui/qcombobox.hpp"
#include "QtGui/qplaintextedit.hpp"
#include "QtGui/qpushbutton.hpp"
#include "misc.hpp"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    QApplicationWrap::Init(env, exports);
    QWidgetWrap::Init(env, exports);
    QMainWindowWrap::Init(env, exports);
    QLabelWrap::Init(env, exports);
    QLineEditWrap::Init(env, exports);
    QPixmapWrap::Init(env, exports);
    QComboBoxWrap::Init(env, exports);
    QPlainTextEditWrap::Init(env, exports);
    QPushButtonWrap::Init(env, exports);
    MiscInit(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)