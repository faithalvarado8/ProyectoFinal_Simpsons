#include "jugador.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>

Jugador::Jugador(string nombre){
    if (nombre=="Bart"){
        spritesLado= QPixmap(":/Nivel3/BartLado.png");
        spritesArribaAbajo = QPixmap(":/Nivel3/BartFrente.png");

        ancho=117;
        alto=187;

        // Dimensiones de cada hoja de sprites
        anchoLado = 117;
        altoLado = 187;
        anchoArribaAbajo = 45;
        altoArribaAbajo = 88;


        sprites = spritesLado; // Iniciar con la hoja de movimientos laterales
        ancho = anchoLado;
        alto = altoLado;
        columna = 0;
        fila = 0;

        QPixmap sprite = sprites.copy(0, 0, ancho, alto);

        setPixmap(sprite.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &Jugador::actualizarAnimacion);
        timer->start(75);

        setPos(0,0);
        setZValue(1);
    }
}

void Jugador::actualizarAnimacion(){
    bool moving = false;

    qDebug() << "Test";

    if (keys[Qt::Key_Left] && pos().x()>0){
        setPos(x()-10,y());

        sprites = spritesLado;
        ancho = anchoLado;
        alto = altoLado;
        fila=1;
        moving = true;
    }
    if (keys[Qt::Key_Right] && pos().x()<1230){
        setPos(x()+10,y());

        sprites = spritesLado;
        ancho = anchoLado;
        alto = altoLado;
        fila=0;
        moving = true;
    }

    if (keys[Qt::Key_Up] && pos().y()>0){
        setPos(x(),y()-10);
        sprites = spritesArribaAbajo;
        ancho = anchoArribaAbajo;
        alto = altoArribaAbajo;
        fila=0;
        moving = true;
    }
    if (keys[Qt::Key_Down] && pos().y()<640){
        setPos(x(),y()+10);

        sprites = spritesArribaAbajo;
        ancho = anchoArribaAbajo;
        alto = altoArribaAbajo;
        fila=1;
        moving = true;
    }

    if (moving){
        // Avanzar al siguiente cuadro en la hoja de sprites
        if (ancho == anchoArribaAbajo){
             columna = (columna + 1) % 3;
        }else{
            columna = (columna + 1) % 4;
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


void Jugador::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()){
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        keys[event->key()]=false;
        break;
    default:
        break;
    }

}

void Jugador::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        keys[event->key()]=true;
        break;
    default:
        break;
    }

    if (event -> key() == Qt::Key_Space){
        //disparar
    }
}
