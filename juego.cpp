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
    delete ui;

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
    connect(nivel, &Nivel::juegoTerminado, this, &Juego::mostrarBotonesFinJuego);

}

void Juego::crearBotonesFinJuego() {
    qDebug() << "Creando botones de fin de juego...";

    // Crear botón de menú
    botonMenu = new QPushButton("Regresar al Menú");
    botonMenu->setFixedSize(200, 50);
    botonWidgetMenu = escena->addWidget(botonMenu);
    botonWidgetMenu->setPos(540, 360);
    botonWidgetMenu->setZValue(10);
    qDebug() << "Botón de menú creado y añadido a la escena.";

    // Crear botón de salir
    botonSalir = new QPushButton("Salir del Juego");
    botonSalir->setFixedSize(200, 50);
    botonWidgetSalir = escena->addWidget(botonSalir);
    botonWidgetSalir->setPos(540, 420);
    botonWidgetSalir->setZValue(10);
    qDebug() << "Botón de salir creado y añadido a la escena.";

    // Conectar señales
    connect(botonMenu, &QPushButton::clicked, this, &Juego::mostrarMenuInicio);
    connect(botonSalir, &QPushButton::clicked, this, &Juego::salirJuego);

    botonMenu->show();
    botonSalir->show();

    // Redibujar la vista
    vista->viewport()->update();
    qDebug() << "Botones de fin de juego configurados.";

}

void Juego::mostrarBotonesFinJuego() {
    crearBotonesFinJuego();
}




// void Juego::crearBotonesFinJuego() {
//     botonMenu = new QPushButton("Regresar al Menú");
//     botonMenu->setFixedSize(200, 50);
//     botonMenu->setAutoFillBackground(true);
//     QPalette paletteMenu = botonMenu->palette();
//     paletteMenu.setColor(QPalette::Button, QColor(76, 175, 80));
//     paletteMenu.setColor(QPalette::ButtonText, Qt::white);
//     botonMenu->setPalette(paletteMenu);
//     botonMenu->isVisible();
//     botonWidgetMenu->setZValue(2);


//     botonWidgetMenu = escena->addWidget(botonMenu);
//     botonWidgetMenu->setPos(640 - 100, 360);
//     botonSalir->setAutoFillBackground(true);
//     QPalette paletteSalir = botonSalir->palette();
//     paletteSalir.setColor(QPalette::Button, QColor(244, 67, 54));
//     paletteSalir.setColor(QPalette::ButtonText, Qt::white);
//     botonSalir->setPalette(paletteSalir);
//     botonSalir->isVisible();
//     botonWidgetSalir->setZValue(2);

//     botonSalir = new QPushButton("Salir del Juego");
//     botonSalir->setFixedSize(200, 50);
//     botonWidgetSalir = escena->addWidget(botonSalir);
//     botonWidgetSalir->setPos(640 - 100, 420);

//     connect(botonMenu, &QPushButton::clicked, this, &Juego::mostrarMenuInicio);
//     connect(botonSalir, &QPushButton::clicked, this, &Juego::salirJuego);
// }

void Juego::salirJuego() {
    QApplication::quit(); // Cierra la aplicación
}

void Juego::seleccionarNivel1(){iniciarNivel(1);}
void Juego::seleccionarNivel2(){iniciarNivel(2);}
void Juego::seleccionarNivel3(){iniciarNivel(3);}
