#include "Homero.h"

Homero::Homero(QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), indiceSprite(0), moviendoIzquierda(false), moviendoDerecha(false) {
    // Cargar la hoja de sprites
    QPixmap hojaSprites(":/Nivel1/Homero.png");
    if (hojaSprites.isNull()) {
        qDebug() << "Error: No se pudo cargar la hoja de sprites de Homero.";
        return;
    }

    int anchoSprite = hojaSprites.width() / 6;
    int altoSprite = hojaSprites.height();

    spritesCaminar = {hojaSprites.copy(0, 0, anchoSprite, altoSprite),
                      hojaSprites.copy(anchoSprite, 0, anchoSprite, altoSprite),
                      hojaSprites.copy(anchoSprite * 3, 0, anchoSprite, altoSprite)};

    spritesSaltar = {hojaSprites.copy(anchoSprite * 2, 0, anchoSprite, altoSprite),
                     hojaSprites.copy(anchoSprite * 4, 0, anchoSprite, altoSprite)};

    spriteCelebrar = hojaSprites.copy(anchoSprite * 5, 0, anchoSprite, altoSprite);

    // Establecer el sprite inicial
    setPixmap(spritesCaminar[0]);

    // Configurar el temporizador para las animaciones
    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Homero::actualizarAnimacion);
    timerAnimacion->start(100);
}

void Homero::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        moviendoIzquierda = true;
        setX(x() - velocidadMovimiento);
    } else if (event->key() == Qt::Key_D) {
        moviendoDerecha = true;
        setX(x() + velocidadMovimiento);
    }
}

void Homero::actualizarAnimacion() {
    if (moviendoIzquierda || moviendoDerecha) {
        indiceSprite = (indiceSprite + 1) % spritesCaminar.size();
        setPixmap(spritesCaminar[indiceSprite]);
    }
}
