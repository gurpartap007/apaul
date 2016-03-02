#ifndef MPD_H
#define MPD_H

#include <QMainWindow>

namespace Ui {
class mpd;
}

class mpd : public QMainWindow
{
    Q_OBJECT

public:
    explicit mpd(QWidget *parent = 0);
    ~mpd();

private:
    Ui::mpd *ui;
};

#endif // MPD_H
