QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quickpass
TEMPLATE = app

#DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    main.cpp \
    quickpass.cpp

HEADERS += \
    quickpass.h \
    newaccount.h \
    newpassword.h

FORMS += \
    quickpass.ui \
    newaccount.ui \
    newpassword.ui
