QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ddlline.cpp \
    figure.cpp \
    gamemap.cpp \
    gamemapone.cpp \
    init.cpp \
    main.cpp \
    mainwindow.cpp \
    obstacle.cpp \
    taskbuff.cpp \
    taskbuffinstance.cpp \
    taskbuffprocessor.cpp

HEADERS += \
    config.h \
    figure.h \
    gamemap.h \
    gamemapone.h \
    mainwindow.h \
    taskbuff.h \
    taskbuffinstance.h \
    taskbuffprocessor.h

# wzl part

SOURCES += \
    level_page_base/ddl_list.cpp \
    level_page_base/levelwindow.cpp \
    level_page_base/live_bar.cpp \
    #level_page_base/main.cpp \
    level_page_base/mylabel.cpp \
    level_page_base/pause_button.cpp \
    level_page_base/set_pausedialog.cpp \
    level_page_base/warning_icon.cpp

HEADERS += \
    level_page_base/Game.h \
    level_page_base/ddl_list.h \
    level_page_base/levelwindow.h \
    level_page_base/live_bar.h \
    level_page_base/mylabel.h \
    level_page_base/pause_button.h \
    level_page_base/set_pausedialog.h \
    level_page_base/warning_icon.h

FORMS += \
    level_page_base/levelwindow.ui

RESOURCES += \
    level_page_base/imges.qrc



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
