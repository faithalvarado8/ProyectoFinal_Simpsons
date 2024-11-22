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
        timerObstaculos->start(500);

        kingHomero = new KingHomero();
        escena->addItem(kingHomero);

        kingHomero->setFlag(QGraphicsItem::ItemIsFocusable);
        kingHomero->setFocus();

        connect(kingHomero, &KingHomero::moverHaciaArriba, this, &Nivel::sincronizarFondo);

        // Agregar a Marge en la parte superior
        margeSprite1 = new QGraphicsPixmapItem(QPixmap(":/Nivel2/Marge_Happy1.png"));
        margeSprite2 = new QGraphicsPixmapItem(QPixmap(":/Nivel2/Marge_Happy2.png"));

        if (margeSprite1->pixmap().isNull() || margeSprite2->pixmap().isNull()) {
            qDebug() << "Error al cargar los sprites de Marge";
            return;
        }

        margeSprite1->setPos(escena->width() / 2 - margeSprite1->pixmap().width() / 2,
                             escena->height() - edificioItem->pixmap().height() - margeSprite1->pixmap().height());
        margeSprite2->setPos(margeSprite1->x(), margeSprite1->y());

        margeSprite1->setVisible(false);
        margeSprite2->setVisible(false);
        escena->addItem(margeSprite1);

        timerMargeAnimacion = new QTimer(this);
        connect(timerMargeAnimacion, &QTimer::timeout, this, &Nivel::animarMarge);
        timerMargeAnimacion->start(500);

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

                murcielago=new Murcielago();
                escena->addItem(murcielago);
            }

        }
    }
}

void Nivel::showMarge() {
    // Actualiza la posición de King Homer y verifica si está cerca del final
    if (nivelSeleccionado == 2) {
        // Si King Homer está cerca de la parte superior del edificio (ejemplo: a 50 píxeles de distancia)
        if (kingHomero->pos().y() < (escena->height() - edificioItem->pixmap().height() - 750)) {
            margeSprite1->setVisible(true);
            margeSprite2->setVisible(true);
            margeSprite1->setZValue(2);
            margeSprite2->setZValue(2);
        } else {
            margeSprite1->setVisible(false);
            margeSprite2->setVisible(false);
        }
    }

    actualizarTiempo();
}

void Nivel::animarMarge() {
    if (margeSprite1->isVisible()) {
        if (escena->items().contains(margeSprite1)) {
            escena->removeItem(margeSprite1);
            escena->addItem(margeSprite2);
        } else {
            escena->removeItem(margeSprite2);
            escena->addItem(margeSprite1);
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
        textoTiempo = nullptr;
        delete timerMargeAnimacion;
        timerMargeAnimacion = nullptr;
        delete margeSprite1;
        margeSprite1 = nullptr;
        delete margeSprite2;
        margeSprite2 = nullptr;
    }

}

