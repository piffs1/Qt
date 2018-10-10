#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QGridLayout>
#include <QListView>
#include <QDebug>
//Файл создан 15.05.2017. Главная форма.
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL"); //Выбор драйвера БД
    _setGranten = new setGranten;
    _spravka = new spravka;
    //Создание форм setGranten,spravka.
    ui->groupBox->setVisible(false);
    ui->label->setVisible(false);
    ui->groupBox_10->setVisible(false);
//Закрытие доступа к админ панели
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setLoginPsw(int str, QString log, QString psw)
{
    db.close(); //Закрытие соединения
    db.setUserName(log);
    db.setPassword(psw);
    db.setDatabaseName("");
    db.open();
//Задаем новые параметры и открываем БД
    if(!db.open())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка входа");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        db.close();
        db.setUserName(username_admin);
        db.setPassword(password_admin);
        db.setDatabaseName(database_admin);
        db.open();
//Если БД не открыта, возвращаемся к прежним значениям БД.
    }else
    {
        userName = log;
        passWord = psw;
        db.close();
        db.setUserName(username_admin);
        db.setPassword(password_admin);
        db.setDatabaseName(database_admin);
        db.open();
	//Иначе передаем в глобальные переменные логин и пароль пользователя
        if(str==0) // Тип операции 0- назначение привилегий
        {
            QObject::connect(this,SIGNAL(signalExecGrantQuery()),this,SLOT(slotExecGrantQuery()));
            emit signalExecGrantQuery();
            QObject::disconnect(this,SIGNAL(signalExecGrantQuery()),this,SLOT(slotExecGrantQuery()));
//Вызываем функцию назначения привилегий.
        }else if(str==1) //Тип операции 1-удаление привелегий.
        {
            QObject::connect(this,SIGNAL(signalExecRevokeQuery()),this,SLOT(slotExecRevokeQuery()));
            emit signalExecRevokeQuery();
            QObject::disconnect(this,SIGNAL(signalExecRevokeQuery()),this,SLOT(slotExecRevokeQuery()));
//Вызываем функцию удаления привилегий.
        }
        _setGranten->close();
    }
}
void MainWindow::setLoginPswAdm(int str, QString log)
{
//Аналогична процедуре setLoginPsw.
    userName = log;
    passWord = "";
    if(str==0)
    {
        slotExecGrantQueryAdm();
    }else if(str==1)
    {
        slotExecRevokeQueryAdm();
    }
    _setGranten->close();
}
void MainWindow::on_pushButton_7_clicked()
{
    ui->comboBox->clear();
    db.setHostName(ui->lineEdit->text());
    db.setPort(ui->lineEdit_3->text().toInt());
    db.setUserName(ui->lineEdit_4->text());
    db.setPassword(ui->lineEdit_5->text());
//Вход в программу
    if(db.open())
    {
        ui->groupBox_5->setEnabled(true);
        username_admin = db.userName();
        password_admin = db.password();
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Вход выполнен успешно!");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        QSqlQuery *qM = new QSqlQuery;
        qM->exec("show schemas;");
//Прорисовка доступных БД
        while(qM->next())
        {
            if(!(qM->value(0).toString() == "mysql" || qM->value(0).toString() == "information_schema" || qM->value(0).toString() == "performance_schema"))
                ui->comboBox->addItem(qM->value(0).toString());
//Выводит все БД,кроме системных
        }
    }else{
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка входа!");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
//Уведомление об ошибке
    }
}
void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        ui->label_3->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
//Открытие доступа к элементам
    }else
    {
        ui->label_3->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
//Закрытие доступа к элементам
    }
}
void MainWindow::on_pushButton_6_clicked()
{
    QSqlQuery *query = new QSqlQuery;
    query->prepare("CREATE SCHEMA `"+ui->lineEdit_2->text()+"`;"); //Подготовка запроса
    if(query->exec()) // Проверка исполнения
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Создание схемы "+ui->lineEdit_2->text()+" выполнено успешно!");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
//Оповещение об успешном исполнении
    }else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка создания схемы");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
