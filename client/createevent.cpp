#include "createevent.h"
#include "ui_createevent.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
//Файл создан 15.05.2017. Файл отвечает за создание объявлений в программе.
createEvent::createEvent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::createEvent)
{
    ui->setupUi(this);
}

createEvent::~createEvent()
{
    delete ui;
}

void createEvent::on_calendarWidget_clicked(const QDate &date) // обработка нажатия на дату в календаре
{
    ui->label_3->setText(QString::number(date.day()) + "-" + QString::number(date.month()) + "-" + QString::number(date.year())); //установка даты в надпись
    dateSelect = QString::number(date.year()) + '-' + QString::number(date.month()) + '-' + QString::number(date.day()); // Передается значние даты в глобальную переменную
}

void createEvent::on_pushButton_2_clicked()
{
    if(ui->label_3->text() == "Дата не указана") // Обработка события
        QMessageBox::information(0, QObject::tr("Ошибка"), "Не заполнено поле даты");
    QSqlQuery *query = new QSqlQuery; // Создаем новый query-запрос
    query->prepare("INSERT INTO "+tableSelect+" (`usrnme`, `msg`, `TIME_OF_MSG`,`DATE_OF_MSG`) VALUES ('"+userNME+"', '"+"[ОБЪЯВЛЕНИЕ]"+ui->textEdit->toPlainText()+"',curtime(), '"+dateSelect+"')"); // Подготовка к запросу
    if(query->exec()) //проверка на выполнение запроса
        QMessageBox::information(0, QObject::tr("Информация"), "Мероприятие создано успешно!");
    else
        QMessageBox::information(0, QObject::tr("Ошибка"), "Ошибка при создании мероприятия!");
    this->close(); // Закрытие формы.
}
