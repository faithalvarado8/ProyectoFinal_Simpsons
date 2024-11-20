#include "kinghomero.h"

// Constructor de KingHomero
KingHomero::KingHomero() : spriteActual(0) {
    sprites.append(QPixmap(":/Nivel2/Homer_Up1.png"));
    sprites.append(QPixmap(":/Nivel2/Homer_Up2.png"));

    QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    setPos(10,40);
    setZValue(2);
    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &KingHomero::actualizarAnimacion);
    timerAnimacion->start(200);
}

void KingHomero::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_A:
        setX(x() - 10);
        break;
    case Qt::Key_D:
        setX(x() + 10);
        break;
    case Qt::Key_W:
        setY(y() - 10);
        break;
    }

    spriteActual = (spriteActual + 1) % sprites.size();
    QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void KingHomero::actualizarAnimacion() {
    spriteActual = (spriteActual + 1) % sprites.size();
    QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
