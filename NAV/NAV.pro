#-------------------------------------------------
#
# Project created by QtCreator 2022-06-04T18:30:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NAV
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    account.cpp \
    ant.cpp \
    clock.cpp \
    course.cpp \
    current.cpp \
    dijkstra.cpp \
    edge.cpp \
    log_search.cpp \
    log.cpp \
    login.cpp \
    vertex.cpp

HEADERS += \
        mainwindow.h \
    account.h \
    ant.h \
    clock.h \
    constants.h \
    course.h \
    current.h \
    dijkstra.h \
    edge.h \
    log_search.h \
    log.h \
    login.h \
    vertex.h

FORMS += \
        mainwindow.ui \
    login.ui \
    log_search.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/benbu.png \
    images/between.png \
    images/class.jpg \
    images/log.jpg \
    images/search.png \
    images/search.webp \
    images/set_time.jpg \
    images/set_v.jpg \
    images/shahe.jpg \
    images/switch_benbu.jpg \
    images/switch_between.jpg \
    images/switch_shahe.png \
    images/switch_shahe.webp \
    l2p.txt \
    log.txt \
    shuttle_schedule.txt \
    accounts.txt \
    adjmap.txt \
    vertices全1.txt \
    vertices半1.txt \
    vertices删.txt \
    vertices.txt \
    adjmap删.txt
