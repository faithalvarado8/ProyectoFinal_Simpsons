#include "kinghomero.h"

KingHomero::KingHomero() : Jugador(3), spriteActual(0), enMovimiento(false) {
    sprites.append(QPixmap(":/Nivel2/Homer_Up1.png"));
    sprites.append(QPixmap(":/Nivel2/Homer_Up2.png"));

    QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    setPos(640, 520);
    setZValue(2);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &KingHomero::moverPersonaje);
    timerMovimiento->start(20);

    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &KingHomero::actualizarAnimacion);
    timerAnimacion->start(200);

    timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, this, &KingHomero::verificarColisionConObstaculos);
    timerColisiones->start(10);

    sonidoColision = new QSoundEffect(this);
    sonidoColision->setSource(QUrl(":/Sonidos/SoundEffects/Colision_Explotar.mp3"));
    sonidoColision->setVolume(1.0f);
}

// ------------------ VIDAS ------------------

void KingHomero::mostrarEstado() const {
    qDebug() << "[KingHomero]";
    Jugador::mostrarEstado();
}



// ------------------ EVENTOS POR TECLADO ----------------------


void KingHomero::keyPressEvent(QKeyEvent *event) {
    teclasPresionadas.insert(event->key());
    enMovimiento = true;
}

void KingHomero::keyReleaseEvent(QKeyEvent *event) {
    teclasPresionadas.remove(event->key());
    enMovimiento = !teclasPresionadas.isEmpty();
}


void KingHomero::moverPersonaje() {
    if (!enMovimiento) return;

    const unsigned int velocidad = 5;
    const unsigned int anchoSprite = 430;
    const unsigned int limiteAncho = 1280 - anchoSprite;
    const unsigned int limiteSuperiorY = 80;

    for (int tecla : teclasPresionadas) {
        switch (tecla) {
        case Qt::Key_A:
            if (x() - velocidad >= 320) setX(x() - velocidad);
            break;
        case Qt::Key_D:
            if (x() + velocidad <= limiteAncho) setX(x() + velocidad);
            break;
        case Qt::Key_W:
            if (y() - velocidad >= limiteSuperiorY) emit moverHaciaArriba(-velocidad);
            break;
        }
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
    for (auto *item : scene()->items()) {
        if (Obstaculo *obstaculo = dynamic_cast<Obstaculo*>(item)) {
            if (collidesWithItem(obstaculo)) {
                qDebug() << "Colisión con un obstáculo!";
                perderVida();
                scene()->removeItem(obstaculo);
                delete obstaculo;
                sonidoColision->play();
                if (getVidas() == 0) {
                    imagenGameOver = new QGraphicsPixmapItem(QPixmap(":/fondos/GAME_OVER.png"));
                    imagenGameOver->setPos(scene()->width() / 2 - imagenGameOver->pixmap().width() / 2,
                                           scene()->height() / 2 - imagenGameOver->pixmap().height() / 2);
                    scene()->addItem(imagenGameOver);
                    imagenGameOver->setZValue(3);
                    return;
                }
                return;
            }
        }
    }
}


// --------- DESTRUCTOR ---------

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

    delete sonidoColision;
    sonidoColision = nullptr;

    sprites.clear();
}

