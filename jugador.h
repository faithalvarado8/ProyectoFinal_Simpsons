#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

using namespace std;

class Jugador: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
protected:

    float posX, posY;
    unsigned int vidas;

public:
    unsigned int recuperarVida();
    unsigned int perderVida();

};

#endif // JUGADOR_H
