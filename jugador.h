#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Jugador : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
protected:
    unsigned int vidas;
public:
    explicit Jugador(unsigned int vidasIniciales = 3);
    void recuperarVida();
    void perderVida();
    unsigned int getVidas() const;
    virtual void mostrarEstado() const;
};

#endif // JUGADOR_H
