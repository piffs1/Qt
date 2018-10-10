#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <setgranten.h>
#include <spravka.h>
//װאיכ סמחהאם 15.05.2017.
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void signalExecGrantQuery();
    void signalExecRevokeQuery();
private slots:
    void setLoginPsw(int str,QString log,QString psw);

    void setLoginPswAdm(int str,QString log);

    void on_pushButton_7_clicked();

    void on_checkBox_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_clicked();

    void on_pushButton_9_clicked();

    void on_checkBox_2_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_3_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_10_clicked();

    void slotExecGrantQuery();

    void slotExecRevokeQuery();

    void slotExecGrantQueryAdm();

    void slotExecRevokeQueryAdm();

    void on_pushButton_11_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void closeEvent(QCloseEvent *event);

    void on_action_triggered();

private:
    QString userName;
    QString passWord;
    QString username_admin;
    QString password_admin;
    QString database_admin;
    Ui::MainWindow *ui;
    QSqlDatabase db;
    setGranten *_setGranten;
    spravka *_spravka;
};

#endif // MAINWINDOW_H
