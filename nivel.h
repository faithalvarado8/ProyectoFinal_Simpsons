#ifndef NIVEL_H
#define NIVEL_H

#include "jugador.h"
#include "homero.h"
#include "kinghomero.h"
#include "bart.h"
#include "objetos.h"
#include "enemigo.h"

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include <QImage>
#include <QGraphicsTextItem>

class Nivel : public QObject{
    Q_OBJECT
private:
    unsigned short nivelSeleccionado;
    unsigned short cont=1;
    QGraphicsScene* escena;

    //Nivel 1
    Homero *homero;
    QImage fondoColisiones;

    //Nivel 2
    QGraphicsPixmapItem* edificioItem;
    KingHomero *kingHomero;
    int yOffset;
    QGraphicsTextItem *textoTiempo;
    QTimer *timerNivel;
    QTimer *timerObstaculos;
    int tiempoRestante;

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

    Jugador * jugador;

public:
    Nivel(short int nivelSeleccionado, QGraphicsScene * escena);
    bool esColision(const QPointF& posicion) const;
    void moverEdificio();
    void actualizarTiempo();
    void sincronizarFondo(int dy);
    void verificarColisiones();
    void gameOver();
    virtual ~Nivel();
};

#endif // NIVEL_H
