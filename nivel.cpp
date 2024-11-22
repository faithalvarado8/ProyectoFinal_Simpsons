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
        edificioItem->setPos(240, escena->height() - edificioItem->pixmap().height());
        edificioItem->setZValue(0);

        timerObstaculos = new QTimer(this);
        connect(timerObstaculos, &QTimer::timeout, [this]() {
            Obstaculo *obstaculo = new Obstaculo(this->escena, this);
            this->escena->addItem(obstaculo);
        });
        timerObstaculos->start(2000);

        kingHomero = new KingHomero();
        escena->addItem(kingHomero);

        kingHomero->setFlag(QGraphicsItem::ItemIsFocusable);
        kingHomero->setFocus();

        connect(kingHomero, &KingHomero::moverHaciaArriba, this, &Nivel::sincronizarFondo);

        tiempoRestante = 30;
        timerNivel = new QTimer(this);
        connect(timerNivel, &QTimer::timeout, this, &Nivel::actualizarTiempo);
        timerNivel->start(1000);

        textoTiempo = new QGraphicsTextItem("Time: 30");
        textoTiempo->setDefaultTextColor(Qt::black);
        textoTiempo->setFont(QFont("Arial", 22, QFont::Bold));
        textoTiempo->setPos(10, 10);
        escena->addItem(textoTiempo);
    }


    if (nivelSeleccionado==3){

        escena->setBackgroundBrush(QBrush(QImage(":/Nivel3/fondoNivel3.png").scaled(1280, 720)));

        bart = new Bart();

        arma= new Objetos("arma");
        escena->addItem(arma);

        pagina= new Objetos("pagina", 1);
        escena->addItem(pagina);

        bart->setFlag(QGraphicsItem::ItemIsFocusable);
        bart->setFocus();

        escena->addItem(bart);

        murcielago=new Murcielago();
        escena->addItem(murcielago);

        QTimer *colisionTimer = new QTimer(this);
        connect(colisionTimer, &QTimer::timeout, this, &Nivel::verificarColisiones);
        colisionTimer->start(100); // Verificar colisiones cada 100 ms
    }
}


void Nivel::verificarColisiones() {
    QList<QGraphicsItem*> colisiones = bart->collidingItems();
    for (QGraphicsItem* item : colisiones) {
        if (item == arma) {
            escena->removeItem(arma);
            delete arma;

            arma= new Objetos("arma");
            escena->addItem(arma);
        }
        if (item == pagina) {
            escena->removeItem(pagina);
            delete pagina;

            if (cont<6){
                cont+=1;
                pagina= new Objetos("pagina", cont);
                escena->addItem(pagina);
            }

        }
    }
}


void Nivel::actualizarTiempo() {
    if (tiempoRestante > 0) {
        tiempoRestante--;
        textoTiempo->setPlainText(QString("Time: %1").arg(tiempoRestante));
        if (tiempoRestante <= 5) {
            textoTiempo->setDefaultTextColor(Qt::red);
        }
    } else {
        timerNivel->stop();

        imagenGameOver = new QGraphicsPixmapItem(QPixmap(":/fondos/GAME_OVER.png"));
        imagenGameOver->setPos(escena->width() / 2 - imagenGameOver->pixmap().width() / 2,
                               escena->height() / 2 - imagenGameOver->pixmap().height() / 2);
        escena->addItem(imagenGameOver);
        imagenGameOver->setZValue(3);

        qDebug() << "King Homer no logró llegar a la cima a tiempo.";
    }
}

void Nivel::sincronizarFondo(int dy) {

    if (!edificioItem || !kingHomero) return;
    yOffset += dy;

    if (yOffset < -(edificioItem->pixmap().height() - escena->height())) {
        yOffset = -(edificioItem->pixmap().height() - escena->height());
    } else if (yOffset > 0) {
        yOffset = 0;
    }

    edificioItem->setPos(240, escena->height() - edificioItem->pixmap().height() - yOffset);

    int nuevaY = kingHomero->y() + dy;

    if (nuevaY >= 50 && nuevaY <= escena->height() - kingHomero->pixmap().height() && nuevaY <= 50) {
        kingHomero->setY(nuevaY);
    }

    if (yOffset <= -(edificioItem->pixmap().height() - escena->height())) {
        if (timerObstaculos->isActive()) {
            timerObstaculos->stop();
            timerNivel->stop();
            qDebug() << "Generación de obstáculos detenida.";
            qDebug() << "¡Nivel completado!";
        }
    }
}


Nivel::~Nivel() {
    if (nivelSeleccionado==3){
        delete bart;
        delete arma;
        if (pagina){
            delete pagina;
        }
        delete murcielago;
    }
    if (nivelSeleccionado==2){
        delete kingHomero;
        kingHomero = nullptr;
        delete timerObstaculos;
        timerObstaculos = nullptr;
        delete timerNivel;
        escena->removeItem(textoTiempo);
        delete textoTiempo;
    }
    //delete objeto;

}

