QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controlwindow.cpp \
    windowbase.cpp \
    main.cpp

HEADERS += \
    Game.hpp\
    controlwindow.h \
    windowbase.h

FORMS += \
    controlwindow.ui \
    windowbase.ui

# Act part

SOURCES += \
    Acts/actwindow.cpp

HEADERS += \
    Acts/actwindow.h

FORMS += \
    Acts/actwindow.ui

RESOURCES += \
    Acts/video.qrc \
    music.qrc

# GameMap part
SOURCES += \
    GameMap/ddlline.cpp \
    GameMap/figure.cpp \
    GameMap/gamemap.cpp \
    GameMap/gamemapone.cpp \
    GameMap/gamemapthree.cpp \
    GameMap/gamemaptwo.cpp \
    GameMap/init.cpp \
    GameMap/mainwindow.cpp \
    GameMap/mainwindowone.cpp \
    GameMap/mainwindowthree.cpp \
    GameMap/mainwindowtwo.cpp \
    GameMap/obstacle.cpp \
    GameMap/taskbuff.cpp \
    GameMap/taskbuffinstance.cpp \
    GameMap/taskbuffprocessor.cpp

HEADERS += \
    GameMap/config.h \
    GameMap/figure.h \
    GameMap/gamemap.h \
    GameMap/gamemapone.h \
    GameMap/gamemapthree.h \
    GameMap/gamemaptwo.h \
    GameMap/mainwindow.h \
    GameMap/mainwindowone.h \
    GameMap/mainwindowthree.h \
    GameMap/mainwindowtwo.h \
    GameMap/taskbuff.h \
    GameMap/taskbuffinstance.h \
    GameMap/taskbuffprocessor.h


RESOURCES += \
    GameMap/images.qrc \
    GameMap/sounds.qrc

# levelWindow part

SOURCES += \
    GameMap/level_page_base/ddl_list.cpp \
    GameMap/level_page_base/levelwindow.cpp \
    GameMap/level_page_base/live_bar.cpp \
    GameMap/level_page_base/mylabel.cpp \
    GameMap/level_page_base/pause_button.cpp \
    GameMap/level_page_base/pause_start_end.cpp \
    GameMap/level_page_base/warning_icon.cpp \

HEADERS += \
    GameMap/level_page_base/Game.hpp \
    GameMap/level_page_base/ddl_list.h \
    GameMap/level_page_base/levelwindow.h \
    GameMap/level_page_base/live_bar.h \
    GameMap/level_page_base/mylabel.h \
    GameMap/level_page_base/pause_button.h \
    GameMap/level_page_base/pause_start_end.h \
    GameMap/level_page_base/warning_icon.h \

FORMS += \
    GameMap/level_page_base/levelwindow.ui \

RESOURCES += \
    GameMap/level_page_base/imges.qrc


# start_menu part

SOURCES += \
    start_menu/endingwindow.cpp \
    start_menu/loadwindow.cpp \
    start_menu/menuwindow.cpp \
    start_menu/set_help_acc.cpp \
    start_menu/startwindow.cpp

HEADERS += \
    start_menu/endingwindow.h \
    start_menu/loadwindow.h \
    start_menu/menuwindow.h \
    start_menu/set_help_acc.h \
    start_menu/startwindow.h

FORMS += \
    start_menu/endingwindow.ui \
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
