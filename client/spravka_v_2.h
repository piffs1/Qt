#ifndef SPRAVKA_V_2_H
#define SPRAVKA_V_2_H
//װאיכ סמחהאם 15.05.2017.
#include <QWidget>

namespace Ui {
class spravka_v_2;
}

class spravka_v_2 : public QWidget
{
    Q_OBJECT

public:
    explicit spravka_v_2(QWidget *parent = 0);
    ~spravka_v_2();

private:
    Ui::spravka_v_2 *ui;
};

#endif // SPRAVKA_V_2_H
