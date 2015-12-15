#include "videowidget.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>

VideoWidget::VideoWidget(QWidget *parent)
    : QVideoWidget(parent)
{
    maxMode = false;

    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);

    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
}

void VideoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //MAXMODE IS A VARIABLE USED TO TOGGLE BETWEEN FULLSCREEN AND NORMAL STATE
    if(maxMode)
    {
        emit this->goto_normal();
        // event->accept();
        maxMode = 0;
    }
    else
    {
        emit this->goto_fullscreen();
        //  event->accept();
        maxMode = 1;
    }
}