//Ошибка создания
    }
    query->exec("show schemas;");
    ui->comboBox->clear();
    while(query->next())
    {
        if(!(query->value(0).toString() == "mysql" || query->value(0).toString() == "information_schema" || query->value(0).toString() == "performance_schema"))
            ui->comboBox->addItem(query->value(0).toString());
//Обновление после создания
    }
}
void MainWindow::on_pushButton_8_clicked()
{
    db.close(); //Закрываем соединение БД
    db.setDatabaseName(ui->comboBox->itemText(ui->comboBox->currentIndex())); //Установка базы для работы
    db.open();
    if(db.open())
    {
        ui->groupBox->setEnabled(true);
        ui->label_11->setText(db.hostName());
        ui->label_12->setText(QString::number(db.port()));
        ui->label_13->setText(db.databaseName());
        QSqlQueryModel *query1 = new QSqlQueryModel;
        query1->setQuery("show tables;");
        ui->comboBox_2->setModel(query1);
        QSqlQueryModel *query = new QSqlQueryModel;
        query->setQuery("select user from mysql.user where user!='mysql.sys' and user!='"+db.userName()+"'"); //Обработка исключения пользователя, для того, чтобы пользователь не мог сам себя удалить.
        ui->comboBox_3->setModel(query);
        database_admin = db.databaseName();
        ui->groupBox_4->setVisible(false);
        ui->groupBox->setVisible(true);
        ui->label->setVisible(true);
        ui->groupBox_10->setVisible(true);
//Открываем доступ к "Админ  панели" и прогружаем все необходимые элементы для работы.
    }
}
void MainWindow::on_pushButton_clicked()
{
    QMessageBox mb("Добавление комнаты",
                               "Добавить комнату "+ui->lineEdit_6->text()+"?",
                               QMessageBox::Question,
                               QMessageBox::Yes | QMessageBox::Default,
                               QMessageBox::No | QMessageBox::Escape,
                               QMessageBox::NoButton);
                if (mb.exec() == QMessageBox::Yes) {
        QSqlQuery *query = new QSqlQuery;
        query->prepare("CREATE TABLE `"+db.databaseName()+"`.`"+ui->lineEdit_6->text()+"` (`ID` INT NOT NULL AUTO_INCREMENT,`usrnme` VARCHAR(100) NULL,`msg` VARCHAR("+QString::number(ui->spinBox->value())+") NULL,  `DATE_OF_MSG` DATE NULL,  `TIME_OF_MSG` TIME NULL,`FILE` MEDIUMBLOB NULL,PRIMARY KEY (`ID`));");
        //Подготовка к созданию таблицы(комнаты чата)
	if(query->exec())
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Создание комнаты "+ui->lineEdit_6->text()+" выполнено успешно!");
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }else
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("Ошибка создания комнаты");
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
        QSqlQueryModel *query1 = new QSqlQueryModel;
        query1->setQuery("show tables;");
        ui->comboBox_2->setModel(query1);
//Обновление списка таблиц(комнат чата)
}
}
void MainWindow::on_pushButton_9_clicked()
{
    QMessageBox mb("Удаление схемы",
                               "Вы действительно хотите удалить схему "+ui->label_13->text()+"?",
                               QMessageBox::Question,
                               QMessageBox::Yes | QMessageBox::Default,
                               QMessageBox::No | QMessageBox::Escape,
                               QMessageBox::NoButton);
                if (mb.exec() == QMessageBox::Yes) {
        QSqlQuery *query = new QSqlQuery;
        query->prepare("DROP DATABASE `"+ui->label_13->text()+"`;");
        //Подготовка к удалению схемы
	if(query->exec())
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Удаление схемы "+ ui->label_13->text()+" выполнено успешно!\nНеобходима перезагрузка системы");
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            this->close();
        }else
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("Ошибка удаления схемы");
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
    }
     ui->groupBox->setEnabled(false);
     ui->groupBox_5->setEnabled(false);
     ui->groupBox_10->setEnabled(false);
//После успешного удаления схемы требуется перезагрузка.
}
void MainWindow::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->isChecked())
        ui->groupBox_7->setEnabled(true);//Открытие доступа к группе для создания комнаты
    else
        ui->groupBox_7->setEnabled(false); //Закрытие доступа к группе для создания комнаты
}
void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox mb("Удаление комнаты",
                               "Вы действительно хотите удалить комнату "+ui->comboBox_2->itemText(ui->comboBox_2->currentIndex())+"?",
                               QMessageBox::Question,
                               QMessageBox::Yes | QMessageBox::Default,
                               QMessageBox::No | QMessageBox::Escape,
                               QMessageBox::NoButton);
                if (mb.exec() == QMessageBox::Yes) {
        QSqlQuery *query = new QSqlQuery;
        query->prepare("DROP TABLE `"+db.databaseName()+"`.`"+ui->comboBox_2->itemText(ui->comboBox_2->currentIndex())+"`;");
        //Подготовка к удалению комнаты
	if(query->exec())
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Удаление комнаты "+ui->comboBox_2->itemText(ui->comboBox_2->currentIndex())+" выполнено успешно!");
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }else
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("Ошибка удаления комнаты");
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
        QSqlQueryModel *query1 = new QSqlQueryModel;
        query1->setQuery("show tables;");
        ui->comboBox_2->setModel(query1);
        }
