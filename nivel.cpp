#include "nivel.h"

Nivel::Nivel(short int nivelSeleccionado, QGraphicsScene * escena): nivelSeleccionado(nivelSeleccionado), escena(escena), edificioItem(nullptr), yOffset(0) {

    qDebug() << "NIVEL: " << nivelSeleccionado;

    if (nivelSeleccionado == 2) {
        // Cargar la imagen del edificio
        QPixmap edificio(":/Nivel2/Edificio.png"); // Asegúrate de que la ruta sea correcta
        if (edificio.isNull()) {
            qDebug() << "Error: No se pudo cargar la imagen.";
            return; // Salir de la función o manejar el error
        }

        // Agregar el edificio a la escena
        edificioItem = escena->addPixmap(edificio.scaled(800, 4881, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        escena->setBackgroundBrush(QBrush(QColor(202, 199, 199))); // Fondo negro para contraste

        // Posicionar el edificio en la parte inferior de la escena
        edificioItem->setPos(80, escena->height() - edificioItem->pixmap().height());
        edificioItem->setZValue(0); // Asegúrate de que esté en el nivel correcto

        // Crear un temporizador para el efecto parallax
        QTimer *parallaxTimer = new QTimer(this);
        connect(parallaxTimer, &QTimer::timeout, this, &Nivel::moverEdificio);
        parallaxTimer->start(16); // ~60 FPS


        // Crear jugador
        jugador = new Jugador("Homero");
        jugador->setPos(100, 4860); // Posición inicial de Homero
        escena->addItem(jugador);
        jugador->setFlag(QGraphicsItem::ItemIsFocusable);
        jugador->setFocus();
    }

    if (nivelSeleccionado==3){

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

// void Nivel::actualizarCamara() {
//     if (jugador) {
//         // Mantener la cámara enfocada en Homero
//         int cameraY = jugador->pos().y() - (escena->height() * 2 / 3);
//         cameraY = qMax(255, cameraY); // Limitar el movimiento vertical
//         cameraY = qMin(4860, cameraY); // Limitar el movimiento vertical

//         // Ajustar la posición de la escena
//         escena->setSceneRect(0, cameraY, escena->width(), escena->height());
//         escena->setPos(0, -cameraY); // Mover la escena hacia arriba
//     }
// }

Nivel::~Nivel() {
    delete jugador;
    delete objeto;

}

