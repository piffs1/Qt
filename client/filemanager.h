#ifndef FILEMANAGER_H
#define FILEMANAGER_H
//���� ������ 15.05.2017. ���� �������� �� ��������� �������.
#include <QWidget>
#include <QSqlQueryModel>
namespace Ui {
class filemanager;
}

class filemanager : public QWidget
{
    Q_OBJECT

public:
    explicit filemanager(QWidget *parent = 0);
    ~filemanager();
    QSqlQueryModel *qModel = new QSqlQueryModel;
    QString fullfilename; //���������� ���������� ������� ����� �����
    QString filename; //���������� ����������, ������ ������ ��� �����
    QString filetype;//���������� ����������, ������ ������ ��� �����
    QString tableSelect;//���������� ����������, ������ ���������� � ������� �������.
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::filemanager *ui;
};

#endif // FILEMANAGER_H
