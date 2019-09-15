#ifndef UNWRAPPER_H
#define UNWRAPPER_H
#include <QWidget>
#include "napi.h"
#include <iostream>
#include "../QtGui/qapplication.hpp"
#include "../QtGui/qmainwindow.hpp"
#include "../QtGui/qwidget.hpp"
#include "../QtGui/qlabel.hpp"
#include "../QtGui/qlineedit.hpp"

QWidget *unwrap(Napi::Value object);

#endif