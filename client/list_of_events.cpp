#include "list_of_events.h"
#include "ui_list_of_events.h"
//���� ������ 15.05.2017. ���� �������� �� ����� ���������� ����������.
list_of_events::list_of_events(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::list_of_events)
{
    ui->setupUi(this);
    ui->tableView->setModel(qModel); //��������� ������ ��� �������.
}

list_of_events::~list_of_events()
{
    delete ui;
}
