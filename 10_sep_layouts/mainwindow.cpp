    #include "mainwindow.h"
#include "ui_mainwindow.h"
int flag=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    cam = new camera;
    phone1 = new phone;
    bus1 = new bus;
    video1 = new video;
    player1 = new QMediaPlayer;
    videowidget = new QVideoWidget;
    player1->setMedia(QUrl::fromLocalFile("/home/apaul/out2.mkv"));

    ui->stackedWidget->addWidget(cam);
    ui->stackedWidget->addWidget(phone1);
    ui->stackedWidget->addWidget(bus1);
    ui->stackedWidget->addWidget(video1);
    ui->stackedWidget->addWidget(videowidget);
    videowidget->setAspectRatioMode(Qt::IgnoreAspectRatio);

    connect(ui->toolButton_6, SIGNAL(clicked()), this, SLOT(switch_to_cam()));
    connect(ui->toolButton_7,SIGNAL(clicked()),this,SLOT(switch_to_phone()));
    connect(ui->toolButton_5,SIGNAL(clicked()),this,SLOT(switch_to_bus()));
    connect(ui->toolButton,SIGNAL(clicked()),this,SLOT(switch_to_video()));

    //connect(video1, SIGNAL(playerplay()), this, SLOT(play_video()));

}

MainWindow::~MainWindow()
{
    system("linphonecsh generic \"terminate\"");
    system("linphonecsh exit");
    delete ui;
}


void MainWindow::switch_to_cam()
{
    ui->stackedWidget->setCurrentWidget(cam);
}

void MainWindow::switch_to_phone()
{

 ui->stackedWidget->setCurrentWidget(phone1);
}

void MainWindow::switch_to_bus()
{
    ui->stackedWidget->setCurrentWidget(bus1);
}

void MainWindow::switch_to_video()
{
    ui->stackedWidget->setCurrentWidget(video1);

}

void MainWindow::play_video()
{

    video1->player1->play();

}
