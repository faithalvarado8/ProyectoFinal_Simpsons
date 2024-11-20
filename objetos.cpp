#include "objetos.h"

Objetos::Objetos(string objeto) {
    if (objeto=="arma"){
        sprites= QPixmap(":/Nivel3/Objetos3.png");

        QPixmap sprite = sprites.copy(0, 29, 31, 29);

        setPixmap(sprite.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        int random_number1 = rand() % 1190, random_number2 = rand() % 430;
        //setPos(random_number1+45, random_number2+45);
        setPos(50, 55);
        setZValue(0);
    }

    if (objeto=="pagina"){
        sprites= QPixmap(":/Nivel3/Objetos3.png");

        QPixmap sprite = sprites.copy(0, 0, 31, 29);

        setPixmap(sprite.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        int random_number1 = rand() % 1190, random_number2 = rand() % 430;
        //setPos(random_number1+45, random_number2+45);
        setPos(1190+45, 430+45);
        setZValue(0);
    }
}
