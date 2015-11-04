#include "mythread.h"
#include <QEventLoop>
MyThread::MyThread(int interval, QObject* parent)
    : QThread(parent)
    , i(0)
    , inc(-1)
    , intvl(interval)
    , timer(0)
{
    if(timer == 0)
    {
        timer = new QTimer(this);
    }
    timer->start(intvl);
}

MyThread::~MyThread()
{
    if(timer != 0)
        delete timer;
}

void MyThread::run(void)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(count()));
    exec();
}

void MyThread::stop(void)
{
    quit();
    wait();
    deleteLater();
}

void MyThread::count(void)
{
    if((i >= 100) || ( i <= 0))
        inc = -inc;

    i += inc;
    emit valueChanged(i);
}
