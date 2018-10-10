#include "list_of_events.h"
#include "ui_list_of_events.h"
//‘айл создан 15.05.2017. ‘айл отвечает за показ актуальных объ€влений.
list_of_events::list_of_events(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::list_of_events)
{
    ui->setupUi(this);
    ui->tableView->setModel(qModel); //”становка модели дл€ таблицы.
}

list_of_events::~list_of_events()
{
    delete ui;
}
