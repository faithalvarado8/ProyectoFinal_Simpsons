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
    short int nivelSeleccionado;
    QGraphicsScene* escena;
    QGraphicsPixmapItem* edificioItem;
    int yOffset;
    Bart * bart;
    KingHomero *kingHomero;
    Murcielago* murcielago;
    unsigned short int cont=1;
    QTimer *timerObstaculos;
    int tiempoRestante;
    QTimer *timerNivel;
    QTimer *timerMargeAnimacion;
    QGraphicsTextItem *textoTiempo;
    QGraphicsPixmapItem* imagenGameOver;
    QGraphicsPixmapItem* margeSprite1;
    QGraphicsPixmapItem* margeSprite2;
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
