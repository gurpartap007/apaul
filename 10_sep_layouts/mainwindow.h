#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "camera.h"
#include "phone.h"
#include "bus.h"
#include "video.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    camera *cam;
    phone *phone1;
    bus *bus1;
    video *video1;
    QMediaPlayer *player1;
    QVideoWidget *videowidget;
signals:
//    void clicked();

private slots:
    void switch_to_cam();
    void switch_to_phone();
    void switch_to_bus();
    void switch_to_video();
    void play_video();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
