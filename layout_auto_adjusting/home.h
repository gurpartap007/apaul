#ifndef HOME_H
#define HOME_H

#include <QWidget>

namespace Ui {
class home;
}

class home : public QWidget
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = 0);
    ~home();

private:
    Ui::home *ui;
};

#endif // HOME_H
