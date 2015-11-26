#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     /***************************************************
     *         This class demonstrates how to make         *
     *              new path if it doesn't exist                      *
     *                                                                              *
     * *************************************************/
    dir_example = new dir;

     /****************************************************
     *  This class demonstrates how to open or create   *
     *  new text file if it doesn't exist and how to read    *
     *  from this file using QTextStream                          *
     * **************************************************/
    file_example = new file;
}

MainWindow::~MainWindow()
{
    delete ui;
}
