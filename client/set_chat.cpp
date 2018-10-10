#include "set_chat.h"
#include "ui_set_chat.h"
#include <QDebug>
#include <QMessageBox>
//Файл создан 15.05.2017. Установка настроек чата.
set_chat::set_chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::set_chat)
{
    ui->setupUi(this);
}
set_chat::~set_chat()
{
    delete ui;
}
void set_chat::keyPressEvent(QKeyEvent *e)
{
    QWidget::keyPressEvent(e);
    if (e->key()==16777220)
        ui->pushButton->click();
    else if (e->key()==16777216)
        this->close();
}
void set_chat::on_pushButton_clicked()
{
    int tmr_interval;
    tmr_interval = ui->spinBox_2->value() * 60 + ui->spinBox->value(); //Перевод в Секунды
    tmr_interval = tmr_interval * 1000; //Перевод в Миллисекунды
    if(tmr_interval == 0)
        QMessageBox::critical(0, QObject::tr("Ошибка"), "Таймер обновления не может быть нулевым");
    else
    {
        emit setIntervalTimer(tmr_interval);
        this->close();
    }
    emit setSizeFont(QFont("MS Shell Dlg 2",ui->spinBox_3->value()));
//Процедура обновления размера шрифта и таймера обновления
}
void set_chat::on_horizontalSlider_valueChanged(int value)
{
    ui->textEdit->setFont(QFont("MS Shell Dlg 2",value));
    ui->textEdit->clear();
    ui->textEdit->append("Пользователь1>Привет\nПользователь2>Привет! Как дела?");
//Просмотр удобного шрифта для пользователя
}
