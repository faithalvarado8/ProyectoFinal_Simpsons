#ifndef NIVEL_H
#define NIVEL_H

#include <QGraphicsScene>
#include <QObject>
#include "jugador.h"
#include "objetos.h"

class Nivel : public QObject{
    Q_OBJECT
private:
    short int nivelSeleccionado;

public:
    Nivel(short int nivelSeleccionado, QGraphicsScene * escena);
    Jugador * jugador;
    Objetos* objeto;
    virtual ~Nivel();
};

#endif // NIVEL_H
