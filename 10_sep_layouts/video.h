#ifndef VIDEO_H
#define VIDEO_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QUdpSocket>
#include <QFile>

namespace Ui {
class video;
}

class video : public QWidget
{
    Q_OBJECT

public:
    explicit video(QWidget *parent = 0);
    ~video();
    QVideoWidget *videowidget1;
    QMediaPlayer *player1;
    QTimer *timer1;
    QUdpSocket *udpSocketout;
    QFile *inputFile;


private slots:
    void player_play();
    void player_pause();
    void player_stop();

signals:
    void playerplay();
private:
    Ui::video *ui;
};

#endif // VIDEO_H
