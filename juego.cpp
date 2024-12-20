#include "juego.h"
#include "ui_juego.h"
#include "nivel.h"
#include <QGraphicsProxyWidget>
#include <QPixmap>

Juego::Juego(QWidget *parent): QMainWindow(parent), ui(new Ui::Juego), nivel(nullptr), botonMenu(nullptr),
    botonWidgetMenu(nullptr),
    botonSalir(nullptr),
    botonWidgetSalir(nullptr){
    ui->setupUi(this);
    escena = new QGraphicsScene(this);
    vista = new QGraphicsView(this);

    setFixedSize(1280, 720);

    vista->setScene(escena);
    escena->setSceneRect(0, 0, 1280, 720);
    vista->setFixedSize(1280, 720);

    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    iniciarJuego();
}

Juego::~Juego()
{
    // Liberar la escena
    if (escena) {
        delete escena;
        escena = nullptr;
    }

    // Liberar la vista
    if (vista) {
        delete vista;
        vista = nullptr;
    }

    // Liberar el nivel
    if (nivel) {
        delete nivel;
        nivel = nullptr;
    }

    // Liberar botones y sus widgets asociados
    if (botonNivel1) {
        delete botonNivel1;
        botonNivel1 = nullptr;
    }

    if (botonNivel2) {
        delete botonNivel2;
        botonNivel2 = nullptr;
    }

    if (botonNivel3) {
        delete botonNivel3;
        botonNivel3 = nullptr;
    }

    if (botonWidget1) {
        delete botonWidget1;
        botonWidget1 = nullptr;
    }

    if (botonWidget2) {
        delete botonWidget2;
        botonWidget2 = nullptr;
    }

    if (botonWidget3) {
        delete botonWidget3;
        botonWidget3 = nullptr;
    }

    if (botonInicio) {
        delete botonInicio;
        botonInicio = nullptr;
    }

    if (botonWidgetInicio) {
        delete botonWidgetInicio;
        botonWidgetInicio = nullptr;
    }

    if (botonMenu) {
        delete botonMenu;
        botonMenu = nullptr;
    }

    if (botonWidgetMenu) {
        delete botonWidgetMenu;
        botonWidgetMenu = nullptr;
    }

    if (botonSalir) {
        delete botonSalir;
        botonSalir = nullptr;
    }

    if (botonWidgetSalir) {
        delete botonWidgetSalir;
        botonWidgetSalir = nullptr;
    }

    // Liberar la interfaz de usuario
    if (ui) {
        delete ui;
        ui = nullptr;
    }
}
void Juego::iniciarJuego(){

    escena->setBackgroundBrush(QBrush(QImage(":/fondos/FondoInicio.png").scaled(1280,720)));

    botonInicio = new QPushButton();

    botonInicio->setFixedSize(200, 115);

    QPixmap iconoInicio(":/fondos/BotonInicio.png");

    botonInicio->setIcon(iconoInicio);

    botonInicio->setIconSize(QSize(185, 100));

    botonWidgetInicio =escena->addWidget(botonInicio);
    botonWidgetInicio->setPos(975, 100);

    botonInicio->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "}"
    );

    connect(botonInicio, &QPushButton::clicked, this, &Juego::mostrarMenuInicio);
}


void Juego::mostrarMenuInicio(){

    if (botonMenu!=nullptr){
        disconnect(botonMenu, &QPushButton::clicked, this, &Juego::mostrarMenuInicio);
        disconnect(botonSalir, &QPushButton::clicked, this, &Juego::salirJuego);
        escena->removeItem(botonWidgetMenu);
        escena->removeItem(botonWidgetSalir);
        escena->clear();
    }

    disconnect(botonInicio, &QPushButton::clicked, this, &Juego::mostrarMenuInicio);
    escena->removeItem(botonWidgetInicio);

    escena->setBackgroundBrush(QBrush(QImage(":/fondos/Fondo_MenuNiveles.png").scaled(1280,720)));

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

    disconnect(botonNivel1, &QPushButton::clicked, this, &Juego::seleccionarNivel1);
    disconnect(botonNivel2, &QPushButton::clicked, this, &Juego::seleccionarNivel2);
    disconnect(botonNivel3, &QPushButton::clicked, this, &Juego::seleccionarNivel3);

    escena->removeItem(botonWidget1);
    escena->removeItem(botonWidget2);
    escena->removeItem(botonWidget3);

    //Eliminar cualquier nivel previamente creado

    if (nivel) {
        delete nivel;
    }
    nivel = new Nivel(nivelSeleccionado, escena);
    connect(nivel, &Nivel::juegoTerminado, this, &Juego::crearBotonesFinJuego);

}

void Juego::crearBotonesFinJuego() {

    // Crear botón de menú
    botonMenu = new QPushButton("Regresar al Menú");
    botonMenu->setFixedSize(200, 50);
    botonWidgetMenu = escena->addWidget(botonMenu);
    botonWidgetMenu->setPos(300, 650);
    botonWidgetMenu->setZValue(10);

    // Crear botón de salir
    botonSalir = new QPushButton("Salir del Juego");
    botonSalir->setFixedSize(200, 50);
    botonWidgetSalir = escena->addWidget(botonSalir);
    botonWidgetSalir->setPos(600, 650);
    botonWidgetSalir->setZValue(10);

    // Conectar señales
    connect(botonMenu, &QPushButton::clicked, this, &Juego::mostrarMenuInicio);
    connect(botonSalir, &QPushButton::clicked, this, &Juego::salirJuego);

    botonMenu->show();
    botonSalir->show();

    // Redibujar la vista
    vista->viewport()->update();
}

void Juego::salirJuego() {
    QApplication::quit(); // Cierra la aplicación
}

void Juego::seleccionarNivel1(){iniciarNivel(1);}
void Juego::seleccionarNivel2(){iniciarNivel(2);}
void Juego::seleccionarNivel3(){iniciarNivel(3);}
