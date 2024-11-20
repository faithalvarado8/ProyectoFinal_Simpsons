#include "nivel.h"

Nivel::Nivel(short int nivelSeleccionado, QGraphicsScene * escena): nivelSeleccionado(nivelSeleccionado), escena(escena), edificioItem(nullptr), yOffset(0) {

    qDebug() << "NIVEL: " << nivelSeleccionado;

    if (nivelSeleccionado == 2) {
        QPixmap edificio(":/Nivel2/Edificio.png");
        if (edificio.isNull()) {
            qDebug() << "Error: No se pudo cargar la imagen.";
            return;
        }

        edificioItem = escena->addPixmap(edificio.scaled(800, 4881, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        escena->setBackgroundBrush(QBrush(QColor(202, 199, 199)));

        edificioItem->setPos(80, escena->height() - edificioItem->pixmap().height());
        edificioItem->setZValue(0);

        // Crear un temporizador para el efecto parallax
        QTimer *parallaxTimer = new QTimer(this);
        connect(parallaxTimer, &QTimer::timeout, this, &Nivel::moverEdificio);
        parallaxTimer->start(16); // ~60 FPS

        KingHomero *kingHomero = new KingHomero();
        escena->addItem(kingHomero);

        kingHomero->setFlag(QGraphicsItem::ItemIsFocusable);
        kingHomero->setFocus();
    }


    if (nivelSeleccionado==3){

        escena->setBackgroundBrush(QBrush(QImage(":/Nivel3/fondoNivel3.png").scaled(1280, 720)));

        bart = new Bart();

        for (short int i=0; i<5; i++){
           objeto= new Objetos("arma");
           escena->addItem(objeto);
        }

        for (short int i=0; i<5; i++){
           objeto= new Objetos("pagina");
           escena->addItem(objeto);
        }

        // Enfocar personaje
        bart->setFlag(QGraphicsItem::ItemIsFocusable);
        bart->setFocus();

        escena->addItem(bart);
    }

}

void Nivel::moverEdificio() {

    if (!edificioItem) return;

    // Obtener la posición actual
    yOffset -= 2; // Velocidad del desplazamiento hacia arriba

    // Detener el desplazamiento al llegar a la parte superior
    if (yOffset <= -(edificioItem->pixmap().height() - escena->height())) {
        yOffset = -(edificioItem->pixmap().height() - escena->height()); // Fijar en el límite superior
        return; // No mover más
    }

    // Actualizar posición
    edificioItem->setPos(230, escena->height() - edificioItem->pixmap().height() - yOffset);
}



Nivel::~Nivel() {
    if (nivelSeleccionado==3){
        delete bart;
        delete objeto;
    }
    if (nivelSeleccionado==2){
        delete kingHomero;
    }
    //delete objeto;

}

