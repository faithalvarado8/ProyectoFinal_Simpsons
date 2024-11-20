#include "objetos.h"

Objetos::Objetos(string objeto) {
    if (objeto=="arma"){
        sprites= QPixmap(":/Nivel3/Objetos3.png");

        QPixmap sprite = sprites.copy(0, 29, 31, 29);

        setPixmap(sprite.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        int random_number1 = rand() % 1150, random_number2 = rand() % 425;
        setPos(random_number1+50, random_number2+55);

        setZValue(0);
    }

    if (objeto=="pagina"){
        sprites= QPixmap(":/Nivel3/Objetos3.png");

        QPixmap sprite = sprites.copy(0, 0, 31, 29);

        setPixmap(sprite.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        int random_number1 = rand() % 1150, random_number2 = rand() % 425;
        setPos(random_number1+50, random_number2+55);
        setZValue(0);
    }
}
