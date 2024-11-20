#ifndef MURCIELAGO_H
#define MURCIELAGO_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QMap>

class Murcielago: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Murcielago();

private slots:
    void actualizarAnimacion();
    void movimiento();

private:
    QVector<QPixmap> sprites;
    int spriteActual;
    QTimer *timer;
    QTimer *timerMov;
    int angulo;
    int radio;

};

#endif // MURCIELAGO_H
