#ifndef NIVEL_H
#define NIVEL_H

#include "jugador.h"
#include "objetos.h"
#include "bart.h"
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
    Bart * bart;

public:
    Nivel(short int nivelSeleccionado, QGraphicsScene * escena);
    void moverEdificio();
    void actualizarCamara();
    void verificarColisiones();
    Jugador * jugador;
    Objetos* arma;
    Objetos* pagina;
    virtual ~Nivel();
};

#endif // NIVEL_H
