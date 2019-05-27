#!/bin/bash

#
# Only repo maintainers should need to use this
# Copies all necessary Qt frameworks into the current dir, and updates
# the LD paths
#

# /Cellar assumes we've installed Qt via homebrew
QT_PATH=/usr/local/Cellar/qt/5.12.3

echo Removing existing copy
rm -rf include lib plugins
mkdir include lib plugins

process_framework() {
    cp -R ${QT_PATH}/lib/$1.framework lib
    find . -type l | xargs rm -f
    mv -f lib/$1.framework/Versions/5/Headers include/$1
    mv -f lib/$1.framework/Versions/5/* lib/$1.framework
    chmod -R u+rw *
    install_name_tool -id lib/$1.framework/$1 lib/$1.framework/$1
}

cp -R ${QT_PATH}/plugins/platforms .
install_name_tool -id platforms/libqcocoa.dylib platforms/libqcocoa.dylib

process_framework "QtCore"
process_framework "QtGui"
process_framework "QtWidgets"
process_framework "QtDBus"
process_framework "QtPrintSupport"

# Update internal refs (from old paths to new)
install_name_tool -change ${QT_PATH}/lib/QtCore.framework/Versions/5/QtCore lib/QtCore.framework/QtCore lib/QtGui.framework/QtGui

install_name_tool -change ${QT_PATH}/lib/QtCore.framework/Versions/5/QtCore lib/QtCore.framework/QtCore lib/QtWidgets.framework/QtWidgets
install_name_tool -change ${QT_PATH}/lib/QtGui.framework/Versions/5/QtGui lib/QtGui.framework/QtGui lib/QtWidgets.framework/QtWidgets

install_name_tool -change ${QT_PATH}/lib/QtCore.framework/Versions/5/QtCore lib/QtCore.framework/QtCore lib/QtDBus.framework/QtDBus

install_name_tool -change ${QT_PATH}/lib/QtCore.framework/Versions/5/QtCore lib/QtCore.framework/QtCore lib/QtPrintSupport.framework/QtPrintSupport
install_name_tool -change ${QT_PATH}/lib/QtGui.framework/Versions/5/QtGui lib/QtGui.framework/QtGui lib/QtPrintSupport.framework/QtPrintSupport
install_name_tool -change ${QT_PATH}/lib/QtWidgets.framework/Versions/5/QtWidgets lib/QtWidgets.framework/QtWidgets lib/QtPrintSupport.framework/QtPrintSupport

install_name_tool -change ${QT_PATH}/platforms/libqcocoa.dylib platforms/libqcocoa.dylib platforms/libqcocoa.dylib
install_name_tool -change ${QT_PATH}/lib/QtCore.framework/Versions/5/QtCore @loader_path/../lib/QtCore.framework/QtCore platforms/libqcocoa.dylib
install_name_tool -change ${QT_PATH}/lib/QtGui.framework/Versions/5/QtGui @loader_path/../lib/QtGui.framework/QtGui platforms/libqcocoa.dylib
install_name_tool -change ${QT_PATH}/lib/QtWidgets.framework/Versions/5/QtWidgets @loader_path/../lib/QtWidgets.framework/QtWidgets platforms/libqcocoa.dylib
install_name_tool -change ${QT_PATH}/lib/QtDBus.framework/Versions/5/QtDBus @loader_path/../lib/QtDBus.framework/QtDBus platforms/libqcocoa.dylib
install_name_tool -change ${QT_PATH}/lib/QtPrintSupport.framework/Versions/5/QtPrintSupport @loader_path/../lib/QtPrintSupport.framework/QtPrintSupport platforms/libqcocoa.dylib

# # Fix libpng (we need libpng as per: https://github.com/arturadib/node-qt/issues/5)
# install_name_tool -change /usr/X11/lib/libpng15.15.dylib libpng15.15.dylib lib/QtGui.framework/QtGui

# Break unncessary references to old path to avoid Qt's weird fallback
# (find command only matches binary files like QtCore, not QtCore.prl)
find lib -type f -name 'Qt*' ! -name '*.*' | LANG=C xargs sed -i.bak -E 's/Cellar/______/g'
find lib -name '*.bak' | xargs rm -f

