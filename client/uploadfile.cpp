#include "uploadfile.h"
#include "ui_uploadfile.h"
#include <QSqlQuery>
#include <QFileDialog>
#include <QMessageBox>
//Файл создан 15.05.2017. Файл отвечает за отправку файлов на сервер.
uploadfile::uploadfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uploadfile)
{
    ui->setupUi(this);
    ui->label_2->hide();
    ui->label_3->hide();
    ui->pushButton_2->hide();
//Скрытие кнопки загрузки и данных файла
}
uploadfile::~uploadfile()
{
    delete ui;
}
void uploadfile::on_pushButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Открыть"),"",tr("All Files(*)")); //Диалоговое окно для открытия файла
    QByteArray ba;//Байтовый массив для считывания файла
    fullfilename = ""; //Обнуляем полное файловое имя для предотвращения ошибок
    int iterator=fileName.size()-1; //Переменная итератор отвечает за нахождение индекса содержащий точку. 
    for(int i = fileName.size()-1;i>0;i--)
    {
        if(fileName[i] == '/')
            break;
        iterator--; 
    }
    for(int i = iterator+1;i <= fileName.size()-1; i++)
        fullfilename = fullfilename + fileName[i]; //Запись формата файла 
    if(!fileName.isEmpty())
    {
        ui->label_2->show();
        ui->label_3->show();
        ui->pushButton_2->show();
        ui->label_3->setText(fullfilename);
//Обработка события невыбранного файла.
    }else
    {
        ui->label_2->hide();
        ui->label_3->hide();
        ui->pushButton_2->hide();
//Иначе показ кнопок загрузки и данных о файле.
    }

}
void uploadfile::on_pushButton_2_clicked()
{
    QSqlQuery *query = new QSqlQuery;
    QByteArray ba="";
    QFile f(fileName);
    if(!fileName.contains("zip") && f.size() < 15295906){ //Обработка файлов с форматом zip и размер файла. Если файл меньше 15 МБ, то загрузка возможна
        if(f.open(QIODevice::ReadOnly))
        {
            ba=f.readAll().toBase64(); //Перевод в стандарт base64();
            f.close();
            query->prepare("INSERT INTO `"+tableSelect+"` (`usrnme`,`msg`, `DATE_OF_MSG`, `TIME_OF_MSG`,`FILE`) SELECT USER(),'"+fullfilename+"',curdate(),curtime(),'"+ba+"'");
            //Подготовка к загрузке файла на сервер
	    if(query->exec()) //Если файл загружен
                QMessageBox::information(0, QObject::tr("Информация"), "Файл успешно загружен на сервер!");
            else
                QMessageBox::information(0, QObject::tr("Ошибка"), "Ошибка при загрузке файла!");
            query->clear();//Очистка
        }
    }else
        if(fileName.contains("zip") && f.size() < 3000000) //Обработка передачи архива "zip".
        {
            ba=f.readAll().toBase64(); 
            f.close();
            query->prepare("INSERT INTO `"+tableSelect+"` (`usrnme`,`msg`, `DATE_OF_MSG`, `TIME_OF_MSG`,`FILE`) SELECT USER(),'"+fullfilename+"',curdate(),curtime(),'"+ba+"'");
            if(query->exec())
                QMessageBox::information(0, QObject::tr("Информация"), "Файл успешно загружен на сервер!");
            else
                QMessageBox::information(0, QObject::tr("Ошибка"), "Ошибка при загрузке файла!");
            query->clear();
        }else
            QMessageBox::information(0, QObject::tr("Ошибка"), "Файл превышает максимально допустимый размер");
}
