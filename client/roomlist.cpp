#include "roomlist.h"
#include "ui_roomlist.h"
#include <newroom.h>
#include <QDebug>
//Файл создан 15.05.2017. Файл отвечает за показ списка комнат в чате.
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
    QString tempo = ui->listView->model()->data(index).toString();//Запись выбранного элемента
    _newroom->setTableSelect(tempo); //Установка работы с выбранной таблицей(комнатой)
    _newroom->setWindowTitle(tempo); //Установка заголовка окна.
    _newroom->show();
    this->close();//Закрытие формы
//Обработка двойного нажатия на элемент листа
}
