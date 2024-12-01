#include "Homero.h"
#include <QDebug>
#include <cmath>

Homero::Homero(QList<QGraphicsRectItem*> plataformas, QGraphicsScene* escena): indiceSprite(0),plataformas(plataformas), enElAire(false), v0(58), angulo(65), colisionX(false), escena(escena) {

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
        spritesCaminarDerecha.append(hojaCaminar.copy(i * anchoCaminar, 0, anchoCaminar, altoCaminar).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // Fila 1
        spritesCaminarIzquierda.append(hojaCaminar.copy(i * anchoCaminar, altoCaminar, anchoCaminar, altoCaminar).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // Fila 2
    }

    spritesSaltarDerecha = {hojaSaltar.copy(0, 0, anchoSaltar, altoSaltar).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation), hojaSaltar.copy(anchoSaltar, 0, anchoSaltar, altoSaltar).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation)}; // Fila 1
    spritesSaltarIzquierda = {hojaSaltar.copy(0, altoSaltar, anchoSaltar, altoSaltar).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation), hojaSaltar.copy(anchoSaltar, altoSaltar, anchoSaltar, altoSaltar).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation)}; // Fila 2

    spritesCelebrar = {hojaCelebrar.copy(0, 0, anchoCelebrar, altoCelebrar).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation), hojaCelebrar.copy(anchoCelebrar, 0, anchoCelebrar, altoCelebrar).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation)};

    setPixmap(spritesCaminarDerecha[1]);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Homero::actualizarAnimacion);
    timer->start(100);

    timerSalto=new QTimer();
    connect(timerSalto, &QTimer::timeout, this, &Homero::actualizarSalto);

    colisionesX=new QTimer();
    connect(colisionesX, &QTimer::timeout, this, &Homero::colisionPlataformasX);
    colisionesX->start(10);

    colisionesY=new QTimer();
    connect(colisionesY, &QTimer::timeout, this, &Homero::colisionPlataformasY);
    colisionesY->start(10);

    setPos(18, 548);
    setZValue(2);
}

void Homero::actualizarAnimacion() {

    moving = false;

    if (keys[Qt::Key_A] && !enElAire){
        setX(pos().x()-15);
        moving = true;
        direccion = 'A';
    }
    else if (keys[Qt::Key_D] && !enElAire) {
        setX(pos().x()+15);
        moving = true;
        direccion = 'D';
    }
    else if (keys[Qt::Key_Space] && !enElAire){
        saltar();
    }

    // Actualizar la animación

    if (enElAire){
        if (direccion == 'D') {
            setPixmap(spritesSaltarDerecha[1]);
        } else if (direccion == 'A') {
            setPixmap(spritesSaltarIzquierda[1]);
        }
    }
    else if (moving) {
        if (direccion == 'D') {
            indiceSprite = (indiceSprite + 1) % spritesCaminarDerecha.size();
            setPixmap(spritesCaminarDerecha[indiceSprite]);
        } else if (direccion == 'A') {
            indiceSprite = (indiceSprite + 1) % spritesCaminarIzquierda.size();
            setPixmap(spritesCaminarIzquierda[indiceSprite]);
        }
    } else{
        indiceSprite = 1;
        if (direccion == 'D') {
            setPixmap(spritesCaminarDerecha[indiceSprite]);
        } else if (direccion == 'A') {
            setPixmap(spritesCaminarIzquierda[indiceSprite]);
        }
    }
}

void Homero::colisionPlataformasY() {
    for (QGraphicsRectItem* plataforma : plataformas) {
        if (this->collidesWithItem(plataforma)) {
            QRectF rectPersonaje = boundingRect().translated(pos());
            QRectF rectPlataforma = plataforma->boundingRect().translated(plataforma->pos());

            if (rectPersonaje.top() <= rectPlataforma.bottom() && rectPersonaje.top() >= rectPlataforma.top()){
                //setY(pos().y()+15);
                if (timerSalto->isActive()){
                    timerSalto->stop();
                }
            }
            else if (rectPersonaje.bottom() >= rectPlataforma.top() && rectPersonaje.bottom() <= rectPlataforma.bottom()){
                //setY(plataforma->pos().y() - boundingRect().height());
                enElAire=false;
                if (timerSalto->isActive()){
                    timerSalto->stop();
                }
            }
        }
    }
}

void Homero::colisionPlataformasX() {
    for (QGraphicsRectItem* plataforma : plataformas) {
        if (this->collidesWithItem(plataforma)) {
            QRectF rectPersonaje = boundingRect().translated(pos());
            QRectF rectPlataforma = plataforma->boundingRect().translated(plataforma->pos());

            if (rectPersonaje.left() <= rectPlataforma.right() && rectPersonaje.left() >= rectPlataforma.left()){
                //setX(rectPlataforma.right());
                moving = false;
                if (timerSalto->isActive()){
                    timerSalto->stop();
                }
            }
            else if (rectPersonaje.right() >= rectPlataforma.left() && rectPersonaje.right() <= rectPlataforma.right()){
                //setX(rectPlataforma.left() - boundingRect().width());
                if (timerSalto->isActive()){
                    timerSalto->stop();
                }
                moving = false;
            }else{
                moving = true;
            }
        }
    }
}

void Homero::saltar() {
    x0=pos().x();
    y0=pos().y();
    t=0;
    angulo = qDegreesToRadians(angulo);
    enElAire = true;
    timerSalto->start(5);
}

void Homero::actualizarSalto(){
    t+=0.02;
    qreal nuevaX = x0 + v0 * cos(angulo) * t;
    qreal nuevaY = y0 - (v0 * sin(angulo) * t - 0.5 * 9.8 * t * t); // Física de caída libre
    setPos(nuevaX, nuevaY);
}

void Homero::keyReleaseEvent(QKeyEvent *event) {
    if (keys.contains(event->key())) {
        keys[event->key()] = false;
    }
}

void Homero::keyPressEvent(QKeyEvent *event){
    if (keys.contains(event->key())) {
        keys[event->key()] = true;
    }
}

Homero::~Homero(){

    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
}
