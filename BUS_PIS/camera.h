#ifndef CAMERA
#define CAMERA

#include <QWidget>
#include <QMouseEvent>
#include <QMediaPlayer>
#include "videowidget.h"
#include <QThread>
#include <QLabel>

namespace Ui {
class Camera;
}

class Camera : public QWidget
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = 0);
    VideoWidget *videoWidget1;
    VideoWidget *videoWidget2;
    VideoWidget *videoWidget3;
    VideoWidget *videoWidget4;
    QMediaPlayer *player1;
    QMediaPlayer *player2;
    QMediaPlayer *player3;
    QMediaPlayer *player4;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    ~Camera();

public slots:
    void widget1_fullscreen();
    void widget1_normal();
    void widget2_fullscreen();
    void widget2_normal();
    void widget3_fullscreen();
    void widget3_normal();
    void widget4_fullscreen();
    void widget4_normal();

private:
    Ui::Camera *ui;
};

#endif // CAMERA
