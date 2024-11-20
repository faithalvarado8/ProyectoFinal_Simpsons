#ifndef KINGHOMERO_H
#define KINGHOMERO_H

#include "jugador.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QElapsedTimer>
#include <QTimer>

class KingHomero : public Jugador{
    Q_OBJECT
public:
    KingHomero();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void ajustarVelocidadAnimacion();

signals:
    void moverHaciaArriba(int dy);

private slots:
    void actualizarAnimacion();

private:
    QList<QPixmap> sprites;
    unsigned int spriteActual;
    bool enMovimiento;
    QTimer *timerAnimacion; // Temporizador para actualizar la animación
    QElapsedTimer *tiempoPresion;
};

#endif // KINGHOMERO_H
