#include "spravka.h"
#include "ui_spravka.h"
//Файл создан 15.05.2017. Файл отвечает за показ справки.
spravka::spravka(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spravka)
{
    ui->setupUi(this);
}

spravka::~spravka()
{
    delete ui;
}
