#ifndef SCROLLING_H
#define SCROLLING_H

#include <QMainWindow>

namespace Ui {
class scrolling;
}

class scrolling : public QMainWindow
{
    Q_OBJECT

public:
    explicit scrolling(QWidget *parent = 0);
    ~scrolling();

private:
    Ui::scrolling *ui;
};

#endif // SCROLLING_H
