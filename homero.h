#ifndef HOMERO_H
#define HOMERO_H
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>

class Homero : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Homero(QList<QGraphicsRectItem*> plataformas);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    void saltar();
    ~Homero();

private:
    QVector<QPixmap> spritesCaminarDerecha;
    QVector<QPixmap> spritesCaminarIzquierda;
    QVector<QPixmap> spritesSaltarDerecha;
    QVector<QPixmap> spritesSaltarIzquierda;
    QVector<QPixmap> spritesCelebrar;

    int indiceSprite;
    QTimer *timer;
    bool moving;
    char direccion;
    QList<QGraphicsRectItem*> plataformas;
    QMap<int,bool>keys;
    QPointF nuevaPos;
    QPointF oldPos;

    //NUEVO
    bool enElAire; // Indica si Homero está en el aire
    qreal velocidadVertical; // Velocidad vertical para simular gravedad y saltos
    bool noColisiona;
    void colisionPlataformas();
    void caerEnPlataforma();
    QTimer *timerSalto;
    int t;

private slots:
    void actualizarAnimacion();


};

#endif // HOMERO_H
