#include "bart.h"

Bart::Bart(QGraphicsScene* escena, QList<QGraphicsPixmapItem*> tumbasEscena) : timer(nullptr), timerDisparo(nullptr), tumbasEscena(tumbasEscena), escena(escena) {
    numMuniciones=0;
    disparar=false;
    spritesLado= QPixmap(":/Nivel3/BartLado.png");
    spritesArribaAbajo = QPixmap(":/Nivel3/BartFrente.png");
    spritesArma=QPixmap(":/Nivel3/BartArma2.png");

    timerDisparo = new QTimer(this);
    connect(timerDisparo, &QTimer::timeout, this, &Bart::actualizarDisparo);
    timerDisparo->start(16);

    // Dimensiones de cada hoja de sprites
    anchoLado = 117;
    altoLado = 188;
    anchoArribaAbajo = 45;
    altoArribaAbajo = 89;
    anchoArma= 124;
    altoArma= 138;

    sprites = spritesLado; // Iniciar con la hoja de movimientos laterales
    ancho = anchoLado;
    alto = altoLado;
    columna = 0;
    fila = 0;

    QPixmap sprite = sprites.copy(0, 0, ancho, alto);

    setPixmap(sprite.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Bart::actualizarAnimacion);
    timer->start(110);

    setPos(45,10);
    oldPos=QPointF(pos());
    nuevaPos=QPointF(pos());
    setZValue(1);
}

void Bart::actualizarAnimacion(){
    moving = false;
    oldPos=QPointF(pos());

    if (keys[Qt::Key_A] && pos().x()>45){
        nuevaPos=pos()-QPointF(15,0);
        if (disparar){
            sprites = spritesArma;
            ancho = anchoArma;
            alto = altoArma;
            fila=1;
        }
        else{
            sprites = spritesLado;
            ancho = anchoLado;
            alto = altoLado;
            fila=1;
        }

        moving = true;
        direccion='A';
    }
    else if (keys[Qt::Key_D] && pos().x()<1190){
        nuevaPos=pos()+QPointF(15,0);
        if (disparar){
            sprites = spritesArma;
            ancho = anchoArma;
            alto = altoArma;
            fila=2;
        }
        else{
            sprites = spritesLado;
            ancho = anchoLado;
            alto = altoLado;
            fila=0;
        }
        moving = true;
        direccion='D';
    }

    else if (keys[Qt::Key_W] && pos().y()>10){
        nuevaPos=pos()-QPointF(0,15);
        sprites = spritesArribaAbajo;
        ancho = anchoArribaAbajo;
        alto = altoArribaAbajo;
        fila=0;
        moving = true;
        direccion='W';
    }
    else if (keys[Qt::Key_S] && pos().y()<430){
        nuevaPos=pos()+QPointF(0,15);
        if (disparar){
            sprites = spritesArma;
            ancho = anchoArma;
            alto = altoArma;
            fila=0;
        }
        else{
            sprites = spritesArribaAbajo;
            ancho = anchoArribaAbajo;
            alto = altoArribaAbajo;
            fila=1;
        }
        moving = true;
        direccion='S';
    }

    // Simular el movimiento para detectar colisiones
    setPos(nuevaPos);
    colisionTumba();

    if (moving){
        // Avanzar al siguiente cuadro en la hoja de sprites
        if (ancho == anchoArribaAbajo){
            columna = (columna + 1) % 3;
        }
        else if (ancho == anchoLado){
            columna = (columna + 1) % 4;
        }
        else if (ancho==anchoArma){
            if (fila==0){
                columna = (columna + 1) % 3;
            }
            else{
                columna = (columna + 1) % 4;
            }
        }

    }
    else {
        if (disparar){
            if (direccion=='A'){
                sprites = spritesArma;
                ancho = anchoArma;
                alto = altoArma;
                fila=1;
            }
            else if (direccion=='D'){
                sprites = spritesArma;
                ancho = anchoArma;
                alto = altoArma;
                fila=2;
            }
            else if (direccion=='S'){
                sprites = spritesArma;
                ancho = anchoArma;
                alto = altoArma;
                fila=0;
            }
        }else{
            if (direccion=='A'){
                sprites = spritesLado;
                ancho = anchoLado;
                alto = altoLado;
                fila=1;
            }
            else if (direccion=='D'){
                sprites = spritesLado;
                ancho = anchoLado;
                alto = altoLado;
                fila=0;
            }
            else if (direccion=='S'){
                sprites = spritesArribaAbajo;
                ancho = anchoArribaAbajo;
                alto = altoArribaAbajo;
                fila=1;
            }
        }

        columna = 0;

    }

    // Calcular la posicion del cuadro en la hoja de sprites
    spriteX = columna * ancho;
    spriteY = fila * alto;

    // Actualizar la imagen del personaje
    QPixmap sprite = sprites.copy(spriteX, spriteY, ancho, alto);
    setPixmap(sprite.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


void Bart::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()){
    case Qt::Key_A:
    case Qt::Key_D:
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_Space:
        keys[event->key()]=false;
        break;
    default:
        break;
    }
}

