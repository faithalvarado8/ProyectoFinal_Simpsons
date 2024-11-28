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

    void actualizarAnimacion();

private:
    QVector<QPixmap> spritesCaminar;
    QVector<QPixmap> spritesSaltar;
    QPixmap spriteCelebrar;
    int indiceSprite;
    bool moviendoIzquierda;
    bool moviendoDerecha;
    QTimer *timerAnimacion;

    const int velocidadMovimiento = 5;
};

#endif // HOMERO_H