//Удаление комнаты
}
void MainWindow::on_checkBox_3_clicked()
{
    if(ui->checkBox_3->isChecked())
        ui->groupBox_8->setEnabled(true);
    else
        ui->groupBox_8->setEnabled(false);
}
void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox mb("Добавление пользователя",
                               "Добавить пользователя "+ui->lineEdit_7->text()+"'@'"+db.hostName()+"?",
                               QMessageBox::Question,
                               QMessageBox::Yes | QMessageBox::Default,
                               QMessageBox::No | QMessageBox::Escape,
                               QMessageBox::NoButton);
                if (mb.exec() == QMessageBox::Yes) {
                QSqlQuery *query = new QSqlQuery;
                query->prepare("create user '"+ui->lineEdit_7->text()+"'@'"+db.hostName()+"' identified by '"+ui->lineEdit_8->text()+"';");
                if(query->exec())
                {
                    QMessageBox msgBox;
                    msgBox.setIcon(QMessageBox::Information);
                    msgBox.setText("Создание пользователя "+ui->lineEdit_7->text()+" выполнено успешно!");
                    msgBox.setDefaultButton(QMessageBox::Ok);
                    msgBox.exec();
                }else
                {
                    QMessageBox msgBox;
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.setText("Ошибка создания пользователя");
                    msgBox.setDefaultButton(QMessageBox::Ok);
                    msgBox.exec();
                }
                QSqlQueryModel *query1 = new QSqlQueryModel;
                query1->setQuery("select user from mysql.user where user!='mysql.sys' and user!="+db.userName()+"'");
                ui->comboBox_3->setModel(query1);
        }
//Добавление пользователя
}
void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox mb("Удаление пользователя",
                               "Удалить пользователя "+ui->comboBox_3->itemText(ui->comboBox_3->currentIndex())+"'@'"+db.hostName()+"'"+"?",
                               QMessageBox::Question,
                               QMessageBox::Yes | QMessageBox::Default,
                               QMessageBox::No | QMessageBox::Escape,
                               QMessageBox::NoButton);
                if (mb.exec() == QMessageBox::Yes) {
    QSqlQuery *query = new QSqlQuery;
    query->prepare("DROP USER '" + ui->comboBox_3->itemText(ui->comboBox_3->currentIndex())+"'@'"+db.hostName()+"'");
    if(query->exec())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Удаление пользователя "+ui->comboBox_3->itemText(ui->comboBox_3->currentIndex())+" выполнено успешно!");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка удаления пользователя");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    QSqlQueryModel *query1 = new QSqlQueryModel;
    query1->setQuery("select user from mysql.user where user!='mysql.sys' and user!='"+db.userName()+"'");
    ui->comboBox_3->setModel(query1);
    }
//Удаление пользователя
}
void MainWindow::on_pushButton_5_clicked()
{
    ui->groupBox_10->setEnabled(true);
    QSqlQueryModel *query = new QSqlQueryModel;
    query->setQuery("select user from mysql.user where user!='mysql.sys' and user!='"+db.userName()+"';");
    ui->listView->setModel(query);
    QSqlQueryModel *query1 = new QSqlQueryModel;
    query1->setQuery("show tables;");
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();
    ui->comboBox_4->addItem("Всем таблицам");
    ui->comboBox_5->addItem("Всем таблицам");
//Добавления варианта назначения привилегий "Всем таблицам".
    for(int i =0;i<query1->rowCount();i++)
    {
        ui->comboBox_4->addItem(query1->data(query1->index(i,0)).toString()); //Считывание значения из query1 в выпадающий список
        ui->comboBox_5->addItem(query1->data(query1->index(i,0)).toString()); //Считывание значения из query1 в выпадающий списокы
    }
}
void MainWindow::on_pushButton_10_clicked()
{
    delete _setGranten;
    _setGranten = new setGranten;
    _setGranten->setWindowTitle("Введите данные пользователя");
    _setGranten->strStd = 0; //Передача типа операции(Назначение привилегий)
    connect(_setGranten,SIGNAL(getBack(int,QString,QString)),this,SLOT(setLoginPsw(int,QString,QString))); //Связь обычного сигнала и слота
    connect(_setGranten,SIGNAL(getBackAdm(int,QString)),this,SLOT(setLoginPswAdm(int,QString))); //Связь секретного сигнала и слота
    _setGranten->show();
}
void MainWindow::slotExecGrantQuery()
{
    QString grantSID; //Переменная, которая хранит в себе выбранные привилегии.
    if (ui->checkBox_4->isChecked())
        grantSID = grantSID + "SELECT,INSERT "; //Запись привилегий.
    QSqlQuery *query = new QSqlQuery;
    QString tables; //Переменная содержащая таблицу(-ы) на которую назначают права
    if(ui->comboBox_4->itemText(ui->comboBox_4->currentIndex())=="Всем таблицам")
        tables = "*"; //Все
    else
        tables = ui->comboBox_4->itemText(ui->comboBox_4->currentIndex());
    query->prepare("GRANT " + grantSID + "ON " + db.databaseName() + "."+tables+" TO '"+ userName + "'@'" + db.hostName() +"' IDENTIFIED BY '"+passWord+"';");
//Подготовка к исполнению
    if(query->exec())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Исполнено");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка исполнения");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    QSqlQuery *query1 = new QSqlQuery;
    query1->exec("flush priveleges"); //Обновление привилегий
