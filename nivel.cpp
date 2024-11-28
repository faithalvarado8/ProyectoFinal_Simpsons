#include "nivel.h"
#include <random>
#include "obstaculo.h"
#include <cmath>

Nivel::Nivel(short int nivelSeleccionado, QGraphicsScene * escena): nivelSeleccionado(nivelSeleccionado), escena(escena), edificioItem(nullptr), yOffset(0) {

    qDebug() << "NIVEL: " << nivelSeleccionado;

    if (nivelSeleccionado == 1) {
        QPixmap fondo(":/Nivel1/FondoNivel1.png");
        if (fondo.isNull()) {
            qDebug() << "Error: No se pudo cargar la imagen del fondo del nivel 1.";
            return;
        }
        escena->setBackgroundBrush(QBrush(fondo.scaled(1280, 720, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)));

        Homero *homero = new Homero();
        escena->addItem(homero);
        homero->setPos(20,510);
        homero->setZValue(3);
        homero->setScale(1.2);
        homero->setFlag(QGraphicsItem::ItemIsFocusable);
        homero->setFocus();
    }

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

        posicionesInvalidas= {QPointF(800, 400), QPointF(1090, 150), QPointF(150, 155), QPointF(700, 200), QPointF(250, 420), QPointF(45,10)};
        agregarTumbas(12);

        tiempoRestante = 60;

        timerNivel = new QTimer(this);
        connect(timerNivel, &QTimer::timeout, this, &Nivel::actualizarTiempo);
        timerNivel->start(1000);

        textoTiempo = new QGraphicsTextItem("Time: 60");
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

        pagina= new Objetos(1);
        escena->addItem(pagina);

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

            arma= new Objetos(posicionesInvalidas);
            escena->addItem(arma);
        }
        if (item == pagina && contadorPaginas) {
            escena->removeItem(pagina);
            delete pagina;
            pagina=nullptr;

            contadorPaginas->setPlainText(QString("x %1").arg(cont));

            if (cont<6){
                cont+=1;
                pagina= new Objetos(cont);
                escena->addItem(pagina);

                if (cont<=5){
                    murcielago=new Enemigo(cont);
                    escena->addItem(murcielago);
                    murcielagos.append(murcielago);
                }
            }
        }

        for (int i=0; i<murcielagos.size(); i++) {
            if (item == murcielagos[i]){
                bart->perderVida();

                delete murcielagos[i];
                murcielagos[i]=nullptr;
                murcielagos.removeAt(i);

                if (bart->getVidas()==2){
                    delete vidasActuales;
                    vidasActuales=nullptr;

                    imagenRecortada = imagenVidas.copy(0, 12, 43, 12).scaled(140, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    vidasActuales= new QGraphicsPixmapItem(imagenRecortada);
                    escena->addItem(vidasActuales);
                    vidasActuales->setPos(60,620);
                }

                else if (bart->getVidas()==1){
                    delete vidasActuales;
                    vidasActuales=nullptr;

                    imagenRecortada = imagenVidas.copy(0, 24, 43, 12).scaled(140, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    vidasActuales= new QGraphicsPixmapItem(imagenRecortada);
                    escena->addItem(vidasActuales);
                    vidasActuales->setPos(60,620);
                }

                else if (bart->getVidas() == 0) {
                    gameOver();
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
            timerNivel->stop();
            qDebug() << "Generación de obstáculos detenida";
            qDebug() << "¡Nivel completado!";
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
                if (distancia < 140) {
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

void Nivel::gameOver(){

    escena->setBackgroundBrush(QBrush(QImage(":/fondos/GAME_OVER.png").scaled(1280, 720)));
    if (nivelSeleccionado==1){

    }
    else if (nivelSeleccionado==2){

        delete edificioItem;
        edificioItem=nullptr;

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
            //escena->removeItem(textoTiempo);
            delete textoTiempo;
            textoTiempo = nullptr;
        }
        //escena->clear();
    }

    else if(nivelSeleccionado==3){
        colisionTimer->stop();
        delete colisionTimer;
        colisionTimer=nullptr;

        delete bart;
        bart=nullptr;

        delete vidasActuales;
        vidasActuales=nullptr;

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
        for (QGraphicsPixmapItem* tumba : tumbasEscena) {
            if (tumba){
                delete tumba;
                tumba=nullptr;
            }
        }

        delete paginaCont;
        paginaCont=nullptr;

        delete contadorPaginas;
        contadorPaginas=nullptr;

        //escena->clear();
    }
}

Nivel::~Nivel() {
    if (nivelSeleccionado==3){
        if (bart){
            delete bart;
            bart = nullptr;
        }
        if (arma){
            delete arma;
            arma = nullptr;
        }
        if (pagina){
            delete pagina;
            pagina = nullptr;
        }

        for (Enemigo* murcielago : murcielagos) {
            if (murcielago){
                delete murcielago;
                murcielago=nullptr;
            }
        }
        for (QGraphicsPixmapItem* tumba : tumbasEscena) {
            if (tumba){
                delete tumba;
                tumba=nullptr;
            }
        }

        delete paginaCont;
        paginaCont=nullptr;

        delete contadorPaginas;
        contadorPaginas=nullptr;

        delete colisionTimer;
        colisionTimer=nullptr;

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
    }

}
