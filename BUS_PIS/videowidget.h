#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>

class VideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    VideoWidget(QWidget *parent = 0);
    bool maxMode;

signals:
    void goto_fullscreen();
    void goto_normal();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // VIDEOWIDGET_H
