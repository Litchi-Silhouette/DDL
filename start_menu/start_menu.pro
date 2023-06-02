QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controlwindow.cpp \
    loadwindow.cpp \
    main.cpp \
    menuwindow.cpp \
    set_help_acc.cpp \
    startwindow.cpp \
    windowbase.cpp

HEADERS += \
    Game.hpp \
    controlwindow.h \
    loadwindow.h \
    menuwindow.h \
    set_help_acc.h \
    startwindow.h \
    windowbase.h

FORMS += \
    controlwindow.ui \
    loadwindow.ui \
    menuwindow.ui \
    startwindow.ui \
    windowbase.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    page.qrc
