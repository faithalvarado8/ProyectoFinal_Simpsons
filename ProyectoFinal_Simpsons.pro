QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bart.cpp \
    jugador.cpp \
    main.cpp \
    juego.cpp \
    nivel.cpp \
    objetos.cpp \
    personajes.cpp

HEADERS += \
    bart.h \
    juego.h \
    jugador.h \
    nivel.h \
    objetos.h \
    personajes.h

FORMS += \
    juego.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    BartFrente.png \
    BartLado.png \
    Edificio.png \
    KingHomer-Sprites.png \
    KingHomero.jpg \
    Krusty.jpg \
    Objetos3.png \
    cementerio.jpg \
    fondoInicio1.png \
    fondoNivel3.jpg

RESOURCES += \
    Resources.qrc
