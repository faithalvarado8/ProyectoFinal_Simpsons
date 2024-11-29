#ifndef HOMERO_H
#define HOMERO_H
#include "Nivel.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>

class Homero : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    explicit Homero(QObject *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mover(int dx, int dy);
    void actualizarAnimacion();
    void iniciarSalto();
    void actualizarSalto();

private:
    QVector<QPixmap> spritesCaminarDerecha;
    QVector<QPixmap> spritesCaminarIzquierda;
    QVector<QPixmap> spritesSaltarDerecha;
    QVector<QPixmap> spritesSaltarIzquierda;
    QVector<QPixmap> spritesCelebrar;

    int indiceSprite;
    bool moviendoDerecha;
    bool moviendoIzquierda;
    bool saltando;
    QTimer *timerAnimacion;
    QTimer *timerSalto;

    static constexpr int velocidadMovimiento = 5;
    static constexpr int alturaSalto = 50;

    // Variables para controlar el salto
    float velocidadY = 0;
    const float fuerzaSalto = 15.0f; // Fuerza inicial del salto
    const float gravedad = 0.5f; // Aceleración de la gravedad
    double nivelSuelo = 710;
};

#endif // HOMERO_H
