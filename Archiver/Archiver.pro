#-------------------------------------------------
#
# Project created by QtCreator 2017-09-17T01:09:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Archiver
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    probability_of_chars.cpp \
    get_text_from_file.cpp \
    create_file_with_prob.cpp \
    parse_hash_to_string.cpp \
    huffman_tree.cpp \
    compress.cpp \
    decompress.cpp \
    parse_string_to_hash.cpp

HEADERS += \
        mainwindow.h \
    probability_of_chars.h \
    get_text_from_file.h \
    create_file_with_prob.h \
    parse_hash_to_string.h \
    huffman_tree.h \
    alias.h \
    compress.h \
    decompress.h \
    parse_string_to_hash.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc

CONFIG += c++14

win32:RC_ICONS += Resources\Icon\icon.png

DISTFILES +=
