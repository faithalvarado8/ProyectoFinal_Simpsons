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

private:
    QVector<QPixmap> sprites;
    int spriteActual=0;
    QTimer *timer;

};

#endif // MURCIELAGO_H
