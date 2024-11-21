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
    bool enMovimiento;
    QList<QPixmap> sprites;
    QTimer *timerAnimacion;
    QTimer *timerColisiones;
    QElapsedTimer *tiempoPresion;
    QSet<int> teclasPresionadas;
    void verificarColisionConObstaculos();
    QSoundEffect *sonidoColision;

};

#endif // KINGHOMERO_H
