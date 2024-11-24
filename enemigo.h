#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QMap>

class Enemigo: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Enemigo(unsigned short int cont);

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
    unsigned short int contM;

};

#endif // ENEMIGO_H
