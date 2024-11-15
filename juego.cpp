#include "juego.h"
#include "ui_juego.h"
#include "nivel.h"
#include <QGraphicsProxyWidget>
#include <QPixmap>

Juego::Juego(QWidget *parent): QMainWindow(parent), ui(new Ui::Juego), nivel(nullptr){
    ui->setupUi(this);
    escena = new QGraphicsScene(this);
    vista = new QGraphicsView(this);

    unsigned int ancho = 1280;
    unsigned int alto = 720;

    setFixedSize(ancho, alto);

    vista->setScene(escena);
    escena->setSceneRect(0, 0, ancho, alto);
    vista->setFixedSize(ancho, alto);

    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    escena->setBackgroundBrush(QBrush(QImage(":/fondos/fondoInicio1.png").scaled(ancho,alto)));

    mostrarMenuInicio();
}

Juego::~Juego()
{
    delete ui;
}

void Juego::mostrarMenuInicio(){

    // Crea botones para seleccionar el nivel
    botonNivel1 = new QPushButton();
    botonNivel2 = new QPushButton();
    botonNivel3 = new QPushButton();

    // Configura el tamaño de los botones
    botonNivel1->setFixedSize(215, 125);  // Ajusta el tamaño
    botonNivel2->setFixedSize(215, 125);
    botonNivel3->setFixedSize(215, 125);

    // Ajusta tamaño de los iconos
    QPixmap iconoPixmapNivel1(":/fondos/Krusty.jpg");
    QPixmap iconoPixmapNivel2(":/fondos/KingHomero.jpg");
    QPixmap iconoPixmapNivel3(":/fondos/cementerio.jpg");

    botonNivel1->setIcon(iconoPixmapNivel1);
    botonNivel2->setIcon(iconoPixmapNivel2);
    botonNivel3->setIcon(iconoPixmapNivel3);

    botonNivel1->setIconSize(QSize(185, 100));
    botonNivel2->setIconSize(QSize(185, 100));
    botonNivel3->setIconSize(QSize(185, 100));

    // Posiciona botones en la escena
    botonWidget1 =escena->addWidget(botonNivel1);
    botonWidget1->setPos(650, 150);
    botonWidget2 =escena->addWidget(botonNivel2);
    botonWidget2->setPos(650, 310);
    botonWidget3 =escena->addWidget(botonNivel3);
    botonWidget3->setPos(650, 470);

    // Conecta botones a las funciones para seleccionar el nivel
    connect(botonNivel1, &QPushButton::clicked, this, &Juego::seleccionarNivel1);
    connect(botonNivel2, &QPushButton::clicked, this, &Juego::seleccionarNivel2);
    connect(botonNivel3, &QPushButton::clicked, this, &Juego::seleccionarNivel3);
}

void Juego::iniciarNivel(short nivelSeleccionado){
    // Limpiar la escena de los botones
    qDebug() << "PASO A";
    disconnect(botonNivel1, &QPushButton::clicked, this, &Juego::seleccionarNivel1);
    disconnect(botonNivel2, &QPushButton::clicked, this, &Juego::seleccionarNivel2);
    disconnect(botonNivel3, &QPushButton::clicked, this, &Juego::seleccionarNivel3);
    qDebug() << "PASO B";
    escena->removeItem(botonWidget1);
    escena->removeItem(botonWidget2);
    escena->removeItem(botonWidget3);

    //Eliminar cualquier nivel previamente creado
    qDebug() << "Valor nivel" << QString::pointer(nivel);
    if (nivel) {
        qDebug() << "PASO 8";
        delete nivel;
        qDebug() << "PASO 9";
    }
    qDebug() << "PASO 10";

    nivel= new Nivel(nivelSeleccionado,escena);

    qDebug() << "PASO 11";
}

void Juego::seleccionarNivel1(){iniciarNivel(1);}
void Juego::seleccionarNivel2(){iniciarNivel(2);}
void Juego::seleccionarNivel3(){iniciarNivel(3);}
