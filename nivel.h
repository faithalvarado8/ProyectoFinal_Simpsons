#ifndef NIVEL_H
#define NIVEL_H

#include "objetos.h"
#include "bart.h"
#include "kinghomero.h"
#include "enemigo.h"
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsTextItem>
#include <homero.h>
#include "obstaculo.h"

class Nivel : public QObject{
    Q_OBJECT
private:
    unsigned short nivelSeleccionado;
    unsigned short cont=1;
    QGraphicsScene* escena;

    //Nivel 1
    Homero* homero;
    void agregarPlataformas();
    QList<QGraphicsRectItem*> plataformas;

    //Nivel 2
    QGraphicsPixmapItem* edificioItem;
    KingHomero *kingHomero;
    int yOffset;
    QGraphicsTextItem *textoTiempo;
    QTimer *timerNivel;
    QTimer *timerObstaculos;
    unsigned short int tiempoRestante;
    Obstaculo *obstaculo;

    //Nivel 3
    Bart * bart;
    Objetos* arma;
    Objetos* pagina;
    Objetos* paginaCont;
    Enemigo* murcielago;
    QList<Enemigo*> murcielagos;
    QTimer *colisionTimer;
    QGraphicsPixmapItem* tumba;
    void agregarTumbas(int numTumbas);
    QList<QPointF> posicionesInvalidas;
    QVector<QPixmap> tumbas;
    int spriteTumba;
    bool posicionValida;
    QList<QGraphicsPixmapItem*> tumbasEscena;
    QGraphicsTextItem *contadorPaginas;
    QPixmap imagenVidas;
    QPixmap imagenRecortada;
    QGraphicsPixmapItem* vidasActuales;
    Enemigo* zombie;
    QList<Enemigo*> zombies;
    QTimer *timerZombies;
    unsigned int puntaje;

    void escribirArchivo();

private slots:
    void agregarZombies();
    void verificarColisiones();
    void agregarObstaculos();

signals:
    void juegoTerminado();

public:
    Nivel(short int nivelSeleccionado, QGraphicsScene * escena);
    void moverEdificio();
    void actualizarTiempo();
    void sincronizarFondo(int dy);
    void eliminar();
    void gameOver();
    void ganarNivel();
    void actualizarVidasBart();
    void colisionesZombies();
    virtual ~Nivel();
};

#endif // NIVEL_H
