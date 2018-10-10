#ifndef SPRAVKA_H
#define SPRAVKA_H
//װאיכ סמחהאם 15.05.2017.
#include <QWidget>

namespace Ui {
class spravka;
}

class spravka : public QWidget
{
    Q_OBJECT

public:
    explicit spravka(QWidget *parent = 0);
    ~spravka();

private:
    Ui::spravka *ui;
};

#endif // SPRAVKA_H
