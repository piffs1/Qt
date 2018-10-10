#ifndef ROOMLIST_H
#define ROOMLIST_H
#include <QWidget>
#include <QSqlQueryModel>
#include <newroom.h>
//Файл создан 15.05.2017.
namespace Ui {
class roomlist;
}
class roomlist : public QWidget
{
    Q_OBJECT
public:
    explicit roomlist(QWidget *parent = 0);
    ~roomlist();
    QSqlQueryModel *qModel = new QSqlQueryModel;
private slots:
    void on_listView_doubleClicked(const QModelIndex &index);
private:
    newroom *_newroom;
    Ui::roomlist *ui;
};

#endif // ROOMLIST_H
