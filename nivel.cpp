#include "nivel.h"
#include <random>
#include <cmath>
#include <QFile>

Nivel::Nivel(short int nivelSeleccionado, QGraphicsScene * escena): nivelSeleccionado(nivelSeleccionado), escena(escena), edificioItem(nullptr), yOffset(0), timerNivel(nullptr) {


    if (nivelSeleccionado == 1) {
        // escena->setBackgroundBrush(QBrush(QImage(":/Nivel1/PlataformasNivel.png").scaled(1280, 720)));
        escena->setBackgroundBrush(QBrush(QImage(":/Nivel1/FondoNivel1.png").scaled(1280, 720)));
        agregarPlataformas();

        homero = new Homero(plataformas, escena);
        homero->setFlag(QGraphicsItem::ItemIsFocusable);
        homero->setFocus();
        escena->addItem(homero);

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
    escena->addItem(plataforma);


    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(0, 15, 15, 704);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);


    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(15, 704, 1265, 16);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(1264, 15, 16, 690);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(416, 104, 91, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(324, 104, 31, 59);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(128, 164, 439, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(16, 608, 163, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(276, 608, 879, 15);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(16, 340, 159, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);
    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(280, 340, 63, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(176, 476, 220, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(276, 508, 31, 99);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(476, 476, 587, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(1032, 508, 31, 99);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(1204, 476, 61, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(476, 304, 103, 171);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(580, 304, 483, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(756, 268, 127, 35);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(788, 236, 95, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(820, 204, 63, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(820, 336, 31, 47);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(940, 336, 31, 47);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
    escena->addItem(plataforma);

    plataformas.append(plataforma);

    plataforma = new QGraphicsRectItem(852, 172, 412, 31);
    plataforma->setBrush(Qt::NoBrush);
    plataforma->setPen(Qt::NoPen);
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

    }

    else if(nivelSeleccionado==3){

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
    escena->setBackgroundBrush(QBrush(QImage(":/fondos/NivelCompletado.jpg").scaled(1280, 720)));
    eliminar();
}

void Nivel::gameOver(){
    escena->setBackgroundBrush(QBrush(QImage(":/fondos/GAME_OVER.png").scaled(1280, 720)));
    eliminar();
    emit juegoTerminado();
}

void Nivel::escribirArchivo(const QString &nombreArchivo, unsigned short int tiempoRestante){

    QFile archivo(nombreArchivo);
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        return;
    }

    // Crear un QTextStream para escribir en el archivo.
    QTextStream salida(&archivo);
    salida << 30-tiempoRestante;

    archivo.close();  // Cerrar el archivo.
}

void Nivel::agregarObstaculos(){
    obstaculo=new Obstaculo(this->escena, this);
    escena->addItem(obstaculo);
}

Nivel::~Nivel() {

    if (nivelSeleccionado==1){

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
