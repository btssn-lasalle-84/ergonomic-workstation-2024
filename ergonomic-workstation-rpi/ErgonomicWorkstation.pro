QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    affichagepageprocessus.cpp \
    bac.cpp \
    dialoguemodule.cpp \
    etape.cpp \
    ihm.cpp \
    main.cpp \
    operateur.cpp \
    postetravail.cpp \
    processusassemblage.cpp

HEADERS += \
    affichagepageprocessus.h \
    bac.h \
    dialoguemodule.h \
    etape.h \
    ihm.h \
    operateur.h \
    postetravail.h \
    processusassemblage.h

FORMS +=

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT

COPIES += dossier
dossier.files = processus-assemblage
dossier.path = $$OUT_PWD/
dossier.base = $$PWD/

