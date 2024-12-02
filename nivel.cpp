#include "nivel.h"
#include <random>
#include <cmath>
#include <QFile>
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>

Nivel::Nivel(short int nivelSeleccionado, QGraphicsScene * escena): nivelSeleccionado(nivelSeleccionado), escena(escena), edificioItem(nullptr), yOffset(0), timerNivel(nullptr), puntaje(0) {


    if (nivelSeleccionado == 1) {
        escena->setBackgroundBrush(QBrush(QImage(":/Nivel1/FondoNivel1.png").scaled(1280, 720)));
        agregarPlataformas();

        homero = new Homero(plataformas, escena);
        homero->setFlag(QGraphicsItem::ItemIsFocusable);
        homero->setFocus();
        escena->addItem(homero);
        QList<Enemigo*> enemigos;

        // Agregar a Krusty
        Enemigo* krusty1 = new Enemigo(400, 630);
        krusty1->setPos(500, 548);
        krusty1->setZValue(2);
        enemigos.append(krusty1);

        Enemigo* krusty2 = new Enemigo(50, 400);
        krusty2->setPos(200, 646);
        krusty2->setZValue(2);
        enemigos.append(krusty2);

        Enemigo* krusty3 = new Enemigo(600, 930);
        krusty3->setPos(900, 416);
        krusty3->setZValue(2);
        enemigos.append(krusty3);

        Enemigo* krusty4 = new Enemigo(970, 1200);
        krusty4->setPos(1100, 114);
        krusty4->setZValue(2);
        enemigos.append(krusty4);

        tiempoRestante = 100;

        timerNivel = new QTimer(this);
        connect(timerNivel, &QTimer::timeout, this, &Nivel::actualizarTiempo);
        timerNivel->start(1000);

        textoTiempo = new QGraphicsTextItem("Time: 100");
        textoTiempo->setDefaultTextColor(Qt::black);
        textoTiempo->setFont(QFont("Arial", 20, QFont::Bold));
        textoTiempo->setPos(30, 20);
        escena->addItem(textoTiempo);

        imagenVidas= QPixmap (":/Nivel3/Vida.png");
        imagenRecortada = imagenVidas.copy(0, 0, 43, 12).scaled(130, 130, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        vidasActuales= new QGraphicsPixmapItem(imagenRecortada);
        escena->addItem(vidasActuales);
        vidasActuales->setPos(280,20);

        for (Enemigo* enemigo : enemigos) {
            escena->addItem(enemigo);
        }

        Objetos* switchEvil = new Objetos(":/Nivel1/SwicheKrusty-EVIL.png", 100, 530);
        Objetos* switchGood = new Objetos(":/Nivel1/SwicheKrusty-GOOD.png", 1200, 80);

        escena->addItem(switchEvil);
        escena->addItem(switchGood);

        QPixmap mueble(":/Nivel1/mueble.png");
        itemMueble = escena->addPixmap(mueble.scaled(150, 230, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        itemMueble->setPos(220, 418);
        itemMueble->setZValue(1);

        colisionTimer= new QTimer(this);
        connect(colisionTimer, &QTimer::timeout, this, &Nivel::homeroColision);
        colisionTimer->start(100);
    }

    if (nivelSeleccionado == 2) {
        QPixmap edificio(":/Nivel2/Edificio.png");
        if (edificio.isNull()) {
            return;
        }

        edificioItem = escena->addPixmap(edificio.scaled(800, 4881, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        escena->setBackgroundBrush(QBrush(QColor(202, 199, 199)));
        edificioItem->setPos(240, escena->height() - edificioItem->pixmap().height());
        edificioItem->setZValue(0);

        timerObstaculos = new QTimer(this);
        connect(timerObstaculos, &QTimer::timeout, this, &Nivel::agregarObstaculos);
        timerObstaculos->start(450);

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

        posicionesInvalidas= {QPointF(800, 400), QPointF(1090, 150), QPointF(150, 155), QPointF(700, 200), QPointF(250, 420), QPointF(45,10)};
        agregarTumbas(12);

        posicionesInvalidas.removeOne(QPointF(800, 400));
        posicionesInvalidas.removeOne(QPointF(1090, 150));
        posicionesInvalidas.removeOne(QPointF(150, 155));
        posicionesInvalidas.removeOne(QPointF(700, 200));
        posicionesInvalidas.removeOne(QPointF(250, 420));
        posicionesInvalidas.removeOne(QPointF(45,10));

        tiempoRestante = 100;

        timerNivel = new QTimer(this);
        connect(timerNivel, &QTimer::timeout, this, &Nivel::actualizarTiempo);
        timerNivel->start(1000);

        textoTiempo = new QGraphicsTextItem("Time: 100");
        textoTiempo->setDefaultTextColor(Qt::black);
        textoTiempo->setFont(QFont("Arial", 22, QFont::Bold));
        textoTiempo->setPos(55, 530);
        escena->addItem(textoTiempo);

        contadorPaginas = new QGraphicsTextItem("x 0");
        contadorPaginas->setDefaultTextColor(Qt::black);
        contadorPaginas->setFont(QFont("Arial", 22, QFont::Bold));
        contadorPaginas->setPos(95, 567);
        escena->addItem(contadorPaginas);

        imagenVidas= QPixmap (":/Nivel3/Vida.png");
        imagenRecortada = imagenVidas.copy(0, 0, 43, 12).scaled(140, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        vidasActuales= new QGraphicsPixmapItem(imagenRecortada);
        escena->addItem(vidasActuales);
        vidasActuales->setPos(60,620);

        arma= new Objetos(posicionesInvalidas);
        escena->addItem(arma);

        paginaCont= new Objetos(6);
        escena->addItem(paginaCont);

        cont=0;
        pagina= new Objetos(cont);
        escena->addItem(pagina);

        bart = new Bart(escena, tumbasEscena);

        bart->setFlag(QGraphicsItem::ItemIsFocusable);
        bart->setFocus();
        escena->addItem(bart);

        timerZombies= new QTimer(this);
        connect(timerZombies, &QTimer::timeout, this, &Nivel::agregarZombies);
        timerZombies->start(10000);

        murcielago=new Enemigo(cont);
        escena->addItem(murcielago);
        murcielagos.append(murcielago);

        colisionTimer = new QTimer(this);
        connect(colisionTimer, &QTimer::timeout, this, &Nivel::verificarColisiones);
        colisionTimer->start(100);
    }
}

void Nivel::verificarColisiones() {

    QList<QGraphicsPixmapItem*> municiones=bart->getMuniciones();

    for (int j=0; j<municiones.size(); j++) {
        QList<QGraphicsItem*> colisionesConMunicion = municiones[j]->collidingItems();
        for (QGraphicsItem* item : colisionesConMunicion) {
            bool colisionManejada = false;
            for (int i=0; i<murcielagos.size(); i++) {
                if (item == murcielagos[i] && !colisionManejada){
                    delete murcielagos[i];
                    murcielagos[i]=nullptr;
                    murcielagos.removeAt(i);

                    bart->eliminarMunicion(j);
                    colisionManejada = true;
                    puntaje+=2000;
                    break;
                }
            }
            if (colisionManejada){
                break;
            }
            for (int i=0; i<zombies.size(); i++) {
                if (item == zombies[i] && !colisionManejada){
                    delete zombies[i];
                    zombies[i]=nullptr;
                    zombies.removeAt(i);

                    bart->eliminarMunicion(j);
                    puntaje+=1500;
                    break;
                }
            }
        }
    }

    QList<QGraphicsItem*> colisiones = bart->collidingItems();
    for (QGraphicsItem* item : colisiones) {
        if (item == arma) {
            escena->removeItem(arma);
            delete arma;
            arma=nullptr;

            bart->municiones();
            puntaje+=250;

            arma= new Objetos(posicionesInvalidas);
            escena->addItem(arma);
        }
        if (item == pagina && contadorPaginas) {
            escena->removeItem(pagina);
            delete pagina;
            pagina=nullptr;
            cont+=1;

            contadorPaginas->setPlainText(QString("x %1").arg(cont));

            if (cont<5){
                pagina= new Objetos(cont);
                escena->addItem(pagina);

                murcielago=new Enemigo(cont);
                escena->addItem(murcielago);
                murcielagos.append(murcielago);
            }else{
                ganarNivel();
            }
        }

        for (int i=0; i<murcielagos.size(); i++) {
            if (item == murcielagos[i]){
                bart->perderVida();

                delete murcielagos[i];
                murcielagos[i]=nullptr;
                murcielagos.removeAt(i);

                actualizarVidasBart();
                puntaje-=200;

                if (bart->getVidas() == 0) {
                    gameOver();
                }
            }
        }
        for (int i=0; i<zombies.size(); i++) {
            if (item == zombies[i]){
                bart->perderVida();

                delete zombies[i];
                zombies[i]=nullptr;
                zombies.removeAt(i);

                actualizarVidasBart();
                puntaje-=200;

                if (bart->getVidas() == 0) {
                    gameOver();
                }
            }
        }
    }
}

void Nivel::agregarPlataformas(){
    QGraphicsRectItem* plataforma = new QGraphicsRectItem(0, 0, 1280, 15); // x, y, ancho, alto
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::green);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);


    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(0, 15, 15, 704);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::green);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);


    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(15, 704, 1265, 16);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::green);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(1264, 15, 16, 690);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::green);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    /*
    plataforma = new QGraphicsRectItem(416, 104, 91, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(324, 104, 31, 59);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataformas.append(plataforma);*/
    /*
    plataforma = new QGraphicsRectItem(324, 104, 31, 80);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);
    plataformas.append(plataforma);*/
/*
    plataforma = new QGraphicsRectItem(0, 164, 380, 31); // RECORTAR EN X
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);
    plataforma = new QGraphicsRectItem(0, 120, 1280, 10); // RECORTAR EN X
    plataforma->setBrush(Qt::blue);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(16, 608, 163, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);*/

    plataforma = new QGraphicsRectItem(0, 608, 179, 31);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(276, 608, 879, 15);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma = new QGraphicsRectItem(270, 608, 900, 15);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(16, 340, 159, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma = new QGraphicsRectItem(0, 340, 175, 31);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);
    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(340, 340, 63, 31); //CAMBIANDO
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma = new QGraphicsRectItem(330, 350, 95, 31); //CAMBIANDO
    plataforma->setBrush(Qt::blue);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(176, 476, 220, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma = new QGraphicsRectItem(176, 476, 210, 31);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(276, 508, 31, 99);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(476, 476, 587, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(1032, 508, 31, 99);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(1204, 476, 61, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma = new QGraphicsRectItem(1180, 470, 150, 20);
    plataforma->setBrush(Qt::blue);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(476, 304, 103, 171);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma = new QGraphicsRectItem(476, 304, 103, 180);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(580, 304, 483, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma = new QGraphicsRectItem(560, 323, 515, 15);
    plataforma->setBrush(Qt::green);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    /*
    plataforma = new QGraphicsRectItem(756, 268, 127, 35);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(788, 236, 95, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(820, 204, 63, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);
    plataformas.append(plataforma);*/

    plataforma = new QGraphicsRectItem(820, 336, 31, 47);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(940, 336, 31, 47);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::yellow);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(852, 172, 412, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    plataforma->setBrush(Qt::green);
    plataforma->setPen(QPen(Qt::black));
    escena->addItem(plataforma);

    plataformas.append(plataforma);

}

void Nivel::actualizarTiempo() {
    if (tiempoRestante > 0) {
        tiempoRestante--;
        textoTiempo->setPlainText(QString("Time: %1").arg(tiempoRestante));
        if (tiempoRestante <= 5) {
            textoTiempo->setDefaultTextColor(Qt::red);
        }
    } else {
        gameOver();
    }
}

void Nivel::sincronizarFondo(int dy) {

    if (kingHomero->getVidas()==0){
        gameOver();
        return;
    }

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

            QList<QGraphicsItem *> items = escena->items();
            for (QGraphicsItem *item : items) {
                if (dynamic_cast<Obstaculo *>(item)) {
                    escena->removeItem(item);
                    delete item;
                }
            }
            timerNivel->stop();
            kingHomero->setPos(640,515);
            kingHomero->iniciarCelebracion();

            ganarNivel();
            return;
        }
    }
}

void Nivel::agregarTumbas(int numTumbas){

    int x,y;
    double distancia;
    QPointF nuevaPos;

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
            for (const QPointF& pos : posicionesInvalidas) {
                // Calcular la distancia entre las tumbas
                distancia = std::sqrt(std::pow(x - pos.x(), 2) + std::pow(y - pos.y(), 2));

                // Verificar si la distancia entre las tumbas es menor que el tamaño de una tumba (80 px)
                if (distancia < 145) {
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
        posicionesInvalidas.append(nuevaPos);
        tumbasEscena.append(tumba);
    }
}

void Nivel::actualizarVidasBart() {
    delete vidasActuales;
    vidasActuales = nullptr;

    int vidas = bart->getVidas();
    if (vidas > 0) {
        // Actualizar el sprite de vidas según el número restante
        int offsetY = (3 - vidas) * 12; // Cambiar según tu hoja de sprites
        imagenRecortada = imagenVidas.copy(0, offsetY, 43, 12).scaled(140, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        vidasActuales = new QGraphicsPixmapItem(imagenRecortada);
        escena->addItem(vidasActuales);
        vidasActuales->setPos(60, 620);
    }
}

void Nivel::agregarZombies(){
    zombie= new Enemigo(posicionesInvalidas, bart);
    escena->addItem(zombie);
    zombies.append(zombie);
}

void Nivel::eliminar(){
    if (nivelSeleccionado==1){
        if (homero){
            delete homero;
            homero=nullptr;
        }
        for (QGraphicsRectItem* plataforma : plataformas) {
            if (plataforma){
                delete plataforma;
                plataforma=nullptr;
            }
        }
        plataformas.clear();

        for (Enemigo* krusty : krustys) {
            if (krusty){
                delete krusty;
                krusty=nullptr;
            }
        }
        krustys.clear();

        if (switchEvil){
            delete switchEvil;
            switchEvil=nullptr;
        }
        if (switchGood){
            delete switchGood;
            switchGood=nullptr;
        }
        if (itemMueble){
            delete itemMueble;
            itemMueble=nullptr;
        }

    }
    else if(nivelSeleccionado==2){

        if (timerNivel){
            timerNivel->stop();
            delete timerNivel;
            timerNivel = nullptr;
        }

        if (timerObstaculos){
            timerObstaculos->stop();
            delete timerObstaculos;
            timerObstaculos = nullptr;
        }

        if (textoTiempo){
            delete textoTiempo;
            textoTiempo = nullptr;
        }

        if (edificioItem){
            delete edificioItem;
            edificioItem=nullptr;
        }

        if (kingHomero){
            delete kingHomero;
            kingHomero = nullptr;
        }
    }

    else{
        if (colisionTimer){
            colisionTimer->stop();
            delete colisionTimer;
            colisionTimer=nullptr;
        }

        if(timerZombies){
            timerZombies->stop();
            delete timerZombies;
            timerZombies = nullptr;
        }

        for (Enemigo* zombie : zombies) {

            if (zombie){
                delete zombie;
                zombie=nullptr;
            }
        }
        zombies.clear();

        if (bart){
            delete bart;
            bart=nullptr;
        }

        if (vidasActuales){
            delete vidasActuales;
            vidasActuales=nullptr;
        }

        if (timerNivel){
            timerNivel->stop();
            delete timerNivel;
            timerNivel = nullptr;
        }

        if (textoTiempo){
            delete textoTiempo;
            textoTiempo = nullptr;
        }

        if (arma){
            delete arma;
            arma=nullptr;
        }

        if (pagina){
            delete pagina;
            pagina=nullptr;
        }

        for (Enemigo* murcielago : murcielagos) {
            if (murcielago){
                delete murcielago;
                murcielago=nullptr;
            }
        }
        murcielagos.clear();

        for (QGraphicsPixmapItem* tumba : tumbasEscena) {
            if (tumba){
                tumbasEscena.removeOne(tumba);
                delete tumba;
                tumba=nullptr;
            }
        }
        tumbasEscena.clear();

        if (paginaCont){
            delete paginaCont;
            paginaCont=nullptr;
        }

        if (contadorPaginas){
            delete contadorPaginas;
            contadorPaginas=nullptr;
        }
    }
    escena->clear();
}

void Nivel::ganarNivel(){
    eliminar();
    escena->setBackgroundBrush(QBrush(QImage(":/fondos/NivelCompletado.jpg").scaled(1280, 720)));
    escribirArchivo();
    QTimer::singleShot(1100, this, &Nivel::mostrarRanking);
}

void Nivel::gameOver(){
    eliminar();
    escena->setBackgroundBrush(QBrush(QImage(":/fondos/GAME_OVER.png").scaled(1280, 720)));
    QTimer::singleShot(1100, this, &Nivel::mostrarRanking);
}

void Nivel::mostrarRanking(){
    escena->setBackgroundBrush(QBrush(Qt::black));
    QGraphicsTextItem* textoItem = new QGraphicsTextItem("TOP 5 PUNTAJES");
    QFont font("Courier New", 55);
    font.setBold(true);
    font.setItalic(true);
    textoItem->setFont(font);
    textoItem->setDefaultTextColor(Qt::cyan);
    textoItem->setPos(331, 50);
    escena->addItem(textoItem);

    if (nivelSeleccionado==1){
        escribirDatos("Nivel1.txt", false );
    }
    else if (nivelSeleccionado==2){
        escribirDatos("Nivel2.txt", true);
    }
    else{
        escribirDatos("Nivel3.txt", false);
    }
    emit juegoTerminado();
}

void Nivel::escribirDatos(const QString &nombreArchivo, bool ascendente){
    QFile archivo(nombreArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&archivo);
    int yPos = 200; // Posición inicial en el eje Y para mostrar el texto

    while (!in.atEnd()) {
        QString linea = in.readLine();  // Lee una línea del archivo
        QGraphicsTextItem *textoItem = new QGraphicsTextItem(linea);
        puntos.append(textoItem);
    }
    ordenarPuntos(puntos, ascendente);

    QFont font("Courier New", 25);
    font.setBold(true);
    font.setItalic(false);

    unsigned short int cont= puntos.size();
    if (cont>=5){
        cont=5;
    }

    for (int i = 0; i < cont; ++i) {
        QGraphicsTextItem* item = puntos[i];
        item->setFont(font);
        if (item->toPlainText().toInt() == ultimoPuntaje) {
            item->setDefaultTextColor(Qt::red); // Resaltar en amarillo
        } else {
            item->setDefaultTextColor(Qt::white); // Color estándar
        }
        escena->addItem(item);
        item->setPos(550, yPos);
        yPos += 60;
    }
    archivo.close();
}

void Nivel::ordenarPuntos(QList<QGraphicsTextItem *> &puntos, bool ascendente) {
    std::sort(puntos.begin(), puntos.end(), [ascendente](QGraphicsTextItem* a, QGraphicsTextItem* b) {
        int valorA = a->toPlainText().toInt();
        int valorB = b->toPlainText().toInt();
        return ascendente ? valorA < valorB : valorA > valorB;
    });
}

void Nivel::escribirArchivo(){

    if (nivelSeleccionado==1){
        ultimoPuntaje = puntaje + tiempoRestante;
        QFile archivo("Nivel1.txt");
        if (!archivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            return;
        }

        // Crear un QTextStream para escribir en el archivo.
        QTextStream salida(&archivo);
        salida <<puntaje+tiempoRestante<<"\n";

        archivo.close();  // Cerrar el archivo.
    }
    else if (nivelSeleccionado==2){
        ultimoPuntaje = 30- tiempoRestante;
        QFile archivo("Nivel2.txt");
        if (!archivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            return;
        }

        // Crear un QTextStream para escribir en el archivo.
        QTextStream salida(&archivo);
        salida << 30-tiempoRestante<<"\n";

        archivo.close();  // Cerrar el archivo.
    }
    else{
        ultimoPuntaje = puntaje + tiempoRestante;
        QFile archivo("Nivel3.txt");
        if (!archivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            return;
        }

        // Crear un QTextStream para escribir en el archivo.
        QTextStream salida(&archivo);
        salida <<puntaje+tiempoRestante<<"\n";

        archivo.close();  // Cerrar el archivo.
    }

}

void Nivel::agregarObstaculos(){
    obstaculo=new Obstaculo(this->escena, this);
    escena->addItem(obstaculo);
}

void Nivel::homeroColision(){

    QList<QGraphicsItem*> colisiones = homero->collidingItems();

    // Verifica colisiones con enemigos
    for (QGraphicsItem* item : colisiones) {
        if (krustys.contains(static_cast<Enemigo*>(item))) { // Verifica si el objeto está en la lista krustys
            for (int i = 0; i < krustys.size(); i++) {
                if (item == krustys[i]) {
                    homero->perderVida();

                    delete krustys[i];
                    krustys[i] = nullptr;
                    krustys.removeAt(i);

                    actualizarVidasKrusty();
                    tiempoRestante -= 10;

                    if (homero->getVidas() == 0) {
                        gameOver();
                        return; // Termina si se acaba el juego
                    }
                }
            }
        }
    }

    // Verifica colisiones con objetos
    if (colisiones.contains(switchGood)) { // Si el objeto switchGood está en las colisiones
        ganarNivel();
    }
}

void Nivel::actualizarVidasKrusty(){
    delete vidasActuales;
    vidasActuales = nullptr;

    int vidas = homero->getVidas();
    if (vidas > 0) {
        // Actualizar el sprite de vidas según el número restante
        int offsetY = (3 - vidas) * 12; // Cambiar según tu hoja de sprites
        imagenRecortada = imagenVidas.copy(0, offsetY, 43, 12).scaled(140, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        vidasActuales = new QGraphicsPixmapItem(imagenRecortada);
        escena->addItem(vidasActuales);
        vidasActuales->setPos(60, 620);
    }
}

Nivel::~Nivel() {

    if (nivelSeleccionado==1){
        if (homero){
            delete homero;
            homero=nullptr;
        }
        for (QGraphicsRectItem* plataforma : plataformas) {
            if (plataforma){
                delete plataforma;
                plataforma=nullptr;
            }
        }
        plataformas.clear();

        for (Enemigo* krusty : krustys) {
            if (krusty){
                delete krusty;
                krusty=nullptr;
            }
        }
        krustys.clear();

        if (switchEvil){
            delete switchEvil;
            switchEvil=nullptr;
        }
        if (switchGood){
            delete switchGood;
            switchGood=nullptr;
        }
        if (itemMueble){
            delete itemMueble;
            itemMueble=nullptr;
        }
    }

    else if (nivelSeleccionado==2){
        if (edificioItem){
            delete edificioItem;
            edificioItem=nullptr;
        }

        if (kingHomero){
            delete kingHomero;
            kingHomero = nullptr;
        }

        if (timerObstaculos){
            timerObstaculos->stop();
            delete timerObstaculos;
            timerObstaculos = nullptr;
        }

        if (timerNivel){
            timerNivel->stop();
            delete timerNivel;
            timerNivel = nullptr;
        }

        if (textoTiempo){
            delete textoTiempo;
            textoTiempo = nullptr;
        }
    }

    else if (nivelSeleccionado==3){

        if (colisionTimer){
            colisionTimer->stop();
            delete colisionTimer;
            colisionTimer=nullptr;
        }

        for (Enemigo* zombie : zombies) {
            if (zombie){
                delete zombie;
                zombie=nullptr;
            }
        }
        zombies.clear();

        if (bart){
            delete bart;
            bart=nullptr;
        }

        if (vidasActuales){
            delete vidasActuales;
            vidasActuales=nullptr;
        }

        if (timerNivel){
            timerNivel->stop();
            delete timerNivel;
            timerNivel = nullptr;
        }

        if (textoTiempo){
            delete textoTiempo;
            textoTiempo = nullptr;
        }

        if (arma){
            delete arma;
            arma=nullptr;
        }

        if (pagina){
            delete pagina;
            pagina=nullptr;
        }

        for (Enemigo* murcielago : murcielagos) {
            if (murcielago){
                delete murcielago;
                murcielago=nullptr;
            }
        }
        murcielagos.clear();

        for (QGraphicsPixmapItem* tumba : tumbasEscena) {
            if (tumba){
                delete tumba;
                tumba=nullptr;
            }
        }
        tumbasEscena.clear();

        if (paginaCont){
            delete paginaCont;
            paginaCont=nullptr;
        }

        if (contadorPaginas){
            delete contadorPaginas;
            contadorPaginas=nullptr;
        }
    }
    escena->clear();
}
