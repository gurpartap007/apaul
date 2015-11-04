#ifndef FFMPEGTASK_H
#define FFMPEGTASK_H

#include <QtCore/QtGlobal>
#include <QWidget>
#include <QMainWindow>
#include <QTcpSocket>
#include <QProcess>

class FFmpegTask : public QWidget
{
public:
    explicit FFmpegTask(QWidget *parent = 0);
    ~FFmpegTask();
    //void doConnect();
    //void session_splitter(QByteArray &received_data);
    //void rtp_to_frame_splitter(QByteArray &received_data);

public slots:
    //void connected();
    //void disconnected();
    //void readyRead();
    //void start_getting_frames();
    void video_saving();
    void video_streaming_at_low_fps();

private:
    //QTcpSocket *socket;
    //QTcpSocket *send_socket;
    QProcess *mSavingProcess;
    QProcess *mStreamingProcess;
    QTimer *timer;
};

#endif // FFMPEGTASK_H
