#include "mainwindow.h"
#include "ui_mainwindow.h"
/** @brief Default constructor of Mainwindow class to display mainwindow
 * @ingroup camera
 * @param parent - QWidget pointer
 * */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   if( QCameraInfo::availableCameras().count() > 0)
            qDebug() << "true" ;
}

MainWindow::~MainWindow()
{
    delete ui;
}
