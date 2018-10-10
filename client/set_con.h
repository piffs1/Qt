#ifndef SET_CON_H
#define SET_CON_H
//Файл создан 15.05.2017.
#include <QWidget>
#include <QKeyEvent>
namespace Ui {
class set_con;
}

class set_con : public QWidget
{
    Q_OBJECT
signals:
    void back_to_port(int _prtBase);
    void back_to_host(QString _hstBase);
    void back_to_data(QString _dataBase);
public:
    explicit set_con(QWidget *parent = 0);
    ~set_con();
    void keyPressEvent(QKeyEvent *e);

private slots:
    void on_pushButton_clicked();

private:
    Ui::set_con *ui;
};

#endif // SET_CON_H