void Bart::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_A:
    case Qt::Key_D:
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_Space:
        keys[event->key()]=true;
        break;
    default:
        break;
    }

    if (event -> key() == Qt::Key_Space && disparar){
        lanzarMunicion();
    }
}

void Bart::municiones(){
    numMuniciones+=3;
    disparar=true;
}

void Bart::lanzarMunicion(){

    numMuniciones-=1;

    if (numMuniciones==0){
        disparar=false;
    }

    municion= new QGraphicsPixmapItem(QPixmap(":/Nivel3/Disparo.png").scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    municion->setZValue(2);
    escena->addItem(municion);

    QPointF posInicial;
    if (direccion == 'A') posInicial = QPointF(x() - 13, y() + 36);
    else if (direccion == 'D') posInicial = QPointF(x() + 62, y() + 36);
    else if (direccion == 'W') posInicial = QPointF(x(), y());
    else posInicial = QPointF(x() + 7, y() + 36);

    municion->setPos(posInicial);

    // Guardar datos de la munición
    municion->setData(0, posInicial); // Posición inicial
    municion->setData(1, direccion); // Dirección
    municion->setData(2, 0.0);       // Tiempo acumulado

    listaMuniciones.append(municion);
}

void Bart::actualizarDisparo(){

    for (int i = 0; i < listaMuniciones.size(); ++i) {
        QGraphicsPixmapItem* mun = listaMuniciones[i];

        QPointF posInicial = mun->data(0).toPointF(); // Recuperar posición inicial guardada
        char dir = mun->data(1).toChar().toLatin1(); // Recuperar dirección guardada
        double t = mun->data(2).toDouble();          // Recuperar tiempo acumulado

        t += 0.016;
        double desplazamiento = 350 * t - 0.5 * 120 * t * t; // x(t)=x0+v0*t-0.5*a*t^2

        QPointF nuevaPos;

        if (dir == 'A') nuevaPos = QPointF(posInicial.x() - desplazamiento, posInicial.y());
        else if (dir == 'D') nuevaPos = QPointF(posInicial.x() + desplazamiento, posInicial.y());
        else if (dir == 'W') nuevaPos = QPointF(posInicial.x(), posInicial.y() - desplazamiento);
        else nuevaPos = QPointF(posInicial.x(), posInicial.y() + desplazamiento);

        if (desplazamiento > 510 || nuevaPos.x() < 46 || nuevaPos.x() > 1222 || nuevaPos.y() < 47 || nuevaPos.y() > 500) {
            escena->removeItem(mun);
            delete mun;
            mun=nullptr;
            listaMuniciones.removeAt(i);
            continue;
        }

        // Actualiza posición y tiempo acumulado
        mun->setPos(nuevaPos);
        mun->setData(2, t); // Guardar nuevo tiempo acumulado
    }
}

void Bart::colisionTumba(){

    for (QGraphicsPixmapItem* tumba : tumbasEscena) {
        if (this->collidesWithItem(tumba)) {
            setPos(oldPos);
            moving=false;
            return;
        }
    }
}

QList<QGraphicsPixmapItem*> Bart::getMuniciones(){
    return listaMuniciones;
}

void Bart::eliminarMunicion(int i){
    delete listaMuniciones[i];
    listaMuniciones[i]=nullptr;
    listaMuniciones.removeAt(i);
}

Bart::~Bart(){

    if (timer) {
        timer->stop();
        disconnect(timer, &QTimer::timeout, this, &Bart::actualizarAnimacion);
        delete timer;
        timer = nullptr;
    }

    for (QGraphicsPixmapItem* mun : listaMuniciones) {
        escena->removeItem(mun);
        delete mun;
        mun=nullptr;
    }
    listaMuniciones.clear();

    if (timerDisparo) {
        timerDisparo->stop();
        disconnect(timerDisparo, &QTimer::timeout, this, &Bart::actualizarDisparo);
        delete timerDisparo;
        timerDisparo = nullptr;
    }
}
