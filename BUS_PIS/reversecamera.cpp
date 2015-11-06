#include "reversecamera.h"
#include "ui_reversecamera.h"

ReverseCamera::ReverseCamera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReverseCamera)
{
    player1 = new QMediaPlayer;
    player1->setMedia(QUrl("rtsp://192.168.0.128"));
    player1->play();

    ui->setupUi(this);

    videoWidget1 = new VideoWidget();
    videoWidget1->setAspectRatioMode(Qt::IgnoreAspectRatio);
    player1->setVideoOutput(videoWidget1);

    ui->Box1->addWidget(videoWidget1);
    videoWidget1->setUpdatesEnabled(true);
}

ReverseCamera::~ReverseCamera()
{
    delete ui;
}

