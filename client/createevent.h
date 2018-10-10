#ifndef CREATEEVENT_H
#define CREATEEVENT_H
//���� ������ 15.05.2017.
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
    QString userNME; //���������� ����������, ���������� �� ���������� �������� ��������
    QString tableSelect; //����������� ����������, ���������� �� ������ � ������� ��������
    QString dateSelect; //���������� ����������, ���������� �� ������� ���� �� �������

private slots:
    void on_calendarWidget_clicked(const QDate &date); //��������� ������� ���������

    void on_pushButton_2_clicked(); //��������� ������� �������

private:
    Ui::createEvent *ui;
};

#endif // CREATEEVENT_H
