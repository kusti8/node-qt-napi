#ifndef MISC_H
#define MISC_H
#include <napi.h>
#include <QDesktopWidget>

void MiscInit(Napi::Env env, Napi::Object exports);

Napi::Object desktopSize(const Napi::CallbackInfo &info);
#endif