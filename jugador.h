#ifndef JUGADOR_H
#define JUGADOR_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Jugador : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
protected:
    unsigned short int vidas;

public:
    explicit Jugador(unsigned short int vidasIniciales = 3);
    void recuperarVida();
    void perderVida();
    unsigned short int getVidas() const;
    virtual ~Jugador() = default;
};

#endif // JUGADOR_H
