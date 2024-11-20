#ifndef BART_H
#define BART_H

#include "jugador.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QMap>

class Bart: public Jugador{
    Q_OBJECT

public:
    Bart(); 
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void actualizarAnimacion();

private:
    // Hojas de sprites
    QPixmap sprites;            // Hoja de sprites actualmente activa
    QPixmap spritesLado;        // Hoja de sprites para movimiento lateral
    QPixmap spritesArribaAbajo; // Hoja de sprites para movimiento vertical

    // Dimensiones de los cuadros de cada hoja de sprites
    int anchoLado, altoLado;         // Dimensiones para la hoja de movimiento lateral
    int anchoArribaAbajo, altoArribaAbajo; // Dimensiones para la hoja de movimiento vertical
    int ancho, alto;                 // Dimensiones actuales de los cuadros en uso

    int columna;
    int fila;

    QTimer *timer;

    QMap<int,bool>keys;

};

#endif // BART_H
