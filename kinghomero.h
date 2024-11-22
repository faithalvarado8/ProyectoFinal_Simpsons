#ifndef KINGHOMERO_H
#define KINGHOMERO_H

#include "jugador.h"
#include "obstaculo.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QElapsedTimer>
#include <QTimer>
#include <QSet>
#include <QSoundEffect>

class KingHomero : public Jugador{
    Q_OBJECT
public:
    KingHomero();
    ~KingHomero();

signals:
    void moverHaciaArriba(int dy);

private slots:
    void actualizarAnimacion();

private:
    unsigned int spriteActual;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void moverPersonaje();
    bool enMovimiento;
    QList<QPixmap> sprites;
    QTimer *timerMovimiento;
    QTimer *timerAnimacion;
    QTimer *timerColisiones;
    QSet<int> teclasPresionadas;
    void verificarColisionConObstaculos();
    QSoundEffect *sonidoColision;

};

#endif // KINGHOMERO_H
