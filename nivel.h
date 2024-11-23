#ifndef NIVEL_H
#define NIVEL_H

#include "jugador.h"
#include "objetos.h"
#include "bart.h"
#include "kinghomero.h"
#include "murcielago.h"
#include "obstaculo.h"
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>


class Nivel : public QObject{
    Q_OBJECT
private:
    unsigned short nivelSeleccionado;
    unsigned short cont=1;
    QGraphicsScene* escena;

    //Nivel 2
    QGraphicsPixmapItem* edificioItem;
    KingHomero *kingHomero;
    int yOffset;
    QGraphicsPixmapItem* margeSprite1;
    QGraphicsPixmapItem* margeSprite2;
    QGraphicsTextItem *textoTiempo;
    QTimer *timerNivel;
    QTimer *timerMargeAnimacion;
    QTimer *timerObstaculos;
    int tiempoRestante;

    //Nivel 3
    Bart * bart;
    Murcielago* murcielago;

    QGraphicsPixmapItem* imagenGameOver;

public:
    Nivel(short int nivelSeleccionado, QGraphicsScene * escena);
    void moverEdificio();
    void actualizarTiempo();
    void sincronizarFondo(int dy);
    void verificarColisiones();
    void animarMarge();
    void showMarge();
    Jugador * jugador;
    Objetos* arma;
    Objetos* pagina;
    virtual ~Nivel();
};

#endif // NIVEL_H