//Процедура назначения привилегий
}
void MainWindow::slotExecRevokeQuery()
{
    QString grantSID;
    if (ui->checkBox_5->isChecked())
        grantSID = grantSID + "SELECT,INSERT ";
    QSqlQuery *query = new QSqlQuery;
    QString tables;
    if(ui->comboBox_5->itemText(ui->comboBox_5->currentIndex())=="Всем таблицам")
        tables = "*";
    else
        tables = ui->comboBox_5->itemText(ui->comboBox_5->currentIndex());
    query->prepare("REVOKE " + grantSID + "ON " + db.databaseName() + "."+tables+" FROM '"+ userName + "'@'" + db.hostName()+"'");
//Подготовка к удалению привилегий
    if(query->exec())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Исполнено");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка исполнения");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    QSqlQuery *query1 = new QSqlQuery;
    query1->exec("flush priveleges");
//Процедура удаления привилегий.
}
void MainWindow::slotExecGrantQueryAdm()
{
    QString grantSID;
    if (ui->checkBox_4->isChecked())
        grantSID = grantSID + "SELECT,INSERT ";
    QSqlQuery *query = new QSqlQuery;
    QString tables;
    if(ui->comboBox_4->itemText(ui->comboBox_4->currentIndex())=="Всем таблицам")
        tables = "*";
    else
        tables = ui->comboBox_4->itemText(ui->comboBox_4->currentIndex());
    query->prepare("GRANT " + grantSID + "ON " + db.databaseName() + "."+tables+" TO '"+ userName + "'@'" + db.hostName() + "';");
    if(query->exec())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Исполнено");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка исполнения");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    QSqlQuery *query1 = new QSqlQuery;
    query1->exec("flush priveleges");
//Аналогична slotExecGrantQuery, но использует секретное слово и не требует пароля пользователя.
}
void MainWindow::slotExecRevokeQueryAdm()
{
    QString grantSID;
    if (ui->checkBox_5->isChecked())
        grantSID = grantSID + "SELECT,INSERT ";
    QSqlQuery *query = new QSqlQuery;
    QString tables;
    if(ui->comboBox_5->itemText(ui->comboBox_5->currentIndex())=="Всем таблицам")
        tables = "*";
    else
        tables = ui->comboBox_5->itemText(ui->comboBox_5->currentIndex());
    query->prepare("REVOKE " + grantSID + "ON " + db.databaseName() + "."+tables+" FROM '"+ userName + "'@'" + db.hostName()+"'");
    qDebug() << "REVOKE " + grantSID + "ON " + db.databaseName() + "."+tables+" FROM '"+ userName + "'@'" + db.hostName()+"'";
    if(query->exec())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Исполнено");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Ошибка исполнения");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    QSqlQuery *query1 = new QSqlQuery;
    query1->exec("flush priveleges");
//Аналогична slotExecRevokeQuery, но использует секретное слово и не требует пароля пользователя.
}
void MainWindow::on_pushButton_11_clicked()
{
    delete _setGranten;
    _setGranten = new setGranten;
    _setGranten->setWindowTitle("Введите данные пользователя");
    _setGranten->strStd = 1; //Тип операции - 1. Удаление привилегий.
    connect(_setGranten,SIGNAL(getBack(int,QString,QString)),this,SLOT(setLoginPsw(int,QString,QString))); 
    connect(_setGranten,SIGNAL(getBackAdm(int,QString)),this,SLOT(setLoginPswAdm(int,QString)));
    _setGranten->show();
}
void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QSqlQueryModel *query = new QSqlQueryModel;
    query->setQuery("show grants for '"+ui->listView->model()->data(index).toString()+"'@'"+db.hostName()+"';");
    ui->listView_2->setModel(query);
    QSqlQueryModel *query1 = new QSqlQueryModel;
    query1->setQuery("show tables;");
    ui->listView_3->setModel(query1);
//Прорисовываем все права пользователя и все таблицы в БД.
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    delete _setGranten;
    delete _spravka;
}
void MainWindow::on_action_triggered()
{
    delete _spravka;
    _spravka = new spravka;
    _spravka->show();
}
