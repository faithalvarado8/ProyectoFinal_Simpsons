#include "objetos.h"

Objetos::Objetos(string objeto, unsigned short int cont) {
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

        if (cont==1){
            setPos(1200, 480);
        }
        else if (cont==2){
            setPos(50, 55);
        }
        else if (cont==3){
            setPos(150, 155);
        }
        else if (cont==4){
            setPos(250, 255);
        }
        else{
            setPos(350, 355);
        }

        setZValue(0);
    }
}
