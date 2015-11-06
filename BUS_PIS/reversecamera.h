#ifndef REVERSECAMERA_H
#define REVERSECAMERA_H

#include <QWidget>
#include <QMediaPlayer>
#include "videowidget.h"

namespace Ui {
class ReverseCamera;
}

class ReverseCamera : public QWidget
{
    Q_OBJECT

public:
    explicit ReverseCamera(QWidget *parent = 0);
    VideoWidget *videoWidget1;
    QMediaPlayer *player1;
    ~ReverseCamera();

signals:
    void reverse_done();

private:
    Ui::ReverseCamera *ui;
};

#endif // REVERSECAMERA_H
