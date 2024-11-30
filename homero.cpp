#include "Homero.h"
#include <QDebug>

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
    timer->start(110);

    setPos(18,540);
    setZValue(2);
}

void Homero::actualizarAnimacion(){

    const int LIMITE_IZQUIERDO = 20; // Límite izquierdo de la pantalla
    const int LIMITE_DERECHO = 1260; // Límite derecho
    const int LIMITE_SUPERIOR = 0; // Límite superior
    const int LIMITE_INFERIOR = 644; // Límite inferior
    moving = false;

    //NUEVO
    if (!enElAire) {
        enElAire = true;
        for (auto plataforma : plataformas) {
            // Verifica si Homero está directamente encima de la plataforma.
            if (collidesWithItem(plataforma)) {
                QRectF rectHomero = this->boundingRect(); // Obtiene el rectángulo de Homero.
                QRectF rectPlataforma = plataforma->boundingRect(); // Obtiene el rectángulo de la plataforma.

                // Verifica si Homero está tocando la plataforma por debajo.
                if (rectHomero.bottom() <= rectPlataforma.top() && rectHomero.bottom() > rectPlataforma.top() - 5) {
                    enElAire = false;
                    velocidadVertical = 0; // Detener la caída
                    setPos(x(), rectPlataforma.top() - rectHomero.height()); // Alinea Homero encima de la plataforma
                    break;
                }
            }
        }
    }

    // if (!enElAire) {
    //     // Revisar si está sobre una plataforma
    //     enElAire = true;
    //     for (auto plataforma : plataformas) {
    //         if (collidesWithItem(plataforma)) {
    //             enElAire = false;
    //             velocidadVertical = 0; // Detenemos la caída
    //             break;
    //         }
    //     }
    // }

    if (enElAire) {
        // Aplicar gravedad si está en el aire
        velocidadVertical += 0.5; // Incrementamos la velocidad hacia abajo
        setPos(x(), y() + velocidadVertical);
    }

    if (keys[Qt::Key_A]){
        if (x() > LIMITE_IZQUIERDO) { // Verifica el límite izquierdo
            setPos(x() - 15, y());
        }
        moving = true;
        direccion='A';
    }

    if (keys[Qt::Key_D]){
        if (x() + pixmap().width() < LIMITE_DERECHO) { // Verifica el límite derecho
            setPos(x() + 15, y());
        }
        moving = true;
        direccion='D';
    }

    if (keys[Qt::Key_W]) {
        if (y() > LIMITE_SUPERIOR) { // Verifica el límite superior
            setPos(x(), y() - 10);
        }
        moving = true;
        direccion = 'W';
    }

    if (keys[Qt::Key_S]) {
        if (y() + pixmap().height() < LIMITE_INFERIOR) { // Verifica el límite inferior
            setPos(x(), y() + 10);
        }
        moving = true;
        direccion = 'S';
    }

    if (keys[Qt::Key_Space] && !enElAire) {
        saltar();
    }

    if (moving){
        if (direccion=='D') {
            indiceSprite = (indiceSprite + 1) % spritesCaminarDerecha.size();
            setPixmap(spritesCaminarDerecha[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else if (direccion=='A') {
            indiceSprite = (indiceSprite + 1) % spritesCaminarIzquierda.size();
            setPixmap(spritesCaminarIzquierda[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }else{
        indiceSprite = 1;
        if (direccion=='D') {
            setPixmap(spritesCaminarDerecha[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else if (direccion=='A') {
            setPixmap(spritesCaminarIzquierda[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}

void Homero::saltar() {
    enElAire = true; // Homero está en el aire
    velocidadVertical = -15; // Impulso inicial hacia arriba
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
