#ifndef OBJETOS_H
#define OBJETOS_H

#include <QGraphicsPixmapItem>
#include <QObject>

using namespace std;

class Objetos: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
private:
    QPixmap sprites;

public:
    Objetos(const QString& imagen, int x, int y); //Constructor de swiches Nivel 1
    Objetos(unsigned short int cont=0);
    Objetos(QList<QPointF> posicionesInvalidas);
    ~Objetos();
};

#endif // OBJETOS_H
