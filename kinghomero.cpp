#include "kinghomero.h"

KingHomero::KingHomero() : spriteActual(0), enMovimiento(false), tiempoPresion(new QElapsedTimer) {
    sprites.append(QPixmap(":/Nivel2/Homer_Up1.png"));
    sprites.append(QPixmap(":/Nivel2/Homer_Up2.png"));

    QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    setPos(10, 10);
    setZValue(2);

    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &KingHomero::actualizarAnimacion);
    timerAnimacion->start(200);
}

void KingHomero::keyPressEvent(QKeyEvent *event) {
    const unsigned int velocidad = 10;
    const unsigned int anchoSprite = 430;
    const unsigned int limiteAncho = 1280 - anchoSprite;

    enMovimiento = true;

    switch (event->key()) {
    case Qt::Key_A:
        if (x() - velocidad >= 320) {
            setX(x() - velocidad);
        }
        break;
    case Qt::Key_D:
        if (x() + velocidad <= limiteAncho) {
            setX(x() + velocidad);
        }
        break;
    case Qt::Key_W:
        emit moverHaciaArriba(-velocidad); // Emitimos la señal hacia el nivel.
        break;
    }

    ajustarVelocidadAnimacion();
}

void KingHomero::keyReleaseEvent(QKeyEvent *event) {
    Q_UNUSED(event);
    enMovimiento = false;

    timerAnimacion->start(200);

    QGraphicsPixmapItem::setPixmap(sprites[0].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void KingHomero::actualizarAnimacion() {
    if (enMovimiento) {
        spriteActual = (spriteActual + 1) % sprites.size();
        QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void KingHomero::ajustarVelocidadAnimacion() {
    qint64 tiempo = tiempoPresion->elapsed();

    if (tiempo > 1000) {
        timerAnimacion->start(200);
    } else if (tiempo > 500) {
        timerAnimacion->start(100);
    } else {
        timerAnimacion->start(50);
    }
}
