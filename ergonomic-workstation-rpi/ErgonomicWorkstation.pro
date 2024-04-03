QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bac.cpp \
    dialoguemodule.cpp \
    etape.cpp \
    main.cpp \
    ihm.cpp \
    operateur.cpp \
    postetravail.cpp \
    processusassemblage.cpp

HEADERS += \
    bac.h \
    dialoguemodule.h \
    etape.h \
    ihm.h \
    operateur.h \
    postetravail.h \
    processusassemblage.h

FORMS += \
    ihm.ui

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
