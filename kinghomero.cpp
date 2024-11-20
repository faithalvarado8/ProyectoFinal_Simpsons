#include "kinghomero.h"

// Constructor de KingHomero
KingHomero::KingHomero() : spriteActual(0) {
    sprites.append(QPixmap(":/Nivel2/Homer_Up1.png"));
    sprites.append(QPixmap(":/Nivel2/Homer_Up2.png"));

    // Redimensiona el sprite a 180x180 píxeles
    QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Establecer la posición inicial
    setPos(600, 720);

    // Asegurarse de que Homero no se salga de la escena (comprobaciones)
    setZValue(2);

    // Crear el temporizador para la animación
    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &KingHomero::actualizarAnimacion);
    timerAnimacion->start(200);
}

void KingHomero::keyPressEvent(QKeyEvent *event) {
    const unsigned int velocidad = 10;
    const unsigned int anchoSprite = 430;  // Ancho del sprite de Homero
    const unsigned int altoSprite = 180;   // Alto del sprite de Homero
    const unsigned int limiteAncho = 1280 - anchoSprite; // Límite derecho de la escena

    switch (event->key()) {
    case Qt::Key_A:
        // Mover hacia la izquierda, asegurándose de que no se salga de la escena
        if (x() - velocidad >= 320) {
            setX(x() - velocidad);
        }
        break;
    case Qt::Key_D:
        // Mover hacia la derecha, asegurándose de que no se salga de la escena
        if (x() + velocidad <= limiteAncho) {
            setX(x() + velocidad);
        }
        break;
    case Qt::Key_W:
        // Mover hacia arriba, asegurándose de que no se salga de la escena
        if (y() - velocidad >= 0) {
            setY(y() - velocidad);
        }
        break;
    }

    // Actualizar la animación después de mover
    spriteActual = (spriteActual + 1) % sprites.size();
    QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(anchoSprite, altoSprite, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void KingHomero::actualizarAnimacion() {
    spriteActual = (spriteActual + 1) % sprites.size();
    QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
