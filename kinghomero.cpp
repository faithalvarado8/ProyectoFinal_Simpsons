#include "kinghomero.h"
#include "obstaculo.h"
#include <QFile>

KingHomero::KingHomero() : spriteActual(0), enMovimiento(false){
    sprites.append(QPixmap(":/Nivel2/Homer_Up1.png"));
    sprites.append(QPixmap(":/Nivel2/Homer_Up2.png"));
    spritesCelebracion.append(QPixmap(":/Nivel2/Homer_Celebration1.png"));
    spritesCelebracion.append(QPixmap(":/Nivel2/Homer_Celebration2.png"));

    QGraphicsPixmapItem::setPixmap(sprites[spriteActual].scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    setPos(640, 520);
    setZValue(2);

    indicadorVida = new QGraphicsPixmapItem(QPixmap(":/Nivel2/Donut3.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    indicadorVida->setZValue(3);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &KingHomero::moverPersonaje);
    timerMovimiento->start(20);

    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &KingHomero::actualizarAnimacion);
    timerAnimacion->start(200);

    timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, this, &KingHomero::verificarColisionConObstaculos);
    timerColisiones->start(10);
}

// ------------------ VIDAS ------------------

void KingHomero::agregarIndicadorVidaALaEscena() {
    if (!indicadorVida || !scene()) {
        return;
    }

    indicadorVida->setPos(scene()->width() - indicadorVida->pixmap().width() - 10, 10);
    scene()->addItem(indicadorVida);
}

void KingHomero::perderVida() {
    if (vidas > 0) {
        Jugador::perderVida();
        actualizarIndicadorGrafico();
    }
}

void KingHomero::actualizarIndicadorGrafico() {
    if (!indicadorVida) return;

    switch (vidas) {
    case 3:
        indicadorVida->setPixmap(QPixmap(":/Nivel2/Donut3.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    case 2:
        indicadorVida->setPixmap(QPixmap(":/Nivel2/Donut2.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    case 1:
        indicadorVida->setPixmap(QPixmap(":/Nivel2/Donut1.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    default:
        break;
    }
}

// ------------------ EVENTOS POR TECLADO ----------------------


void KingHomero::keyPressEvent(QKeyEvent *event) {
    if (keys.contains(event->key())) {
        keys[event->key()] = true;
    }
}

void KingHomero::keyReleaseEvent(QKeyEvent *event) {
    if (keys.contains(event->key())) {
        keys[event->key()] = false;
    }
}


void KingHomero::moverPersonaje() {

    enMovimiento=false;
    const unsigned int velocidad = 5;
    const unsigned int anchoSprite = 430;
    const unsigned int limiteAncho = 1280 - anchoSprite;
    const unsigned int limiteSuperiorY = 80;

    if (keys[Qt::Key_A]){
        if (x() - velocidad >= 320) setX(x() - velocidad);
        enMovimiento=true;
    }
    if (keys[Qt::Key_D]){
        if (x() + velocidad <= limiteAncho) setX(x() + velocidad);
        enMovimiento=true;
    }
    if (keys[Qt::Key_W]){
        if (y() - velocidad >= limiteSuperiorY) emit moverHaciaArriba(-velocidad);
        enMovimiento=true;
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
                perderVida();
                scene()->removeItem(obstaculo);
                delete obstaculo;
                return;
            }
        }
    }
}

// --------- CELEBRACIÓN -------------

void KingHomero::iniciarCelebracion() {
    timerMovimiento->stop();
    enMovimiento = false;
    spriteActual = 0;

    timerAnimacion->stop();
    disconnect(timerAnimacion, &QTimer::timeout, this, &KingHomero::actualizarAnimacion);
    connect(timerAnimacion, &QTimer::timeout, this, &KingHomero::actualizarCelebracion);
    animacion=0;
    timerAnimacion->start(300);

}

void KingHomero::actualizarCelebracion() {
    spriteActual = (spriteActual + 1) % 2;
    QGraphicsPixmapItem::setPixmap(spritesCelebracion[spriteActual].scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    animacion++;

    if (animacion==8){
        timerAnimacion->stop();
    }
}

KingHomero::~KingHomero() {

    if (indicadorVida) {
        delete indicadorVida;
        indicadorVida = nullptr;
    }

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

    if (timerMovimiento) {
        timerMovimiento->stop();
        delete timerMovimiento;
        timerMovimiento = nullptr;
    }

    sprites.clear();
}

