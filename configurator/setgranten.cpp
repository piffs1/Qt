#include "setgranten.h"
#include "ui_setgranten.h"
//���� ������ 15.05.2017. ���� �������� �� ��������� �������.
setGranten::setGranten(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setGranten)
{
    ui->setupUi(this);
}

setGranten::~setGranten()
{
    delete ui;
}

void setGranten::keyPressEvent(QKeyEvent *e)
{
    QWidget::keyPressEvent(e);
    if (e->key()==16777220)
       ui->pushButton->click(); // ��������� ������� ������� "Enter".
}

void setGranten::on_pushButton_clicked()
{
    if(ui->lineEdit_2->text() == "dacicwo")
        emit getBackAdm(strStd,ui->lineEdit->text()); //�������� ���������� ������� �������
    else
        emit getBack(strStd,ui->lineEdit->text(),ui->lineEdit_2->text()); //�������� �������� �������
}
