#-------------------------------------------------
#
# Project created by QtCreator 2018-06-09T17:03:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = genQrCode_ok
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qrencode/bitstream.c \
    qrencode/mask.c \
    qrencode/mmask.c \
    qrencode/mqrspec.c \
    qrencode/qrencode.c \
    qrencode/qrinput.c \
    qrencode/qrspec.c \
    qrencode/rscode.c \
    qrencode/split.c

HEADERS  += mainwindow.h \
    qrencode/bitstream.h \
    qrencode/config.h \
    qrencode/mask.h \
    qrencode/mmask.h \
    qrencode/mqrspec.h \
    qrencode/qrencode.h \
    qrencode/qrencode_inner.h \
    qrencode/qrinput.h \
    qrencode/qrspec.h \
    qrencode/rscode.h \
    qrencode/split.h \
    qrcode.h

FORMS    += mainwindow.ui

RESOURCES += \
    rc.qrc
