#ifndef HOMERO_H
#define HOMERO_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>

class Homero : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Homero(QObject *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void actualizarAnimacion();

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

    const int velocidadMovimiento = 5;
};

#endif // HOMERO_H
