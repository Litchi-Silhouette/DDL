QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Game.hpp\

# GameMap part

SOURCES += \
    GameMap3.3/ddlline.cpp \
    GameMap3.3/figure.cpp \
    GameMap3.3/gamemap.cpp \
    GameMap3.3/gamemapone.cpp \
    GameMap3.3/gamemapthree.cpp \
    GameMap3.3/gamemaptwo.cpp \
    GameMap3.3/init.cpp \
    GameMap3.3/main.cpp \
    GameMap3.3/mainwindow.cpp \
    GameMap3.3/mainwindowone.cpp \
    GameMap3.3/mainwindowthree.cpp \
    GameMap3.3/mainwindowtwo.cpp \
    GameMap3.3/obstacle.cpp \
    GameMap3.3/taskbuff.cpp \
    GameMap3.3/taskbuffinstance.cpp \
    GameMap3.3/taskbuffprocessor.cpp

HEADERS += \
    GameMap3.3/config.h \
    GameMap3.3/figure.h \
    GameMap3.3/gamemap.h \
    GameMap3.3/gamemapone.h \
    GameMap3.3/gamemapthree.h \
    GameMap3.3/gamemaptwo.h \
    GameMap3.3/mainwindow.h \
    GameMap3.3/mainwindowone.h \
    GameMap3.3/mainwindowthree.h \
    GameMap3.3/mainwindowtwo.h \
    GameMap3.3/taskbuff.h \
    GameMap3.3/taskbuffinstance.h \
    GameMap3.3/taskbuffprocessor.h

RESOURCES += \
    GameMap3.3/images.qrc

# levelWindow part

SOURCES += \
    GameMap3.3/level_page_base/ddl_list.cpp \
    GameMap3.3/level_page_base/levelwindow.cpp \
    GameMap3.3/level_page_base/live_bar.cpp \
    GameMap3.3/level_page_base/mylabel.cpp \
    GameMap3.3/level_page_base/pause_button.cpp \
    GameMap3.3/level_page_base/pause_start_end.cpp \
    GameMap3.3/level_page_base/warning_icon.cpp

HEADERS += \
    GameMap3.3/level_page_base/ddl_list.h \
    GameMap3.3/level_page_base/levelwindow.h \
    GameMap3.3/level_page_base/live_bar.h \
    GameMap3.3/level_page_base/mylabel.h \
    GameMap3.3/level_page_base/pause_button.h \
    GameMap3.3/level_page_base/pause_start_end.h \
    GameMap3.3/level_page_base/warning_icon.h

FORMS += \
    GameMap3.3/level_page_base/levelwindow.ui

RESOURCES += \
    GameMap3.3/level_page_base/imges.qrc

# start_menu part

SOURCES += \
    start_menu/controlwindow.cpp \
    start_menu/loadwindow.cpp \
    start_menu/menuwindow.cpp \
    start_menu/set_help_acc_start.cpp \
    start_menu/startwindow.cpp

HEADERS += \
    start_menu/controlwindow.h \
    start_menu/loadwindow.h \
    start_menu/menuwindow.h \
    start_menu/set_help_acc_start.h \
    start_menu/startwindow.h

FORMS += \
    start_menu/controlwindow.ui \
    start_menu/loadwindow.ui \
    start_menu/menuwindow.ui \
    start_menu/startwindow.ui

RESOURCES += \
    start_menu/page.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = icon_w.ico
