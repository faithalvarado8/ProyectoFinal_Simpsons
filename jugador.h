#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QObject>


class Jugador : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
protected:
    unsigned int vidas;
    QGraphicsPixmapItem* imagenGameOver;
public:
    explicit Jugador(unsigned int vidasIniciales = 3);
    void recuperarVida();
    void perderVida();
    unsigned int getVidas() const;
    virtual void mostrarEstado() const;
};

#endif // JUGADOR_H
