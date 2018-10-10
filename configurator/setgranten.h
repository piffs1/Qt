#ifndef SETGRANTEN_H
#define SETGRANTEN_H

#include <QWidget>
#include <QKeyEvent>
//װאיכ סמחהאם 15.05.2017.
namespace Ui {
class setGranten;
}

class setGranten : public QWidget
{
    Q_OBJECT

public:
    explicit setGranten(QWidget *parent = 0);
    ~setGranten();
    void keyPressEvent(QKeyEvent *e);
    int strStd;
signals:
    void getBack(int,QString,QString);
    void getBackAdm(int,QString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::setGranten *ui;
};

#endif // SETGRANTEN_H
