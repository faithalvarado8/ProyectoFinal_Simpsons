#include "juego.h"
#include "ui_juego.h"

Juego::Juego(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Juego)
{
    ui->setupUi(this);
}

Juego::~Juego()
{
    delete ui;
}
