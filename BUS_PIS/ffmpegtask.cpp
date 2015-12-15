#include "ffmpegtask.h"
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <stdlib.h>
#include <sys/types.h>

FFmpegTask::FFmpegTask(QWidget *parent) :
    QWidget(parent)
{
    //ffmpeg for video saving
    mSavingProcess = new QProcess(this);
    //connect(mSavingProcess, SIGNAL(started()), this, SLOT(video_streaming_at_low_fps()));

    //ffmpeg for video saving
    mStreamingProcess = new QProcess(this);

    //File Handling
    //raw_file = QString::fromLatin1(PATH_RAW_FILE);
    //raw_file = raw_file + QString::fromLatin1("raw_file");

    //socket = new QTcpSocket(this);

    //connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    //connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    //connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    //send_socket = new QTcpSocket(this);

    //connect(send_socket, SIGNAL(connected()),this, SLOT(connected()));
    //connect(send_socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    //qDebug() << "connecting..."; // this is not blocking call
    //socket->setSocketOption(QAbstractSocket::KeepAliveOption,true);
    //socket->setReadBufferSize(120000);
    //socket->connectToHost("192.168.0.128", 554); // we need to wait...
    //if(!socket->waitForConnected(5000))
    //{ qDebug() << "Error: " << socket->errorString(); }
    //send_socket->connectToHost("192.168.0.31", 9010); // we need to wait...
    //if(!send_socket->waitForConnected(5000))
    //{ qDebug() << "Error: " << send_socket->errorString(); }
    //QTimer::singleShot(100, this, SLOT(video_saving()));
  //  QTimer::singleShot(200, this, SLOT(video_streaming_at_low_fps()));
//video_streaming_at_low_fps();
  // QTimer::singleShot(1000, this, SLOT(video_saving()));
video_saving();
    //start_getting_frames();
}

FFmpegTask::~FFmpegTask()
{
    //socket->close();
    //send_socket->close();
    mSavingProcess->deleteLater();
    mStreamingProcess->deleteLater();
    //system("pkill -9 ffmpeg");
}

void FFmpegTask::video_saving()
{
    QString program = "/usr/bin/ffmpeg";
    QString input = "/dev/video1";
    //QString subtitles = "subtitles=/home/apaul/Downloads/1.srt";
    QStringList arguments;

    //OPENING VIDEO FILE
    QString folderpath = "/home/apaul/Downloads/Saved Videos/";
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString dtstring = date.toString() + "-" + time.toString() + "/";
    folderpath = folderpath + dtstring;
    QDir dir(folderpath);
    dir.mkpath(folderpath);
    global_video_location = folderpath;
   folderpath = folderpath + "out%03d.avi";
    //folderpath = folderpath + "webcam.avi";
   // arguments << "-f" << "v4l2" << "-i" << input << "-an" << "-f" << "segment" << "-c" << "copy" << "-reset_timestamps" << "1" << "-segment_time" << "00:01:00" << "-segment_format" << "mp4" << folderpath;
    //arguments << input;
    arguments << "-f" << "v4l2" << "-i" << input <<  "-vcodec" << "libx264" << "-pix_fmt" << "yuv420p" << "-reset_timestamps" << "1" << "-f" << "segment" << "-segment_time" << "00:01:00" << "-segment_format" << "mp4" <<  folderpath;
    mSavingProcess->setProcessChannelMode(QProcess::MergedChannels);
    mSavingProcess->start(program, arguments);
}

void FFmpegTask::video_streaming_at_low_fps()
{
    //ffmpeg -re -i output.avi -r 5 -f rtp rtp://localhost:7000
   QString program = " gst-launch -v v4l2src ! v4l2sink device=/dev/video1";
   // QString input = "/home/apaul/Downloads/final.avi";
   // QString output = "rtp://224.1.2.3:7000";
   // QStringList arguments;
    //arguments << "-re" << "-i" << input << "-r" << "5" << "-f" << "rtp" << output;
    mStreamingProcess->setProcessChannelMode(QProcess::MergedChannels);
    mStreamingProcess->start(program);
}



