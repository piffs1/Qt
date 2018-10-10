#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <windows.h>
#include <QMessageBox>
//Файл создан 15.05.2017. Главное окно программы.
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL"); //Выбор драйвера для работы с БД
    _set_con = new set_con;
    _set_chat = new set_chat;
//Создание новых классов форм
    tmr_interval = 1000; //Стандартный интервал обновления 1000 мс (1с)
    ui->actionrecconect->setVisible(false); //Действие переподключения становится невидимым
    ui->action_3->setVisible(false);//Действие подключения к комнатам
    supID = 0;//Вспомогательная переменная для обновления сообщений в клиенте
    ui->action_4->setVisible(false);//Действие подключения к комнатам
    _roomlist = new roomlist;
    _spravka = new spravka;

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    QWidget::keyPressEvent(e);
    if(!ui->page->isHidden())
    {
        if (e->key()==16777220) //Проверка входа в программу и обработка клавиши "ENTER" при входе.
            ui->pushButton->click(); 
    }
}

void MainWindow::setTimer_base(int _tmrBase)
{
    if(!ui->page_2->isHidden())
    {
        tmr_interval = _tmrBase; //Прием нового интервала
        tmr->stop();//Остановка таймера
        tmr->setInterval(tmr_interval); // Установка нового интервала
        tmr->start(); //Запуск таймера
    }
}

void MainWindow::update()
{
    if(ui->page_2->isHidden())
        tmr->stop();//При закрытии формы таймер останавливается.
}
void MainWindow::setPort_base(int _prtBase)
{
    port_base = _prtBase; //Установка порта БД

}
void MainWindow::setHost_base(QString _hstBase)
{
    host_base = _hstBase;//Установка адреса БД
}
void MainWindow::setData_base(QString _dataBase)
{
    data_base = _dataBase;//Установка схемы
}
void MainWindow::setSize_font(QFont _font)
{
    font_size = _font;//Установка размера шрифта
}
void MainWindow::on_action_2_triggered()
{
    this->close();//Выход из программы
}
void MainWindow::on_action_triggered()
{
    delete _set_con;
    _set_con = new set_con;
    _set_con->setFocus();
    _set_con->show();
//Создание новой формы класса set_con.
    QObject::connect(_set_con,SIGNAL(back_to_port(int)),this,SLOT(setPort_base(int)));
    QObject::connect(_set_con,SIGNAL(back_to_host(QString)),this,SLOT(setHost_base(QString)));
    QObject::connect(_set_con,SIGNAL(back_to_data(QString)),this,SLOT(setData_base(QString)));
//Связываем сигналы класса set_con со слотами класса MainWindow.
}
void MainWindow::on_pushButton_clicked()
{
    db.setHostName(host_base); 
    db.setPort(port_base);
    db.setUserName(ui->lineEdit->text());
    db.setPassword(ui->lineEdit_2->text());
    db.setDatabaseName(data_base);
//Задаем параметры для подключения
    if (!db.open())
    {
        QMessageBox::critical(0, QObject::tr("Ошибка"), "Ошибка входа"); //Уведомление об ошибке
    }
    else
    {
        ui->page_2->show(); //Открываем главное окно
        ui->page->hide();//Закрываем окно входа
        if(!ui->page_2->isHidden())//Делаем дополнительную проверку
        {
            tmr = new QTimer(this);//Создаем таймер
            tmr->setInterval(tmr_interval);//Устанавливаем наш стандартный интервал
            connect(tmr,SIGNAL(timeout()),this,SLOT(update()));//Создаем связь между таймером и классом MainWindow.
            tmr->start(); //Запуск таймера
        }
        QSqlQuery *query = new QSqlQuery;
        query->prepare("select curdate(),curtime();"); //Подготовка к запросу
        query->exec();//Запуск запроса
        QString new_time;
        QString new_date;
        while(query->next()){
            new_date = query->value(0).toString(); //Запись даты на сервере
            new_time = query->value(1).toString(); //Запись время на сервере
        }
        ui->label_6->setText(ui->lineEdit->text());
        ui->action->setVisible(false);
        ui->actionrecconect->setVisible(true);
        ui->action_3->setVisible(true);
        ui->action_4->setVisible(true);
        ui->menu_2->setEnabled(true);
        ui->label_3->setText(ui->label_3->text() + "\t" + ui->lineEdit->text());
        ui->label_7->setText(new_date + '\n' + new_time);
//Корректировка компонентов главного окна
    }
}
void MainWindow::on_actionrecconect_triggered()
{
    ui->action->setVisible(true); 
    ui->page->show();//Открываем окно входа
    ui->page_2->close();//Закрываем главное окно
    ui->action_3->setVisible(false);
    ui->actionrecconect->setVisible(false);
}
void MainWindow::on_action_3_triggered()
{
    delete _set_chat;
    _set_chat = new set_chat;
    QObject::connect(_set_chat,SIGNAL(setIntervalTimer(int)),this,SLOT(setTimer_base(int)));
    QObject::connect(_set_chat,SIGNAL(setSizeFont(QFont)),this,SLOT(setSize_font(QFont)));
//Связываем сигналы set_chat и слоты MainWindow.
    _set_chat->show();
}
void MainWindow::on_action_4_triggered()
{
    delete _roomlist;
    _roomlist = new roomlist;
    _roomlist->qModel->setQuery("show tables;");
    _roomlist->show();
//Просмотр всех комнат
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    delete _set_chat;
    delete _set_con;
    delete _roomlist;
//При закрытии главной формы, закрываются все остальные
}
void MainWindow::on_action_5_triggered()
{
    delete _spravka;
    _spravka = new spravka;
    _spravka->show();
//Просмотр справки
}
