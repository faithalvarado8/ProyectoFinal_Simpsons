#include "Homero.h"
#include <QDebug>
#include <cmath>

Homero::Homero(QList<QGraphicsRectItem*> plataformas, QGraphicsScene* escena): indiceSprite(0), direccion('D'), plataformas(plataformas), enElAire(false), v0(58), angulo(65), escena(escena) {

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

    colisiones=new QTimer();
    connect(colisiones, &QTimer::timeout, this, &Homero::colisionPlataformas);
    colisiones->start(10);

    timerCaida=new QTimer();
    connect(timerCaida, &QTimer::timeout, this, &Homero::caida);

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
    else if (keys[Qt::Key_Space]){
        saltar();
    }

    // Actualizar la animación

    if (enElAire){
        if (direccion == 'A') {
            setPixmap(spritesSaltarIzquierda[1]);
        } else{
            setPixmap(spritesSaltarDerecha[1]);
        }
    }
    else if (moving) {
        if (direccion == 'A') {
            indiceSprite = (indiceSprite + 1) % spritesCaminarIzquierda.size();
            setPixmap(spritesCaminarIzquierda[indiceSprite]);
        } else{
            indiceSprite = (indiceSprite + 1) % spritesCaminarDerecha.size();
            setPixmap(spritesCaminarDerecha[indiceSprite]);
        }
    } else{
        indiceSprite = 1;
        if (direccion == 'A') {
            setPixmap(spritesCaminarIzquierda[indiceSprite]);
        } else{
            setPixmap(spritesCaminarDerecha[indiceSprite]);
        }
    }

    if (!timerSalto->isActive() && enElAire && !timerCaida->isActive()){
        timerCaida->start(5);
    }
}

void Homero::colisionPlataformas() {
    for (QGraphicsRectItem* plataforma : plataformas) {
        if (this->collidesWithItem(plataforma)) {
            QRectF rectPersonaje = boundingRect().translated(pos());
            QRectF rectPlataforma = plataforma->boundingRect().translated(plataforma->pos());

            if (rectPersonaje.top() <= rectPlataforma.bottom() && rectPersonaje.top() >= rectPlataforma.top()){
                if (timerSalto->isActive()){
                    timerSalto->stop();
                }
                if (enElAire){
                    timerCaida->start(5);
                }
            }

            if (rectPersonaje.bottom() >= rectPlataforma.top() && rectPersonaje.bottom() <= rectPlataforma.bottom()){
                enElAire=false;
                //setY(rectPlataforma.top() - rectPersonaje.height());
                if (timerSalto->isActive()){
                    timerSalto->stop();
                }
                if (timerCaida->isActive()){
                    timerCaida->stop();
                }
            }else{
                enElAire=true;
            }

            if (rectPersonaje.left() <= rectPlataforma.right() && rectPersonaje.left() >= rectPlataforma.left()){
                //setX(rectPlataforma.right());
                moving = false;
                if (timerSalto->isActive()){
                    timerSalto->stop();
                }
                if (enElAire){
                    timerCaida->start(5);
                }
            }else{
                moving = true;
            }

            if (rectPersonaje.right() >= rectPlataforma.left() && rectPersonaje.right() <= rectPlataforma.right()){
                //setX(rectPlataforma.left() - rectPersonaje.width());
                moving = false;
                if (timerSalto->isActive()){
                    timerSalto->stop();
                }
                if (enElAire){
                    timerCaida->start(5);
                }
            }else{
                moving = true;
            }
        }
    }
}

void Homero::saltar() {
    if (!enElAire) {
        x0=pos().x();
        y0=pos().y();
        nuevaX=x0;
        nuevaY=y0;
        t=0;
        angulo = qDegreesToRadians(angulo);
        hMax=(v0*v0*sin(angulo)*sin(angulo))/(2*9.8);
        enElAire = true;
        timerSalto->start(5);
    }
}

void Homero::actualizarSalto(){
    t+=0.02;

    if (nuevaY>hMax){
        nuevaY = y0 - (v0 * sin(angulo) * t - 0.5 * 9.8 * t * t);
    }else{
        nuevaY = y0 - (v0 * sin(angulo) * t + 0.5 * 9.8 * t * t);
    }

    if (direccion=='D'){
        nuevaX = x0 + v0 * cos(angulo) * t;
    }
    else{
        nuevaX = x0 - v0 * cos(angulo) * t;
    }
    setPos(nuevaX, nuevaY);
}

void Homero::caida(){
    t+=0.02;
    nuevaY = y0 + (v0*t + (0.5 * 9.8 * t * t));
    setY(nuevaY);
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

    if(timerSalto){
        timerSalto->stop();
        delete timerSalto;
        timerSalto=nullptr;
    }

    if (colisiones){
        colisiones->stop();
        delete colisiones;
        colisiones=nullptr;
    }

    if (timerCaida){
        timerCaida->stop();
        delete timerCaida;
        timerCaida=nullptr;
    }
}
