#include "nivel.h"

Nivel::Nivel(short int nivelSeleccionado, QGraphicsScene * escena): nivelSeleccionado(nivelSeleccionado) {

    qDebug() << "NIVEL: " << nivelSeleccionado;

    if (nivelSeleccionado == 2) {
        qDebug() << "Entra 2";
        // Cargar la imagen del edificio
        qDebug() << "PASO 1";
        QPixmap edificio(":/Nivel2/Edificio.png"); // Asegúrate de que la ruta sea correcta
        qDebug() << "PASO 2";
        if (edificio.isNull()) {
            qDebug() << "Error: No se pudo cargar la imagen.";
            return; // Salir de la función o manejar el error
        }
        qDebug() << "PASO 3";
        escena->setBackgroundBrush(QBrush(QImage(":/Nivel2/Edificio.png").scaled(1280, 720)));
        QGraphicsPixmapItem* edificioItem = escena->addPixmap(edificio.scaled(2450, 7000, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        qDebug() << "PASO 4";
        // Posicionar el edificio en la parte inferior de la escena
        edificioItem->setPos(0, escena->height() - edificioItem->pixmap().height());
        qDebug() << "PASO 5";
        edificioItem->setZValue(0); // Asegúrate de que esté en el nivel correcto
        qDebug() << "PASO 6";
    }

    if (nivelSeleccionado==3){
        qDebug() << "Entra 3";

        escena->setBackgroundBrush(QBrush(QImage(":/Nivel3/fondoNivel3.jpg").scaled(1280, 720)));

        jugador = new Jugador("Bart");

        for (short int i=0; i<5; i++){
           objeto= new Objetos("arma");
           escena->addItem(objeto);
        }

        for (short int i=0; i<5; i++){
           objeto= new Objetos("pagina");
           escena->addItem(objeto);
        }

        // Enfocar personaje
        jugador->setFlag(QGraphicsItem::ItemIsFocusable);
        jugador->setFocus();

        escena->addItem(jugador);
    }

}

Nivel::~Nivel() {
    delete jugador;
    delete objeto;

}

