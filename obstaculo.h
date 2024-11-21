#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QObject>
#include <cstdlib>
#include <QTimer>
#include <ctime>


class Obstaculo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Obstaculo(QGraphicsScene *escena, QObject *parent = nullptr);
    ~Obstaculo();

private slots:
    void mover();

private:
    QTimer *timerMovimiento; // Temporizador para el movimiento
    QGraphicsScene *escena;  // Referencia a la escena
};

#endif // OBSTACULO_H
