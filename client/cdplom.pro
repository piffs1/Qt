#-------------------------------------------------
#
# Project created by QtCreator 2017-04-25T17:10:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cdplom
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    set_con.cpp \
    set_chat.cpp \
    roomlist.cpp \
    newroom.cpp \
    spravka.cpp \
    createevent.cpp \
    list_of_events.cpp \
    uploadfile.cpp \
    filemanager.cpp \
    spravka_v_2.cpp

HEADERS  += mainwindow.h \
    set_con.h \
    set_chat.h \
    roomlist.h \
    newroom.h \
    admin_panel_копия.h \
    spravka.h \
    createevent.h \
    list_of_events.h \
    uploadfile.h \
    filemanager.h \
    spravka_v_2.h

FORMS    += mainwindow.ui \
    set_con.ui \
    set_chat.ui \
    roomlist.ui \
    newroom.ui \
    spravka.ui \
    createevent.ui \
    list_of_events.ui \
    uploadfile.ui \
    filemanager.ui \
    spravka_v_2.ui
