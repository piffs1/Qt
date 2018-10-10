#include "newroom.h"
#include "ui_newroom.h"
#include <QDebug>
#include <QSqlQuery>
#include <createevent.h>
#include <QSqlQueryModel>
//Файл создан 15.05.2017. Файл отвечает за показ комнаты чата.
newroom::newroom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newroom)
{
    ui->setupUi(this);
    tmr1 = new QTimer;//Создание нового таймера
    tmr_interval = 1000;
    tmr1->setInterval(tmr_interval); ///swap dnr intereal
    tmr1->start();
    connect(tmr1,SIGNAL(timeout()),this,SLOT(update1()));
    supID = 0;
    _set_chat = new set_chat;
    _createEvent = new createEvent;
    le = new list_of_events;
    _uf = new uploadfile;
    _fm = new filemanager;
    _spravka_v2 = new spravka_v_2;
}
void newroom::setTableSelect(QString &tbl)
{
    tableSelect = tbl; //Установка значения текущей таблицы
}
newroom::~newroom()
{
    delete ui;
}
void newroom::keyPressEvent(QKeyEvent *e)
{
    if (e->key()==16777220)
        ui->pushButton->click(); //Обработка клавиши "ENTER".
}
void newroom::setTimer_base(int _tmrBase)
{
    tmr_interval = _tmrBase;
    tmr1->stop();
    tmr1->setInterval(tmr_interval);
    tmr1->start();
//Обновление таймера
}
void newroom::setFont_size(QFont font)
{
    ui->textEdit->setFont(font);
    ui->textEdit_2->setFont(font);
//Обновление шрифта
}
void newroom::on_pushButton_clicked()
{
    QSqlQueryModel *qModel = new QSqlQueryModel;
    QString sda;
    if(!ui->textEdit_2->toPlainText().isEmpty())
        sda = "INSERT INTO `"+tableSelect+"` (`usrnme`,`msg`, `DATE_OF_MSG`, `TIME_OF_MSG`) SELECT USER(),'"+ui->textEdit_2->toPlainText()+"',curdate(),curtime();";      
    qModel->setQuery(sda);
    ui->textEdit_2->clear();
//Обработка и отправка сообщения на сервер.
}
void newroom::update1()
{
    QSqlQuery *query = new QSqlQuery;
    query->prepare("select id,usrnme,msg,date_of_msg,time_of_msg,file from "+tableSelect+" where id>"+QString::number(supID));//Поиск производится по вспомогательному иду supID
    query->exec(); //Запуск запроса
    while(query->next())
    {
        if(query->value(2).toString().contains("[ОБЪЯВЛЕНИЕ]"))
        { //обработка события если было создано объявление
            QString temp = query->value(2).toString(); //Считывание в переменную сообщения
            QString eventz=""; //Содержит само сообщение.
            for(int i = 12; i < temp.size();i++)
                eventz = eventz + temp[i]; //Считывание сообщения после текста "[ОБЪЯВЛЕНИЕ]".
            ui->textEdit->append("<span style=\" color:#ff0000;\"><b>"+query->value(1).toString() +":Создал объявление. В "+query->value(4).toString()+"."+eventz+"</b></span>");
            //Выделение объявления в клиенте при помощи HTML тегов.
		supID = query->value(0).toInt(); //Передает значения ИДа в глобальну переменную.
        }else if(!query->value(5).toString().isEmpty()){
//Обработка события, если был прислан файл.
            ui->textEdit->append("<span style=\" color:#1E9E1E;\"><b>"+query->value(1).toString() +":Прислал файл. "+query->value(2).toString()+".</b></span>");
            supID = query->value(0).toInt();
            supDate = query->value(3).toString();
        }else if(!query->value(3).toString().contains(supDate)){
//Обработка события, если наступил новый день.
            ui->textEdit->append("<span style=\" color:#ff0000;\"><b>" +query->value(3).toString() + "</b></span>");
            ui->textEdit->append("");
            ui->textEdit->append(query->value(1).toString() + "(" + query->value(4).toString() +")>" + query->value(2).toString());
            supID = query->value(0).toInt();
            supDate = query->value(3).toString();
        }else{
        ui->textEdit->append(query->value(1).toString() + "(" + query->value(4).toString() +")>" + query->value(2).toString());
        supID = query->value(0).toInt();
        supDate = query->value(3).toString();
	//Прорисовка в клиенте всех сообщений.
	}
    }
//Процедура обновления сообщений
}
void newroom::closeEvent(QCloseEvent *event)
{
    delete this;
    delete _set_chat;
    delete _createEvent;
    delete le;
    delete _fm;
    delete _uf;
    delete _spravka_v2;
//Обработчик события закрытия окна
}
void newroom::on_action_triggered()
{
    delete _set_chat;
    _set_chat = new set_chat;
    QObject::connect(_set_chat,SIGNAL(setIntervalTimer(int)),this,SLOT(setTimer_base(int)));
    QObject::connect(_set_chat,SIGNAL(setSizeFont(QFont)),this,SLOT(setFont_size(QFont)));
//Связь сигналов set_chat и слотов newroom.
    _set_chat->show();//Показ формы
}
void newroom::on_action_2_triggered()
{
    delete _createEvent;
    _createEvent = new createEvent;
    QSqlQuery *query = new QSqlQuery;
    query->prepare("SELECT USER()");
    query->exec();
    while(query->next())
        _createEvent->userNME = query->value(0).toString(); //Передача в глобальную переменную имя пользователя
    _createEvent->tableSelect = tableSelect; //Передача в глобальную переменную текущее имя таблицы.
    _createEvent->show();
//Открытие формы для создания объявления
}
void newroom::on_action_3_triggered()
{
    delete le;
    le = new list_of_events;
    QSqlQueryModel *query = new QSqlQueryModel;
    le->qModel->setQuery("SELECT USER(),MSG,DATE_OF_MSG from "+tableSelect+" where msg LIKE '[ОБЪЯВЛЕНИЕ]%' AND DATE_OF_MSG>=curdate();");
    //Поиск по ячейке MSG всех актуальных объявлений.
    le->qModel->setHeaderData(0,Qt::Horizontal,"Пользователь"); 
    le->qModel->setHeaderData(1,Qt::Horizontal,"Объявление");
    le->qModel->setHeaderData(2,Qt::Horizontal,"Дата завершения");//Обработка колонок.

//Форма просмотра актуальных объявлений
    le->show();
}
void newroom::on_action_5_triggered()
{
    delete _uf;
    _uf = new uploadfile;
    _uf->tableSelect = tableSelect;
    _uf->show();

}
void newroom::on_action_6_triggered()
{
    delete _fm;
    _fm = new filemanager;
    _fm->qModel->setQuery("SELECT ID,USRNME,MSG,DATE_OF_MSG,TIME_OF_MSG FROM "+tableSelect+" WHERE !isnull(FILE)");
//Показ всех файлов загруженных на сервер.
    _fm->qModel->setHeaderData(0,Qt::Horizontal,"Номер файла");
    _fm->qModel->setHeaderData(1,Qt::Horizontal,"Пользователь");
    _fm->qModel->setHeaderData(2,Qt::Horizontal,"Имя файла");
    _fm->qModel->setHeaderData(3,Qt::Horizontal,"Дата публикации файла");
    _fm->qModel->setHeaderData(4,Qt::Horizontal,"Время публикации файла");
    _fm->tableSelect = tableSelect;
    _fm->show();
}
void newroom::on_action_4_triggered()
{
    delete _spravka_v2;
    _spravka_v2 = new spravka_v_2;
    _spravka_v2->show();
//Показ справки
}
