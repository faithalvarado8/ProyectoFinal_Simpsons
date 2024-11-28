#include "Homero.h"

Homero::Homero(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), indiceSprite(0), moviendoDerecha(false), moviendoIzquierda(false), saltando(false) {
    // Cargar las hojas de sprites
    QPixmap hojaCaminar(":/Nivel1/HomeroWalk.png");
    QPixmap hojaSaltar(":/Nivel1/HomeroJump.png");
    QPixmap hojaCelebrar(":/Nivel1/HomeroCelebrate.png");

    if (hojaCaminar.isNull() || hojaSaltar.isNull() || hojaCelebrar.isNull()) {
        qDebug() << "Error: No se pudieron cargar las imágenes de Homero.";
        return;
    }

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

    setPixmap(spritesCaminarDerecha[0]);

    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Homero::actualizarAnimacion);
    timerAnimacion->start(100);
}

void Homero::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_D:
        moviendoDerecha = true;
        moviendoIzquierda = false;
        setX(x() + velocidadMovimiento);
        break;

    case Qt::Key_A:
        moviendoIzquierda = true;
        moviendoDerecha = false;
        setX(x() - velocidadMovimiento);
        break;

    case Qt::Key_Space:
        if (!saltando) {
            saltando = true;
            indiceSprite = 0;
        break;

    default:
        break;
    }
}
}

void Homero::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_D) {
        moviendoDerecha = false;
    } else if (event->key() == Qt::Key_A) {
        moviendoIzquierda = false;
    }
}

void Homero::actualizarAnimacion(){
    if (moviendoDerecha) {
        indiceSprite = (indiceSprite + 1) % spritesCaminarDerecha.size();
        setPixmap(spritesCaminarDerecha[indiceSprite]);
    } else if (moviendoIzquierda) {
        indiceSprite = (indiceSprite + 1) % spritesCaminarIzquierda.size();
        setPixmap(spritesCaminarIzquierda[indiceSprite]);
    } else if (saltando) {
        if (moviendoDerecha) {
            setPixmap(spritesSaltarDerecha[indiceSprite]);
        } else if (moviendoIzquierda) {
            setPixmap(spritesSaltarIzquierda[indiceSprite]);
        }
        indiceSprite = (indiceSprite + 1) % 2;
        saltando = false;
    }
}
