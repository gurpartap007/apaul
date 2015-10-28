#ifndef WIDGET3_H
#define WIDGET3_H

#include <QWidget>

namespace Ui {
class widget3;
}

class widget3 : public QWidget
{
    Q_OBJECT

public:
    explicit widget3(QWidget *parent = 0);
    ~widget3();

private:
    Ui::widget3 *ui;
};

#endif // WIDGET3_H
