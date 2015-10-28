#ifndef WIDGET2_H
#define WIDGET2_H

#include <QWidget>

namespace Ui {
class widget2;
}

class widget2 : public QWidget
{
    Q_OBJECT

public:
    explicit widget2(QWidget *parent = 0);
    ~widget2();

private:
    Ui::widget2 *ui;
};

#endif // WIDGET2_H
