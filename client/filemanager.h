#ifndef FILEMANAGER_H
#define FILEMANAGER_H
//Файл создан 15.05.2017. Файл отвечает за настройку доступа.
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
    QString fullfilename; //Глобальная переменная полного имени файла
    QString filename; //Глобальная переменная, хранит только имя файла
    QString filetype;//Глобальная переменная, хранит только тип файла
    QString tableSelect;//Глобальная переменная, хранит информацию о текущей таблице.
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::filemanager *ui;
};

#endif // FILEMANAGER_H
