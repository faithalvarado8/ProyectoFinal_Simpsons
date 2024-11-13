#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Personajes: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    unsigned int vidas;

public:
    virtual ~Personajes() = default;  // Destructor virtual
    unsigned int recuperarVida();
    unsigned int perderVida();

};

#endif // PERSONAJES_H
