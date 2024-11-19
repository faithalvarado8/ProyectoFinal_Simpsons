#ifndef JUGADOR_H
#define JUGADOR_H

#include "personajes.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <string>
#include <QMap>

using namespace std;

class Jugador: public Personajes{
    Q_OBJECT
private:
    string nombre;

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

public:
    Jugador(string nombre);

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void actualizarAnimacion();

};

#endif // JUGADOR_H
