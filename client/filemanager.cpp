#include "filemanager.h"
#include "ui_filemanager.h"
#include <QFileDialog>
#include <QSqlQuery>
#include <QDebug>
//Файл создан 15.05.2017. Файл отвечает за работу файлового менеджера.
filemanager::filemanager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::filemanager)
{
    ui->setupUi(this);
    ui->tableView->setModel(qModel); // Установка модели в таблицу tableView
}
filemanager::~filemanager()
{
    delete ui;
}
void filemanager::on_pushButton_clicked()
{
    filetype = ""; //Обнуление переменной, для предотвращения ошибок при повторном использовании
    QByteArray ba= ""; //Массив байтов - для считывания данных из БД
    QSqlQuery *query = new QSqlQuery;
    query->prepare("SELECT MSG,FILE FROM "+tableSelect+"  WHERE ID="+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toString()+";");
    //Подготовка к выполнению запроса
    query->exec();//Запуск запроса
    while(query->next()) //Считывание с запроса данных
    {
        ba = query->value(1).toByteArray(); //Заполнение байтового массива информацией
        fullfilename = query->value(0).toString(); //Считывание полного имени файла с БД
    }
    ba = ba.fromBase64(ba);//Перевод под стандарт base64 для корректного считывания
    QString adr = QFileDialog::getSaveFileName(this, tr("Сохранить")); //Диалоговое окно выбора пути для сохранения файла
    if (!adr.isEmpty()){ //Обработка случая, если адрес не пуст.
    int iterator = fullfilename.size()-1; //переменная для прохождения по наименованию файла
    if(adr.contains(".")){//Обработка случая перезаписи файла.
        QFile file(adr); //Обозначение файла
        if(file.open(QFile::WriteOnly))
        {
            file.write(ba); //Запись в файл
            file.close();
        }
    }else
    if(fullfilename.contains(".")) //Обработка случая, если файл содержит разрешение.
    {
        for(int i = fullfilename.size()-1;i>0;i--)
        {
            if(fullfilename[i] == '.')
                break;
            iterator--; //Переменная итератор служит отправной точкой для считывания формата
        }
        for(int i = iterator;i <=fullfilename.size()-1;i++)
            filetype = filetype + fullfilename[i]; //Считывание посимвольно типа файла
        QFile file(adr+filetype); //Создание файла. Адрес+его тип.
        if (file.open(QFile::WriteOnly))
        {
            file.write(ba);
            file.close();
        }
    }else{
        QFile file(adr);
        if (file.open(QFile::WriteOnly))
        {
            file.write(ba);
            file.close();
        }
    }
    }
    filetype = "";
    fullfilename = "";
//Обнуляем переменные для предотвращения ошибок.
}

void filemanager::on_pushButton_2_clicked()
{
    int rows=qModel->rowCount(); //Количество стобцов в модели
    int columns=qModel->columnCount(); //Количество колонок в модели

    bool chek = false; 
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            if (qModel->data(qModel->index(i,j)).toString().contains(ui->lineEdit->text(), Qt::CaseInsensitive)) //Проверка на содержание текста в ячейке
            {
                ui->tableView->selectRow(i); //Выбор столбца
                ui->tableView->setFocus(); 
                chek=true;
            }
        }
        if (chek)
        break;
    }
}
