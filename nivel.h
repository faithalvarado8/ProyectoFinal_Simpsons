#ifndef NIVEL_H
#define NIVEL_H

#include "jugador.h"
#include "objetos.h"

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>


class Nivel : public QObject{
    Q_OBJECT
private:
    short int nivelSeleccionado;
    QGraphicsScene* escena;
    QGraphicsPixmapItem* edificioItem;
    int yOffset;

public:
    Nivel(short int nivelSeleccionado, QGraphicsScene * escena);
    void moverEdificio();
    void actualizarCamara();
    Jugador * jugador;
    Objetos* objeto;
    virtual ~Nivel();
};

#endif // NIVEL_H
