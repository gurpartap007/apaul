#include "busmain.h"
#include <QApplication>
#include "splashscreen.h"
#include <QSplashScreen>
QDesktopWidget *screen;
QHBoxLayout *mainlayout;

/************************************************************************************
  THIS IS THE MAIN FUNCTION
  OUR MAINWINDOW OF VIEW IS BUSMAIN
  BUSMAIN HAS A STACKED WIDGET IN WHICH THE CAMERA WIDGET IS ADDED
  WHEN THE BUSMAIN OBJECT IS CREATED BELOW, IT FURTHER CREATES A CAMERA OBJECT
  IN IT'S CONSTRUCTOR WHICH FURTHER CREATES VIDEOWIDGETS IN THE CAMERA CONSTRUCTOR

  THE FUNCTIONALITY TO GO FULLSCREEEN AND BACK HAS BEEN IMPLEMENTED BY SIGNALS IN THE
  VIDEOWIDGET CLASS

  ON EMISSION OF THESE SIGNALS SLOTS ARE EXECUTED IN THE CAMERA CLASS
*************************************************************************************/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    screen = new QDesktopWidget;
    //  mySplashScreen *splash = new mySplashScreen();
    // splash->setFixedSize(1366,768);
    // splash->show();
    mainlayout = new QHBoxLayout;
    system(" modprobe v4l2loopback devices=2" );
    system(" gst-launch -v v4l2src ! v4l2sink device=/dev/video1 &");
    QPixmap pixmap("/home/apaul/Pictures/images/buslogo.png");
    QSplashScreen splash(pixmap);
    splash.show();
    screen = a.desktop();
    a.processEvents();
    delay::msleep(2000);
    BusMain w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.setGeometry(0,0,screen->width(),screen->height());

    w.showFullScreen();


    splash.finish(&w);

    return a.exec();
}
