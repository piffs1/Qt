#include "spravka_v_2.h"
#include "ui_spravka_v_2.h"
//���� ������ 15.05.2017. ���� �������� �� ����� ������� .
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
