#ifndef KINGHOMERO_H
#define KINGHOMERO_H

#include "jugador.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>

class KingHomero : public Jugador{
    Q_OBJECT
public:
    KingHomero();
    void keyPressEvent(QKeyEvent *event);

private slots:
    void actualizarAnimacion();

private:
    QList<QPixmap> sprites; // Lista de sprites para la animación
    int spriteActual;       // Índice del sprite actual
    QTimer *timerAnimacion; // Temporizador para actualizar la animación
};

#endif // KINGHOMERO_H
