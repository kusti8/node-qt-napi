#include <napi.h>
#include "QtGui/qapplication.hpp"
#include "QtGui/qwidget.hpp"
#include "QtGui/qmainwindow.hpp"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    QApplicationWrap::Init(env, exports);
    QWidgetWrap::Init(env, exports);
    QMainWindowWrap::Init(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)