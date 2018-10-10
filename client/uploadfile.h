#ifndef UPLOADFILE_H
#define UPLOADFILE_H
//װאיכ סמחהאם 15.05.2017.
#include <QWidget>

namespace Ui {
class uploadfile;
}

class uploadfile : public QWidget
{
    Q_OBJECT

public:
    explicit uploadfile(QWidget *parent = 0);
    ~uploadfile();
    QString fullfilename;
    QString fileName;
    QString filetype;
    QString tableSelect;
    int supID;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::uploadfile *ui;
};

#endif // UPLOADFILE_H
