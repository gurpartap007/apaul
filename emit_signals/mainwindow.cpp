#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reciever.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reciever *rec;
    rec = new reciever;
    rec->show();
    ui->horizontalLayout->addWidget(rec);
    connect(rec,SIGNAL(play()),this,SLOT(play_button()));
    connect(rec,SIGNAL(pause()),this,SLOT(pause_button()));
    connect(rec,SIGNAL(stop()),this,SLOT(stop_button()));

//ui->label->setText("counter reached");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::play_button()
{
    ui->label->setText("play");
}

void MainWindow::pause_button()
{
    ui->label->setText("pause");
}

void MainWindow::stop_button()
{
    ui->label->setText("stop");
}
