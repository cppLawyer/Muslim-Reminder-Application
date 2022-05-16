QT += core gui
QT += network
QT += core5compat
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
VERSION = 3.0
TARGET = MuslimReminder
RC_ICONS = logo.ico
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
!android-embedded {
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}
android: include(C:\Users\Abdel\Documents\OpenSSLAndroid/openssl.pri)
ANDROID_EXTRA_LIBS += \
   C:\Users\Abdel\Documents\OpenSSLAndroid\Qt-5.12.4_5.13.0\arm64\libcrypto.so \
   C:\Users\Abdel\Documents\OpenSSLAndroid\Qt-5.12.4_5.13.0\arm64\libssl.so
SOURCES += \
    main.cpp

HEADERS += \
    main.h

FORMS += \
    gui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sound.qrc

DISTFILES += \
    android/AndroidManifest.xml
