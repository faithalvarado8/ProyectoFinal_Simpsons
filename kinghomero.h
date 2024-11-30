#ifndef KINGHOMERO_H
#define KINGHOMERO_H

#include "jugador.h"
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
    void agregarIndicadorVidaALaEscena();
    void iniciarCelebracion();

signals:
    void moverHaciaArriba(int dy);

private slots:
    void actualizarAnimacion();
    void actualizarCelebracion();

private:
    // Control de sprites de animación
    unsigned int spriteActual;
    QList<QPixmap> sprites;
    QList<QPixmap> spritesCelebracion;

    // Timers
    QTimer *timerMovimiento;
    QTimer *timerAnimacion;
    QTimer *timerColisiones;

    // Movimiento
    bool enMovimiento;
    QSet<int> teclasPresionadas;

    // Indicador de vidas
    QGraphicsPixmapItem *indicadorVida;
    QMap<unsigned int, QPixmap> vidasSprites;
    void perderVida();
    void actualizarIndicadorGrafico();

    // Colisiones
    void verificarColisionConObstaculos();

    // Métodos de control
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void moverPersonaje();

    // Sonido
    QSoundEffect *sonidoColision;

    // Game Over
    QGraphicsPixmapItem* imagenGame;

    int animacion;
};

#endif // KINGHOMERO_H
