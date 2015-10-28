#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QVideoWidget>
namespace Ui {
class videowidget;
}

class videowidget : public QWidget
{
    Q_OBJECT

public:
    explicit videowidget(QWidget *parent = 0);
    ~videowidget();

private:
    Ui::videowidget *ui;
};

#endif // VIDEOWIDGET_H
