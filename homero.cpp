#include "Homero.h"
#include <QDebug>
#include <cmath>

Homero::Homero(QList<QGraphicsRectItem*> plataformas, QGraphicsScene* escena): indiceSprite(0),plataformas(plataformas), enElAire(false), v0(30), angulo(45), colisionX(false), escena(escena) {

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

    setPixmap(spritesCaminarDerecha[1].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));

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
            setPixmap(spritesSaltarDerecha[1].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else if (direccion == 'A') {
            setPixmap(spritesSaltarIzquierda[1].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
    else if (moving) {
        if (direccion == 'D') {
            indiceSprite = (indiceSprite + 1) % spritesCaminarDerecha.size();
            setPixmap(spritesCaminarDerecha[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else if (direccion == 'A') {
            indiceSprite = (indiceSprite + 1) % spritesCaminarIzquierda.size();
            setPixmap(spritesCaminarIzquierda[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    } else{
        indiceSprite = 1;
        if (direccion == 'D') {
            setPixmap(spritesCaminarDerecha[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else if (direccion == 'A') {
            setPixmap(spritesCaminarIzquierda[indiceSprite].scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}

void Homero::colisionPlataformasY() {
    for (QGraphicsRectItem* plataforma : plataformas) {
        if (this->collidesWithItem(plataforma)) {
            QRectF rectPersonaje = boundingRect().translated(pos());
            QRectF rectPlataforma = plataforma->boundingRect().translated(plataforma->pos());

            if (rectPersonaje.top() <= rectPlataforma.bottom() && rectPersonaje.top() >= rectPlataforma.top()){
                setY(pos().y()+15);
            }
            else if (rectPersonaje.bottom() >= rectPlataforma.top() && rectPersonaje.bottom() <= rectPlataforma.bottom()){
                setY(plataforma->pos().y() - boundingRect().height());
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
                setX(pos().x()+15);
                moving = false;
            }
            else if (rectPersonaje.right() >= rectPlataforma.left() && rectPersonaje.right() <= rectPlataforma.right()){
                setX(pos().x()-15);
                moving = false;
            }else{
                moving = true;
            }
        }
    }
}

void Homero::saltar() {
    x0=pos().x();
    y0=pos().x();
    t=0;
    timerSalto->start(1000);
}

void Homero::actualizarSalto(){
    t+=1;
    setX(x0+(v0*cos(angulo)*t));
    setY(y0+(v0*sin(angulo)*t)+(0.5*9.8*t*t));
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
