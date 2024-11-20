#ifndef OBJETOS_H
#define OBJETOS_H

#include <string>
#include <QGraphicsPixmapItem>
#include <QObject>

using namespace std;

class Objetos: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
private:
    string objeto;
    QPixmap sprites;

public:
    Objetos(string objeto, unsigned short int cont=0);
};

#endif // OBJETOS_H
