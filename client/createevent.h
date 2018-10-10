#ifndef CREATEEVENT_H
#define CREATEEVENT_H
//Файл создан 15.05.2017.
#include <QWidget>

namespace Ui {
class createEvent;
}

class createEvent : public QWidget
{
    Q_OBJECT

public:
    explicit createEvent(QWidget *parent = 0);
    ~createEvent();
    QString userNME; //Глобальная переменная, отвечающая за содержание текущего никнейма
    QString tableSelect; //Глоблальная переменная, отвечающая за работу с текущей таблицей
    QString dateSelect; //Глобальная переменная, отвечающая за текущую дату на сервере

private slots:
    void on_calendarWidget_clicked(const QDate &date); //Обработка нажатия календаря

    void on_pushButton_2_clicked(); //Обработка нажатия клавиши

private:
    Ui::createEvent *ui;
};

#endif // CREATEEVENT_H
