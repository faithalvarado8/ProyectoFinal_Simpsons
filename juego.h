#ifndef JUEGO_H
#define JUEGO_H

#include "nivel.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
// #include <QPointer>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Juego;
}
QT_END_NAMESPACE

class Juego : public QMainWindow
{
    Q_OBJECT

public:
    Juego(QWidget *parent = nullptr);
    ~Juego();

private:
    Ui::Juego *ui;
    QGraphicsScene * escena;
    QGraphicsView * vista;
    Nivel *nivel = nullptr;
    QPushButton *botonNivel1;
    QPushButton *botonNivel2;
    QPushButton *botonNivel3;
    void mostrarMenuInicio();
    void iniciarNivel(short int nivelSeleccionado);
    QGraphicsProxyWidget *botonWidget1;
    QGraphicsProxyWidget *botonWidget2;
    QGraphicsProxyWidget *botonWidget3;


private slots:
    void seleccionarNivel1();
    void seleccionarNivel2();
    void seleccionarNivel3();
};
#endif // JUEGO_H
