QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Nueces.cpp \
    Personaje.cpp \
    Tortuga.cpp \
    aranas.cpp \
    casa.cpp \
    fisica3.cpp \
    fondo.cpp \
    gameover.cpp \
    halcon.cpp \
    inicio.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mundos.cpp \
    muros.cpp \
    murosnota.cpp \
    next.cpp \
    next2.cpp \
    pantano.cpp \
    puntaje.cpp \
    roca.cpp \
    triunfo.cpp \
    vidas.cpp \
    view.cpp

HEADERS += \
    Nueces.h \
    Personaje.h \
    Tortuga.h \
    aranas.h \
    casa.h \
    fisica3.h \
    fondo.h \
    gameover.h \
    halcon.h \
    inicio.h \
    login.h \
    mainwindow.h \
    mundos.h \
    muros.h \
    murosnota.h \
    next.h \
    next2.h \
    pantano.h \
    puntaje.h \
    roca.h \
    triunfo.h \
    vidas.h \
    view.h

FORMS += \
    gameover.ui \
    login.ui \
    triunfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Imagenes.qrc

DISTFILES +=
