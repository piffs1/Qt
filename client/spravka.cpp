#include "spravka.h"
#include "ui_spravka.h"
//���� ������ 15.05.2017. ���� �������� �� ����� �������.
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
