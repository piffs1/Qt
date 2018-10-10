#ifndef SET_CHAT_H
#define SET_CHAT_H
//װאיכ סמחהאם 15.05.2017.
#include <QWidget>
#include <QKeyEvent>
namespace Ui {
class set_chat;
}

class set_chat : public QWidget
{
    Q_OBJECT
signals:
    void setIntervalTimer(int);
    void setSizeFont(QFont);
public:
    explicit set_chat(QWidget *parent = 0);
    ~set_chat();
    void keyPressEvent(QKeyEvent *e);
private slots:
    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::set_chat *ui;
};

#endif // SET_CHAT_H
