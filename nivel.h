#ifndef NIVEL_H
#define NIVEL_H

#include "jugador.h"
#include "objetos.h"
#include "bart.h"
#include "kinghomero.h"
#include "enemigo.h"
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
    Objetos* arma;
    Objetos* pagina;

    Enemigo* murcielago;
    QList<Enemigo*> murcielagos;
    QTimer *colisionTimer;

    QGraphicsPixmapItem* tumba;
    void agregarTumbas(int numTumbas);
    QList<QPointF> posicionesTumbas;
    QVector<QPixmap> tumbas;
    int spriteTumba;
    bool posicionValida;
    int x,y;
    double distancia;
    QPointF nuevaPos;
    QList<QGraphicsPixmapItem*> tumbasEscena;

    QGraphicsPixmapItem* imagenGameOver;
    Jugador * jugador;

public:
    Nivel(short int nivelSeleccionado, QGraphicsScene * escena);
    void moverEdificio();
    void actualizarTiempo();
    void sincronizarFondo(int dy);
    void animarMarge();
    void showMarge();

    void verificarColisiones();
    void gameOver();
    virtual ~Nivel();
};

#endif // NIVEL_H
