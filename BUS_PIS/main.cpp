#include "busmain.h"
#include <QApplication>
#include "splashscreen.h"
#include <QSplashScreen>


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

    //mySplashScreen *splash = new mySplashScreen();
    //splash->setFixedSize(500,500);
    //splash->show();

    QPixmap pixmap("/home/apaul/Downloads/buslogo.png");
    QSplashScreen splash(pixmap);
    splash.show();

    a.processEvents();

    BusMain w;
    w.showFullScreen();
    splash.finish(&w);

    return a.exec();
}
