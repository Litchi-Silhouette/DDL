QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ddl_list.cpp \
    live_bar.cpp \
    main.cpp \
    levelwindow.cpp \
    mylabel.cpp \
    pause_button.cpp \
    warning_icon.cpp

HEADERS += \
    ddl_list.h \
    levelwindow.h \
    live_bar.h \
    mylabel.h \
    pause_button.h \
    warning_icon.h

FORMS += \
    levelwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imges.qrc
