QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    figure.cpp \
    gamemap.cpp \
    init.cpp \
    main.cpp \
    mainwindow.cpp \
    obstacle.cpp \
    taskbuff.cpp \
    taskbuffprocessor.cpp \
    utils.cpp

HEADERS += \
    config.h \
    figure.h \
    gamemap.h \
    mainwindow.h \
    taskbuff.h \
    taskbuffprocessor.h

FORMS += \
    #figure.ui \
    #gamemap.ui \
    #mainwindow.ui \
    #taskbuff.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
