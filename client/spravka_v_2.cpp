#include "spravka_v_2.h"
#include "ui_spravka_v_2.h"
//Файл создан 15.05.2017. Файл отвечает за показ справки .
spravka_v_2::spravka_v_2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spravka_v_2)
{
    ui->setupUi(this);
}

spravka_v_2::~spravka_v_2()
{
    delete ui;
}
