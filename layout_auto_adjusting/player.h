#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>

namespace Ui {
class player;
}

class player : public QWidget
{
    Q_OBJECT

public:
    explicit player(QWidget *parent = 0);
    ~player();

private:
    Ui::player *ui;
};

#endif // PLAYER_H
