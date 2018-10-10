#include "set_con.h"
#include "ui_set_con.h"
#include <QDebug>
//���� ������ 15.05.2017. ���� �������� �� ��������� ���������� ����
set_con::set_con(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::set_con)
{
    ui->setupUi(this);
}
set_con::~set_con()
{
    delete ui;
}
void set_con::keyPressEvent(QKeyEvent *e)
{
    QWidget::keyPressEvent(e);
    if (e->key()==16777220)
        ui->pushButton->click();
    else if (e->key()==16777216)
        this->close(); //��������� ������� ������� "Enter" � "Escape". ��� ������� �� ������� "Enter" ���������� ������. ��� ������� �� ������� "Escape" ����� �����������.
}
void set_con::on_pushButton_clicked()
{
   emit back_to_host(ui->lineEdit_2->text());
   emit back_to_port(ui->lineEdit->text().toInt());
   emit back_to_data(ui->lineEdit_3->text());
   this->close();
//�������� �������� ��� MainWindow � �������� ��������.
}
