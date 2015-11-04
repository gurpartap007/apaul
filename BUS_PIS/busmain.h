#ifndef BUSMAIN_H
#define BUSMAIN_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QThread>
#include <QStatusBar>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QEventLoop>
#include <QTcpSocket>
#include <QTcpServer>
#include <QSocketNotifier>
#include <QMediaPlayer>
#include <QTimer>
#include <QMediaPlaylist>
#include "home.h"
#include "camera.h"
#include "reversecamera.h"
#include "player.h"
#include "route_selection.h"
#include "running_route.h"
#include "mythread.h"
#include "prerecorded.h"
#include "ffmpegtask.h"

#define L_FRAME_START       4
#define L_FRAME_LENGTH      5
#define L_DEVICE_ID         5
#define L_DEVICE_PORT       2
#define L_FUNC_CODE_LENGTH  3
#define L_CRC_LENGTH        3
#define L_FRAME_END         3
#define L_FRAME_ID          5
#define L_FRAME_NUM         3

namespace Ui {
class BusMain;
}

class BusMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit BusMain(QWidget *parent = 0);
    ~BusMain();
    Ui::BusMain *ui;
    QList<MyThread*> threads;
    ReverseCamera *revcam;
    Home *hom;
    Camera *cam;
    player *mplay;
    route_selection *route_sel;
    running_route *run_route;
    PreRecorded *prerecord;
    FFmpegTask *ffmpeg;
    int page_announce_segments[10];
    int page_count;
private slots:
    void on_camera_clicked();
    void on_home_clicked();
    void on_pushButton_clicked();
    void enable_camera();
    void reverse_cam_initiate();
    void on_alarm_clicked();
    void on_play_clicked();
    void on_pass_info_clicked();
    void route_selected();
    void disable_route_selection();
    void enable_route_selection();
    void on_bus_clicked();
    void gps_filling();
    void process_n_fill_packet();
    void update_isr_data(QString gpsdata);
    void lost_path_recovery();
    void route_tasks();
    void display_and_announcement_packets(qint64 option);
    void crc_generate_modbus(unsigned char* rec_buff_address, unsigned int rec_buff_length);
    //unsigned char verify_crc_modbus(QString *rec_buff_address, unsigned int rec_buff_length);
    void openSerialPort();
    void closeSerialPort();
    void handleError(QSerialPort::SerialPortError error);
    void readData();
    void trial_data_send();
    void on_alert_clicked();
    void newConnection();
    void read_socket_data();
    bool openHidraw();
    void readyHIDRead();
    void handleMedia(int state_val);
    void back_to_running_route();
    void show_pre_recorded();
    void socket_check();
    void getter();
    void setter();

signals:
    void finished();
    void gps_valid_packet();
    void Route_Selection(qint64 option);
    void Stop_Arrival(qint64 option);
    void Stop_Departure(qint64 option);
    void Stop_Approaching(qint64 option);
    void trial_signal(qint64 option);
    void trial_datasend();
    void ack_received();
    void hid_detected();

private:
    QSerialPort *serial;
    QTcpServer *server;
    QTcpSocket *socket1;
    QSocketNotifier *m_read;
    QSocketNotifier *m_write;
    QMediaPlayer *mplayer;
    QMediaPlaylist *playlist;
    QTimer *timer;
};


#endif // BUSMAIN_H
