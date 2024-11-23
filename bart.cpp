#include "bart.h"

Bart::Bart() {
    spritesLado= QPixmap(":/Nivel3/BartLado.png");
    spritesArribaAbajo = QPixmap(":/Nivel3/BartFrente.png");
    spritesArma=QPixmap(":/Nivel3/BartArma2.png");

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
    setZValue(1);
}

void Bart::actualizarAnimacion(){
    bool moving = false;

    qDebug() << "Test";

    if (keys[Qt::Key_A] && pos().x()>45){
        setPos(x()-10,y());
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
    }
    else if (keys[Qt::Key_D] && pos().x()<1190){
        setPos(x()+10,y());
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
    }

    else if (keys[Qt::Key_W] && pos().y()>10){
        setPos(x(),y()-10);
        sprites = spritesArribaAbajo;
        ancho = anchoArribaAbajo;
        alto = altoArribaAbajo;
        fila=0;
        moving = true;
    }
    else if (keys[Qt::Key_S] && pos().y()<430){
        setPos(x(),y()+10);
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
    }

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

    }else {
        columna = 0;
    }

    // Calcular la posicion del cuadro en la hoja de sprites
    int x = columna * ancho;
    int y = fila * alto;

    // Actualizar la imagen del personaje
    QPixmap sprite = sprites.copy(x, y, ancho, alto);
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
    if (event -> key() == Qt::Key_Space){
        disparar=false;
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

    if (event -> key() == Qt::Key_Space){
        disparar=true;
    }
}

void Bart::municiones(){

}
