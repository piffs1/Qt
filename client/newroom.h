#ifndef NEWROOM_H
#define NEWROOM_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QTimer>
#include <QCloseEvent>
#include <set_chat.h>
#include <createevent.h>
#include <list_of_events.h>
#include <uploadfile.h>
#include <filemanager.h>
#include <spravka_v_2.h>
//װאיכ סמחהאם 15.05.2017.
namespace Ui {
class newroom;
}

class newroom : public QMainWindow
{
    Q_OBJECT

public:
    void setTableSelect(QString &tbl);
    explicit newroom(QWidget *parent = 0);
    ~newroom();
    QFont font_size;
    void keyPressEvent(QKeyEvent *e);
public slots:
    void setTimer_base(int _tmrBase);
    void setFont_size(QFont font);
private slots:
    void on_pushButton_clicked();
    void update1();
    void closeEvent(QCloseEvent *event);


    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();
    
    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_action_4_triggered();

private:
    filemanager *_fm;
    uploadfile *_uf;
    QString supDate;
    createEvent *_createEvent;
    list_of_events *le;
    set_chat *_set_chat;
    QString tableSelect;
    Ui::newroom *ui;
    QTimer *tmr1;
    int tmr_interval;
    int supID;
    spravka_v_2 *_spravka_v2;
};

#endif // NEWROOM_H
