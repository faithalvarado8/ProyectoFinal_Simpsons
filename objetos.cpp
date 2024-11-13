#include "objetos.h"

Objetos::Objetos(string objeto) {
    if (objeto=="arma"){
        sprites= QPixmap(":/Nivel3/Objetos3.png");

        QPixmap sprite = sprites.copy(0, 29, 31, 29);

        setPixmap(sprite.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        int random_number1 = rand() % 1249, random_number2 = rand() % 691;
        setPos(random_number1, random_number2);
        setZValue(0);
    }

    if (objeto=="pagina"){
        sprites= QPixmap(":/Nivel3/Objetos3.png");

        QPixmap sprite = sprites.copy(0, 0, 31, 29);

        setPixmap(sprite.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        int random_number1 = rand() % 1249, random_number2 = rand() % 691;
        setPos(random_number1, random_number2);
        setZValue(0);
    }
}
