#ifndef JUGADOR_H
#define JUGADOR_H

#include "personajes.h"
//#include "bart.h"

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
    //Bart * bart;

public:
    Jugador(string nombre);

};

#endif // JUGADOR_H
