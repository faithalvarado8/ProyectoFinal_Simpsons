#ifndef HOMERO_H
#define HOMERO_H

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

private:
    void mover(int dx, int dy);
    void actualizarAnimacion();

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

    static constexpr int velocidadMovimiento = 5;
    static constexpr int alturaSalto = 50;
};

#endif // HOMERO_H
