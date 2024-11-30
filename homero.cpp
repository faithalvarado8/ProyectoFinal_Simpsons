#include "Homero.h"
#include <QDebug>
#include <cmath>

Homero::Homero(QList<QGraphicsRectItem*> plataformas): indiceSprite(0), plataformas(plataformas), enElAire(false), velocidadVertical(0) {

    // Cargar las hojas de sprites
    QPixmap hojaCaminar(":/Nivel1/HomeroWalk.png");
    QPixmap hojaSaltar(":/Nivel1/HomeroJump.png");
    QPixmap hojaCelebrar(":/Nivel1/HomeroCelebrate.png");

    int anchoCaminar = hojaCaminar.width() / 3;
    int altoCaminar = hojaCaminar.height() / 2;

    int anchoSaltar = hojaSaltar.width() / 2;
    int altoSaltar = hojaSaltar.height() / 2;

    int anchoCelebrar = hojaCelebrar.width() / 2;
    int altoCelebrar = hojaCelebrar.height();

    for (int i = 0; i < 3; ++i) {
        spritesCaminarDerecha.append(hojaCaminar.copy(i * anchoCaminar, 0, anchoCaminar, altoCaminar)); // Fila 1
        spritesCaminarIzquierda.append(hojaCaminar.copy(i * anchoCaminar, altoCaminar, anchoCaminar, altoCaminar)); // Fila 2
    }

    spritesSaltarDerecha = {hojaSaltar.copy(0, 0, anchoSaltar, altoSaltar), hojaSaltar.copy(anchoSaltar, 0, anchoSaltar, altoSaltar)}; // Fila 1
    spritesSaltarIzquierda = {hojaSaltar.copy(0, altoSaltar, anchoSaltar, altoSaltar), hojaSaltar.copy(anchoSaltar, altoSaltar, anchoSaltar, altoSaltar)}; // Fila 2

    spritesCelebrar = {hojaCelebrar.copy(0, 0, anchoCelebrar, altoCelebrar), hojaCelebrar.copy(anchoCelebrar, 0, anchoCelebrar, altoCelebrar)};

    setPixmap(spritesCaminarDerecha[0].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Homero::actualizarAnimacion);
    timer->start(100);

    timerSalto = new QTimer();
    connect(timerSalto, &QTimer::timeout, this, &Homero::saltar);

    setPos(18,548);
    oldPos=QPointF(pos());
    nuevaPos=QPointF(pos());
    setZValue(2);
}

void Homero::actualizarAnimacion() {
    oldPos = QPointF(pos());
    moving = false;

    // Movimiento horizontal
    if (keys[Qt::Key_A] && !enElAire) {
        nuevaPos = pos() - QPointF(15, 0);
        moving = true;
        direccion = 'A';
    } else if (keys[Qt::Key_D] && !enElAire) {
        nuevaPos = pos() + QPointF(15, 0);
        moving = true;
        direccion = 'D';
    } else if (keys[Qt::Key_Space] && !enElAire) {
        enElAire = true;
        velocidadVertical = -15; // Velocidad inicial del salto
        timerSalto->start(50);
    }

    setPos(nuevaPos);
    colisionPlataformas();

    // Actualizar la animación
    if (moving) {
        if (direccion == 'D') {
            indiceSprite = (indiceSprite + 1) % spritesCaminarDerecha.size();
            setPixmap(spritesCaminarDerecha[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else if (direccion == 'A') {
            indiceSprite = (indiceSprite + 1) % spritesCaminarIzquierda.size();
            setPixmap(spritesCaminarIzquierda[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    } else {
        indiceSprite = 1;
        if (direccion == 'D') {
            setPixmap(spritesCaminarDerecha[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else if (direccion == 'A') {
            setPixmap(spritesCaminarIzquierda[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

    // Aplicar gravedad
    caerEnPlataforma();
}


void Homero::saltar() {
    if (enElAire) {
        // Aplicar gravedad
        velocidadVertical += 1; // Incremento de velocidad por gravedad
        setPos(x(), y() + velocidadVertical);
        // La lógica de colisiones ahora está centralizada en caerEnPlataforma
        caerEnPlataforma();
    }
}


void Homero::colisionPlataformas() {
    if (enElAire) return; // Colisiones verticales manejadas por caerEnPlataforma

    for (QGraphicsRectItem* plataforma : plataformas) {
        if (this->collidesWithItem(plataforma)) {
            setPos(oldPos); // Revertir posición horizontal
            moving = false;
            return;
        }
    }
}


void Homero::caerEnPlataforma() {
    if (!enElAire) return; // Si no está en el aire, no aplica gravedad.

    // Aplicar gravedad
    velocidadVertical += 1; // Acelera la caída con el tiempo.
    setPos(x(), y() + velocidadVertical);

    // Verificar colisiones con plataformas
    for (QGraphicsRectItem* plataforma : plataformas) {
        if (this->collidesWithItem(plataforma)) {
            // Homero aterriza
            setPos(x(), plataforma->y() - boundingRect().height()); // Ajustar para "pararse" sobre la plataforma.
            enElAire = false;
            velocidadVertical = 0; // Resetea la velocidad vertical.
            return; // Salir de la función, ya que ha aterrizado.
        }
    }
}

void Homero::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()){
    case Qt::Key_A:
    case Qt::Key_D:
    case Qt::Key_Space:
        keys[event->key()]=false;
        break;
    default:
        break;
    }
}

void Homero::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_A:
    case Qt::Key_D:
    case Qt::Key_Space:
        keys[event->key()]=true;
        break;
    default:
        break;
    }
}

Homero::~Homero(){

    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
}
