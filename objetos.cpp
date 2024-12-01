#include "objetos.h"

Objetos::Objetos(const QString& imagen, int x, int y) {
    sprites = QPixmap(imagen);
    setPixmap(sprites.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setPos(x, y);
    setZValue(1);
}


Objetos::Objetos(unsigned short int cont) {

    sprites= QPixmap(":/Nivel3/Objetos3.png");

    QPixmap sprite = sprites.copy(0, 0, 31, 29);

    setPixmap(sprite.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    if (cont==0){
        setPos(800, 400);
    }
    else if (cont==1){
        setPos(1090, 150);
    }
    else if (cont==2){
        setPos(150, 155);
    }
    else if (cont==3){
        setPos(700, 200);
    }
    else if (cont==4){
        setPos(250, 420);
    }
    else{
        setPos(65,575);
    }

    setZValue(0);

}


Objetos::Objetos(QList<QPointF> posicionesInvalidas){

    sprites = QPixmap(":/Nivel3/Objetos3.png");

    QPixmap sprite = sprites.copy(0, 29, 31, 29);

    setPixmap(sprite.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    bool posicionValida = false;
    int random_number1, random_number2;

    while (!posicionValida) {
        random_number1 = rand() % 1150;
        random_number2 = rand() % 425;
        posicionValida = true;
        for (const QPointF& pos : posicionesInvalidas) {
            // Calcular la distancia entre las tumbas
            double distancia = std::sqrt(std::pow( (random_number1+50) - pos.x(), 2) + std::pow((random_number2+55) - pos.y(), 2));
            if (distancia < 80) {
                posicionValida = false;
                break;
            }
        }
    }

    setPos(random_number1+50, random_number2+55);

    setZValue(0);

}

Objetos::~Objetos(){}
