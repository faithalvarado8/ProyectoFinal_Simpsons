#include "nivel.h"
#include <random>
#include <cmath>

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
        kingHomero->agregarIndicadorVidaALaEscena();
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

        arma= new Objetos("arma");
        escena->addItem(arma);

        pagina= new Objetos("pagina", 1);
        escena->addItem(pagina);

        agregarTumbas(13);

        bart = new Bart(escena, tumbasEscena);

        bart->setFlag(QGraphicsItem::ItemIsFocusable);
        bart->setFocus();
        escena->addItem(bart);

        murcielago=new Enemigo(1);
        escena->addItem(murcielago);
        murcielagos.append(murcielago);

        colisionTimer = new QTimer(this);
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
            arma=nullptr;

            bart->municiones();

            arma= new Objetos("arma");
            escena->addItem(arma);
        }
        if (item == pagina) {
            escena->removeItem(pagina);
            delete pagina;
            pagina=nullptr;

            if (cont<6){
                cont+=1;
                pagina= new Objetos("pagina", cont);
                escena->addItem(pagina);

                if (cont<=5){
                    murcielago=new Enemigo(cont);
                    escena->addItem(murcielago);
                    murcielagos.append(murcielago);
                }
            }
        }

        for (Enemigo* murcielago : murcielagos) {
            if (item == murcielago){
                bart->perderVida();

                escena->removeItem(murcielago);
                delete murcielago;
                murcielago=nullptr;

                if (bart->getVidas() == 0) {
                    escena->removeItem(bart);
                    delete bart;
                    bart=nullptr;

                    if (arma){
                        escena->removeItem(arma);
                        delete arma;
                        arma=nullptr;
                    }
                    if (pagina){
                        escena->removeItem(pagina);
                        delete pagina;
                        pagina=nullptr;
                    }
                    for (Enemigo* murcielago : murcielagos) {
                        if (murcielago){
                            escena->removeItem(murcielago);
                            delete murcielago;
                            murcielago=nullptr;
                        }
                    }
                    for (QGraphicsPixmapItem* tumba : tumbasEscena) {
                        if (tumba){
                            escena->removeItem(tumba);
                            delete tumba;
                            tumba=nullptr;
                        }
                    }
                    escena->setBackgroundBrush(QBrush(QImage(":/fondos/GAME_OVER.png").scaled(1280, 720)));
                    colisionTimer->stop();
                    return;
                }
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
            qDebug() << "Generación de obstáculos detenida";
            qDebug() << "¡Nivel completado!";
            kingHomero->setPos(640,515);
            kingHomero->iniciarCelebracion();
        }
    }
}

void Nivel::agregarTumbas(int numTumbas){

    std::random_device rd;
    std::mt19937 generador(rd());
    std::uniform_int_distribution<int> posX(50, 1190);
    std::uniform_int_distribution<int> posY(30, 425);
    std::uniform_int_distribution<int> sprite(0, 5);

    tumbas.append(QPixmap(":/Nivel3/Tumbas.png").copy(0, 0, 864, 1577).scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    tumbas.append(QPixmap(":/Nivel3/Tumbas.png").copy(864, 0, 864, 1577).scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    tumbas.append(QPixmap(":/Nivel3/Tumbas.png").copy(1728, 0,864, 1577).scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    tumbas.append(QPixmap(":/Nivel3/Tumbas.png").copy(0, 1577,864, 1577).scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    tumbas.append(QPixmap(":/Nivel3/Tumbas.png").copy(864, 1577,864, 1577).scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    tumbas.append(QPixmap(":/Nivel3/Tumbas.png").copy(1728, 1577,864, 1577).scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    for (int i=0; i<numTumbas; i++){
        posicionValida = false;
        while (!posicionValida) {
            x=posX(generador);
            y=posY(generador);
            nuevaPos = QPointF(x, y);
            posicionValida = true;
            for (const QPointF& pos : posicionesTumbas) {
                // Calcular la distancia entre las tumbas
                distancia = std::sqrt(std::pow(x - pos.x(), 2) + std::pow(y - pos.y(), 2));

                // Verificar si la distancia entre las tumbas es menor que el tamaño de una tumba (80 px)
                if (distancia < 120) {
                    posicionValida = false;
                    break;
                }
            }
        }

        tumba=new QGraphicsPixmapItem;
        spriteTumba=sprite(generador);
        tumba->setPixmap(tumbas[spriteTumba]);
        tumba->setPos(nuevaPos);
        tumba->setZValue(1);
        escena->addItem(tumba);
        posicionesTumbas.append(nuevaPos);
        tumbasEscena.append(tumba);
    }
}

void Nivel::gameOver(){

}

Nivel::~Nivel() {
    if (nivelSeleccionado==3){

        if (bart){
            escena->removeItem(bart);
            delete bart;
            bart = nullptr;
        }
        if (arma){
            escena->removeItem(arma);
            delete arma;
            arma = nullptr;
        }
        if (pagina){
            escena->removeItem(pagina);
            delete pagina;
            pagina = nullptr;
        }

        for (Enemigo* murcielago : murcielagos) {
            if (murcielago){
                escena->removeItem(murcielago);
                delete murcielago;
                murcielago=nullptr;
            }
        }
        for (QGraphicsPixmapItem* tumba : tumbasEscena) {
            if (tumba){
                escena->removeItem(tumba);
                delete tumba;
                tumba=nullptr;
            }
        }

        if (colisionTimer) {
            colisionTimer->stop();
            disconnect(colisionTimer, &QTimer::timeout, this, &Nivel::verificarColisiones);
            delete colisionTimer;
            colisionTimer = nullptr;
        }

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

