#include "camera.h"
#include "ui_camera.h"
#include <QDebug>
#include <QVideoEncoderSettings>
#include <QTimer>
#include <QPainter>

bool maxMode = false;

Camera::Camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Camera)
{
    //MAKING 4 INDIVIDUAL PLAYERS FOR EACH CAMERA
    player1 = new QMediaPlayer;
    player2 = new QMediaPlayer;
    player3 = new QMediaPlayer;
    player4 = new QMediaPlayer;

    //ASSIGNING URLTO THE PLAYER
    player1->setMedia(QUrl("rtsp://192.168.1.88"));
    player2->setMedia(QUrl("rtsp://192.168.1.88"));
    player3->setMedia(QUrl("rtsp://192.168.1.88"));
    player4->setMedia(QUrl("rtsp://192.168.1.88"));

    ui->setupUi(this);

    //ASSIGNING VIDEOWIDGETS TO EACH MEDIA PLAYER
    //IGNORING ASPECT RATIO TO GET FULLL WIDGET FIT
    videoWidget1 = new VideoWidget();
    videoWidget1->setAspectRatioMode(Qt::IgnoreAspectRatio);
    player1->setVideoOutput(videoWidget1);
    connect(videoWidget1,SIGNAL(goto_fullscreen()),this,SLOT(widget1_fullscreen()));  //connecting signal to corresponding function(slot)
    connect(videoWidget1,SIGNAL(goto_normal()),this,SLOT(widget1_normal()));

    videoWidget2 = new VideoWidget;
    videoWidget2->setAspectRatioMode(Qt::IgnoreAspectRatio);
    player2->setVideoOutput(videoWidget2);
    connect(videoWidget2,SIGNAL(goto_fullscreen()),this,SLOT(widget2_fullscreen()));
    connect(videoWidget2,SIGNAL(goto_normal()),this,SLOT(widget2_normal()));

    videoWidget3 = new VideoWidget;
    videoWidget3->setAspectRatioMode(Qt::IgnoreAspectRatio);
    player3->setVideoOutput(videoWidget3);
    connect(videoWidget3,SIGNAL(goto_fullscreen()),this,SLOT(widget3_fullscreen()));
    connect(videoWidget3,SIGNAL(goto_normal()),this,SLOT(widget3_normal()));

    videoWidget4 = new VideoWidget;
    videoWidget4->setAspectRatioMode(Qt::IgnoreAspectRatio);
    player4->setVideoOutput(videoWidget4);
    connect(videoWidget4,SIGNAL(goto_fullscreen()),this,SLOT(widget4_fullscreen()));
    connect(videoWidget4,SIGNAL(goto_normal()),this,SLOT(widget4_normal()));

    //ADDING WIDGETS TO SEPARATE LINEAR LAYOUTS
    ui->Box1->addWidget(videoWidget1);
    ui->Box1->addWidget(videoWidget2);
    ui->Box2->addWidget(videoWidget3);
    ui->Box2->addWidget(videoWidget4);

    //MAKING WIDGET UPDATE ENABLED BECAUSE WE NEED TO SHOW INFORMATION IN A LABEL BOX ALONG WITH VIDEO
    videoWidget1->setUpdatesEnabled(true);
    videoWidget2->setUpdatesEnabled(true);
    videoWidget3->setUpdatesEnabled(true);
    videoWidget4->setUpdatesEnabled(true);

    //MAKING LABELBOX INSIDE EACH VIDEO WIDGET
    label1 = new QLabel(videoWidget1);
    label1->setGeometry(845,5,100,100);
    label1->setStyleSheet("color: rgb(255, 255, 255);background-color: rgba(255, 255, 255, 20);qproperty-alignment: AlignCenter;font:20pt;");
    label1->setText("Test\nText");
    label1->setVisible(true);

    label2 = new QLabel(videoWidget2);
    label2->setGeometry(845,5,100,100);
    label2->setStyleSheet("color: rgb(255, 255, 255);background-color: rgba(255, 255, 255, 20);qproperty-alignment: AlignCenter;font:20pt;");
    label2->setText("Test\nText");
    label2->setVisible(true);

    label3 = new QLabel(videoWidget3);
    label3->setGeometry(845,5,100,100);
    label3->setStyleSheet("color: rgb(255, 255, 255);background-color: rgba(255, 255, 255, 20);qproperty-alignment: AlignCenter;font:20pt;");
    label3->setText("Test\nText");
    label3->setVisible(true);

    label4 = new QLabel(videoWidget4);
    label4->setGeometry(845,5,100,100);
    label4->setStyleSheet("color: rgb(255, 255, 255);background-color: rgba(255, 255, 255, 20);qproperty-alignment: AlignCenter;font:20pt;");
    label4->setText("Test\nText");
    label4->setVisible(true);

    //PLAYING THE VIDEO
    player1->play();
    player2->play();
    player3->play();
    player4->play();
}

Camera::~Camera()
{
    delete ui;
}

void Camera::widget1_fullscreen()
{
    //GOING FULLSCREEN, SO LABEL POSITION HAS TO ADJUST AND OTHER WIDGETS HAVE TO HIDE
    label1->setGeometry(1800,5,100,100);
    videoWidget2->hide();
    videoWidget3->hide();
    videoWidget4->hide();
}

void Camera::widget1_normal()
{
    //COMING BACK TO 4 SCREEN MODE SO LABEL HAS TO READJUST AND OTHER WIDGETS HAVE TO SHOW AGAIN
    label1->setGeometry(845,5,100,100);
    videoWidget2->show();
    videoWidget3->show();
    videoWidget4->show();
}

void Camera::widget2_fullscreen()
{
    label2->setGeometry(1800,5,100,100);
    videoWidget1->hide();
    videoWidget3->hide();
    videoWidget4->hide();
}

void Camera::widget2_normal()
{
    label2->setGeometry(845,5,100,100);
    videoWidget1->show();
    videoWidget3->show();
    videoWidget4->show();
}

void Camera::widget3_fullscreen()
{
    label3->setGeometry(1800,5,100,100);
    videoWidget1->hide();
    videoWidget2->hide();
    videoWidget4->hide();
}

void Camera::widget3_normal()
{
    label3->setGeometry(845,5,100,100);
    videoWidget1->show();
    videoWidget2->show();
    videoWidget4->show();
}

void Camera::widget4_fullscreen()
{
    label4->setGeometry(1800,5,100,100);
    videoWidget1->hide();
    videoWidget2->hide();
    videoWidget3->hide();
}

void Camera::widget4_normal()
{
    label4->setGeometry(845,5,100,100);
    videoWidget1->show();
    videoWidget2->show();
    videoWidget3->show();
}





