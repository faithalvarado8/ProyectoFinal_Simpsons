#include "kinghomero.h"

KingHomero::KingHomero() : spriteActual(0), enMovimiento(false), tiempoPresion(new QElapsedTimer) {
    sprites.append(QPixmap(":/Nivel2/Homer_Up1.png"));
    sprites.append(QPixmap(":/Nivel2/Homer_Up2.png"));

    QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    setPos(640, 520);
    setZValue(2);

    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &KingHomero::actualizarAnimacion);
    timerAnimacion->start(200);

    timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, this, &KingHomero::verificarColisionConObstaculos);
    timerColisiones->start(10);

    sonidoColision = new QSoundEffect(this);
    sonidoColision->setSource(QUrl(":/Sonidos/SoundEffects/Colision_Explotar.mp3"));  // Ruta al archivo MP3
    sonidoColision->setVolume(1.0f);
}

// ------------------ EVENTOS POR TECLADO ----------------------

void KingHomero::keyPressEvent(QKeyEvent *event) {
    const unsigned int velocidad = 10;
    const unsigned int anchoSprite = 430;
    const unsigned int limiteAncho = 1280 - anchoSprite;
    const unsigned int limiteSuperiorY = 80;

    enMovimiento = true;
    teclasPresionadas.insert(event->key());

    if (tiempoPresion->isValid() == false) {
        tiempoPresion->start();
    }

    switch (event->key()) {
    case Qt::Key_A:
        if (x() - velocidad >= 320) {
            setX(x() - velocidad);
            qDebug() << "Tecla A presionada: Movimiento hacia la izquierda. Nueva posición X:" << x();
        } else {
            qDebug() << "Tecla A presionada: Límite izquierdo alcanzado.";
        }
        break;

    case Qt::Key_D:
        if (x() + velocidad <= limiteAncho) {
            setX(x() + velocidad);
            qDebug() << "Tecla D presionada: Movimiento hacia la derecha. Nueva posición X:" << x();
        } else {
            qDebug() << "Tecla D presionada: Límite derecho alcanzado.";
        }
        break;

    case Qt::Key_W:
        if (y() - velocidad >= limiteSuperiorY) {
            emit moverHaciaArriba(-velocidad);
            qDebug() << "Tecla W presionada: Movimiento hacia arriba emitido. Nueva posición Y:" << y();
        } else {
            qDebug() << "Tecla W presionada: Límite superior alcanzado en Y.";
        }
        break;

    default:
        qDebug() << "Tecla no reconocida presionada: Código" << event->key();
        break;
    }
}


void KingHomero::keyReleaseEvent(QKeyEvent *event) {
    teclasPresionadas.remove(event->key());

    if (teclasPresionadas.isEmpty()) {
        enMovimiento = false;
        timerAnimacion->start(200);
    } else {
        enMovimiento = true;
    }

    if (teclasPresionadas.isEmpty()) {
        QGraphicsPixmapItem::setPixmap(sprites[0].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    if (teclasPresionadas.isEmpty()) {
        tiempoPresion->invalidate();
    }
}

// ------------------ ANIMACIÓN DE SPRITES ----------------------

void KingHomero::actualizarAnimacion() {
    if (enMovimiento) {
        spriteActual = (spriteActual + 1) % sprites.size();
        QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

// ------------------  COLISIONES ----------------------

void KingHomero::verificarColisionConObstaculos() {
    for (auto *obstaculo : scene()->items()) {
        Obstaculo *ob = dynamic_cast<Obstaculo*>(obstaculo);
        if (ob && collidesWithItem(ob)) {
            qDebug() << "Colisión con el obstáculo!";
            scene()->removeItem(ob);
            delete ob;
            sonidoColision->play();
            break;
        }
    }
}

KingHomero::~KingHomero() {

    if (timerAnimacion) {
        timerAnimacion->stop();
        delete timerAnimacion;
        timerAnimacion = nullptr;
    }

    if (timerColisiones) {
        timerColisiones->stop();
        delete timerColisiones;
        timerColisiones = nullptr;
    }

    delete tiempoPresion;
    tiempoPresion = nullptr;

    delete sonidoColision;
    sonidoColision = nullptr;

    sprites.clear();
}

