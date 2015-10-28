#include "video.h"
#include "ui_video.h"
#include <QTimer>

video::video(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::video)
{
    ui->setupUi(this);

    videowidget1 = new QVideoWidget;
    player1 = new QMediaPlayer;
   // player1->setMedia(QUrl::fromLocalFile("/home/apaul/out2.mkv"));
        player1->setMedia(QUrl("http://127.0.0.1:8000/mpd.ogg"));
    ui->horizontalLayout->addWidget(videowidget1);
    videowidget1->setAspectRatioMode(Qt::IgnoreAspectRatio);
    connect(ui->play,SIGNAL(clicked()),this,SLOT(player_play()));
    connect(ui->pause,SIGNAL(clicked()),this,SLOT(player_pause()));
    connect(ui->stop,SIGNAL(clicked()),this,SLOT(player_stop()));
}

video::~video()
{
    delete ui;
}

void video::player_play()
{
   // player1->setVideoOutput(videowidget1);
    //videowidget1->show();
    qDebug() << "play button pressed";
    //player1->play();
   //emit this->playerplay();
 timer1 =  new QTimer (this);
       udpSocketout = new QUdpSocket(this);
   /*    inputFile.setFileName(playlist.at(playIDfile));
           if (!inputFile.open(QIODevice::ReadOnly))
           {
               msg.warning(this,"File ERROR","File not found!",QMessageBox::Ok);
               return;
           }
       fileinfo = new QFileInfo (inputFile);
       txfilename = fileinfo->fileName();
       ui->playedFile->setText("Now played: " + txfilename);
       connect(timer1, SIGNAL(timeout()),this, SLOT(writeDatagrams()));
       timer1->start(15);*/
}

void video::player_pause()
{
 player1->pause();
}

void video::player_stop()
{
player1->stop();
videowidget1->hide();
}
