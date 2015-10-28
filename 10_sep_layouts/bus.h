#ifndef BUS_H
#define BUS_H

#include <QWidget>

namespace Ui {
class bus;
}

class bus : public QWidget
{
    Q_OBJECT

public:
    explicit bus(QWidget *parent = 0);
    ~bus();

private:
    Ui::bus *ui;
};

#endif // BUS_H
