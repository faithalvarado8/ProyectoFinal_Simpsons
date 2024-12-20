#ifndef BART_H
#define BART_H

#include "jugador.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QMap>

class Bart: public Jugador{
    Q_OBJECT

public:
    Bart(QGraphicsScene* escena, QList<QGraphicsPixmapItem*> tumbasEscena);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    void municiones();
    void lanzarMunicion();
    void colisionTumba();
    ~Bart();
    QList<QGraphicsPixmapItem*> getMuniciones();
    void eliminarMunicion(int i);

private slots:
    void actualizarAnimacion();
    void actualizarDisparo();

private:
    // Sprites
    QPixmap sprites;
    QPixmap spritesLado;
    QPixmap spritesArribaAbajo;
    QPixmap spritesArma;

    // Dimensiones hoja de sprites
    unsigned int anchoLado, altoLado;
    unsigned int anchoArribaAbajo, altoArribaAbajo;
    unsigned int anchoArma, altoArma;
    unsigned int ancho, alto;

    unsigned short int columna;
    unsigned short int fila;
    QTimer *timer;
    bool moving;
    int spriteX, spriteY;
    char direccion;

    bool disparar;
    int numMuniciones;
    QTimer* timerDisparo;
    QGraphicsPixmapItem* municion;
    QList<QGraphicsPixmapItem*> listaMuniciones;

    QList<QGraphicsPixmapItem*> tumbasEscena;
    QPointF nuevaPos;
    QPointF oldPos;

    QMap<int,bool>keys;
    QGraphicsScene* escena;
};

#endif // BART_H
