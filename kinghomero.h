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
#include <QMap>

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
    // Control de sprites de animación
    unsigned int spriteActual;
    QList<QPixmap> sprites;

    // Timers
    QTimer *timerMovimiento;
    QTimer *timerAnimacion;
    QTimer *timerColisiones;

    // Movimiento
    bool enMovimiento;
    QSet<int> teclasPresionadas;

    // Indicador de vidas
    QGraphicsPixmapItem *indicadorVidas;
    QMap<unsigned int, QPixmap> vidasSprites;
    void perderVida();
    void actualizarIndicadorVidas();

    // Colisiones
    void verificarColisionConObstaculos();

    // Métodos de control
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void moverPersonaje();
    void mostrarEstado() const;

    // Sonido
    QSoundEffect *sonidoColision;

    // Game Over
    QGraphicsPixmapItem* imagenGameOver;


};

#endif // KINGHOMERO_H
