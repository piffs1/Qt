#include "roomlist.h"
#include "ui_roomlist.h"
#include <newroom.h>
#include <QDebug>
//���� ������ 15.05.2017. ���� �������� �� ����� ������ ������ � ����.
roomlist::roomlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::roomlist)
{
    ui->setupUi(this);
    ui->listView->setModel(qModel);
}
roomlist::~roomlist()
{
    delete ui;
}
void roomlist::on_listView_doubleClicked(const QModelIndex &index)
{
    _newroom = new newroom;
    QString tempo = ui->listView->model()->data(index).toString();//������ ���������� ��������
    _newroom->setTableSelect(tempo); //��������� ������ � ��������� ��������(��������)
    _newroom->setWindowTitle(tempo); //��������� ��������� ����.
    _newroom->show();
    this->close();//�������� �����
//��������� �������� ������� �� ������� �����
}
