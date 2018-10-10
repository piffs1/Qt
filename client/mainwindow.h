#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <set_con.h>
#include <QTimer>
#include <set_chat.h>
#include <QKeyEvent>
#include <roomlist.h>
#include <spravka.h>
//Файл создан 15.05.2017.
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *e);
public slots:
    void setTimer_base(int _tmrBase);
    void setPort_base(int _prtBase);
    void setHost_base(QString _hstBase);
    void setData_base(QString _dataBase);
    void setSize_font(QFont _font);

private slots:
    void update();

    void on_action_2_triggered();

    void on_action_triggered();

    void on_pushButton_clicked();

    void on_actionrecconect_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void closeEvent(QCloseEvent *event);

    void on_action_5_triggered();

private:
    spravka *_spravka;
    QFont font_size;
    int supID;
    QString data_base;
    Ui::MainWindow *ui;
    set_con *_set_con;
    set_chat *_set_chat;
    int port_base;
    QString host_base;
    QSqlDatabase db;
    QTimer *tmr;
    int tmr_interval;
    roomlist *_roomlist;
};

#endif // MAINWINDOW_H
