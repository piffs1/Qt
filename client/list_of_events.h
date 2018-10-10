#ifndef LIST_OF_EVENTS_H
#define LIST_OF_EVENTS_H

#include <QWidget>
#include <QSqlQueryModel>
//Файл создан 15.05.2017.
namespace Ui {
class list_of_events;
}

class list_of_events : public QWidget
{
    Q_OBJECT

public:
    explicit list_of_events(QWidget *parent = 0);
    ~list_of_events();
    QSqlQueryModel *qModel = new QSqlQueryModel; //Принимает запрос
private:
    Ui::list_of_events *ui;
};

#endif // LIST_OF_EVENTS_H
