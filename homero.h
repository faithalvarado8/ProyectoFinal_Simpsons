#ifndef HOMERO_H
#define HOMERO_H
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>
#include <QGraphicsScene>

class Homero : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Homero(QList<QGraphicsRectItem*> plataformas, QGraphicsScene* escena);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    ~Homero();

private:
    QVector<QPixmap> spritesCaminarDerecha;
    QVector<QPixmap> spritesCaminarIzquierda;
    QVector<QPixmap> spritesSaltarDerecha;
    QVector<QPixmap> spritesSaltarIzquierda;
    QVector<QPixmap> spritesCelebrar;

    int indiceSprite;
    bool moving;
    char direccion;
    QList<QGraphicsRectItem*> plataformas;
    QMap<int,bool>keys;

    //NUEVO

    bool enElAire; // Indica si Homero está en el aire
   /* void colisionPlataformas();
    void caerEnPlataforma();
    */

    QTimer *timer;
    qreal v0;
    qreal t;
    qreal angulo;
    QTimer *timerSalto;
    void saltar();
    qreal hMax;
    qreal nuevaY;
    qreal nuevaX;

    //Movimiento en X
    qreal x0;
    QTimer *colisiones;

    //Movimiento en y
    qreal y0;
    qreal v0y; // Velocidades iniciales
    qreal g; // Aceleración debido a la gravedad

    QTimer* timerCaida;
    void caida();

    QGraphicsScene* escena;

private slots:
    void actualizarAnimacion();
    void actualizarSalto();
    void colisionPlataformas();
    void actualizarCaida();
};

#endif // HOMERO_H
