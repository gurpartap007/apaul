#include "home.h"
#include "camera.h"
#include "ui_busmain.h"
#include "busmain.h"
#include <QStackedWidget>
#include <QTimer>
#include "struct.h"
#include "math.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "hidapi.h"
/********************************************************************************************/
/*       MODIFIED  BUS PIS CODE ACCORDING TO 1366 X 768 RESOLUTION                  **/
/*       ALL WIDGETS ARE PUT IN LAYOUTS TO PROVIDE BETTER SIZE ADJUSTMENTS */

/*******************************************************************************************/

unsigned char prev_dup_crc_high,prev_dup_crc_low;
unsigned char crc_low_final,crc_high_final;
/*#######################################################################################
CRC LO0K UPS
#######################################################################################*/
unsigned char crc_high_lookup[] =
{
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40
};

unsigned char crc_low_lookup[] =
{
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
    0x40
};

QTextStream in;
int gps_filling_state = 0;
QFile file;
enum gpsdat
{
    HEADING,
    TIME_STAMP,
    VALIDITY,
    LATITUDE,
    NORTH_SOUTH,
    LONGITUDE,
    EAST_WEST,
    SPEED,
    TRUE_COURSE,
    DATE_STAMP,
    VARIATION_1,
    VARIATION_2,
    CHECKSUM
};
enum messagedat
{
    ROUTE,
    PATH_CODE,
    MESSAGE_TRIGGER,
    MESSAGE_CODE,
    STOP_CODE,
    STOP_REFERENCE,
    DEVICE_CODE
};
enum displaymessagedat
{
    ROUT,
    PATH_COD,
    STOP_COD,
    DEVICE_COD,
    MESSAGE_COD,
    PAGE,
    REPEAT_COUNT,
    PAGE_DURATION,
    SECTION_NO,
    X1,
    X2,
    Y1,
    Y2,
    DISPLAY_MODE,
    SCROLL_RATE,
    SCROLL_DIRECTION,
    FLASHING,
    FLASH_RATE,
    FONT,
    TEXT,
    TAGS,
    BITMAP_LENGTH,
    BITMAP,
    ALIGNMENT
};
enum ack_packet_structure
{
    FRAME_START,
    FRAME_LENGTH,
    DEVICE_ID,
    DEVICE_PORT,
    FUNC_CODE,
    FRAME_ID,
    FRAME_NUMBER,
    DATA,
    CRC,
    FRAME_END_ID
};
enum device_master_type
{
    DEVICE_C,
    DEVICE_TYPE,
    DEVICE_PARAMETER
};
enum announcement_dat
{
    ROU,
    PATH_C,
    STOP_C,
    DEVICE_CO,
    MESSAGE_C,
    PAG,
    PAG_DUR,
    SYNC_DEV,
    SEGMENT_DATA,
    SEMENT_SEQ
};

QString gps_file,file_data;
int gps_validity = 0;
QString date,tim,speed;
QStringList gps_data;
QString subString,dev_type;
QString querytext,querytextone;
QStringList table_data,table_data_one,table_data_two,received_data,bitmap_data;
extern QString path_code, route_no, destination_code, path_description, source_code, via_code, total_distance, number_of_stations,pre_recorded;
QString final_sending_data,temp_final_sending_data,recd_data,ack_unresponsive_final_data;
bool acknowledgement_unresponsive = 0,successful_ack = 0;
int stations_within_range = 0,tracked_station_no;
int distance_restriction = 200,no_of_lines,audio_repeat_count,temp_audio_repeat_count;
char buffer[34] = {0};

unsigned char rec_complete;
unsigned char stx_received;
unsigned int received_chars;
unsigned int field_counts;
unsigned int rx_length;
char port_read_data;
char bytes[100];

BusMain::BusMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BusMain)
{
    //CONSTRUCTOR
    ui->setupUi(this);
    QVBoxLayout outer_layout;
    //ui->statusBar->hide();
    QDesktopWidget screen2;
    connect(this, SIGNAL(gps_valid_packet()), this, SLOT(route_tasks()));
    connect(this, SIGNAL(Route_Selection(qint64)), this, SLOT(display_and_announcement_packets(qint64)));
    connect(this, SIGNAL(Stop_Arrival(qint64)), this, SLOT(display_and_announcement_packets(qint64)));
    connect(this, SIGNAL(Stop_Departure(qint64)), this, SLOT(display_and_announcement_packets(qint64)));
    connect(this, SIGNAL(Stop_Approaching(qint64)), this, SLOT(display_and_announcement_packets(qint64)));
    connect(this, SIGNAL(trial_signal(qint64)), this, SLOT(display_and_announcement_packets(qint64)));
    connect(this, SIGNAL(trial_datasend()), this, SLOT(trial_data_send()));

    //RESIZING CDC BUFFER
    //final_sending_data.resize(1000);
    temp_final_sending_data.resize(1000);
    temp_final_sending_data.fill(0x00);

    //socket = new SocketPort1;

    //revcam = new ReverseCamera;

    //HOME SCREEN
    hom = new Home(this);
    hom->setParent(this);
    connect(hom, SIGNAL(announcement_clicked()), this, SLOT(show_pre_recorded()));
    ui->alarm->setFixedSize(screen2.width()*1/10,(screen2.height()*1/4));
    ui->alert->setFixedSize(screen2.width()*1/10,(screen2.height()*1/4));
    ui->bus->setFixedSize(screen2.width()*1/10,(screen2.height()*1/4));
    ui->call->setFixedSize(screen2.width()*1/10,(screen2.height()*1/4));
    ui->camera->setFixedSize(screen2.width()*1/10,(screen2.height()*1/4));
    ui->data->setFixedSize(screen2.width()*1/10,(screen2.height()*1/4));
    ui->gps->setFixedSize(screen2.width()*1/10,(screen2.height()*1/4));
    ui->home->setFixedSize(screen2.width()*1/10,(screen2.height()*1/4));
    ui->pass_info->setFixedSize(screen2.width()*1/10,(screen2.height()*1/4));
    ui->play->setFixedSize(screen2.width()*1/10,(screen2.height()*1/4));
    ui->line->setMaximumSize(screen2.width(),13);
    ui->line->setGeometry(0,(screen2.height()*1/4)+5,screen2.width(),13);
    ui->stackedWidget->setGeometry(0,ui->alarm->height()+ui->line->height(),screen2.width(),screen2.height()-(ui->alarm->height()+ui->line->height()+ui->statusBar->height())-5);
    outer_layout.setSizeConstraint(QLayout::SetMinAndMaxSize);
    outer_layout.setParent(this->centralWidget());
    ui->line->setLayout(&outer_layout);
    ui->stackedWidget->setLayout(&outer_layout);
    // outer_layout.addLayout(ui->horizontalLayout);
    //  outer_layout.addLayout(ui->verticalLayout);

  //Q_ASSERT(outer_layout.count() % 2 == 1);  // USED TO CHECK TEST CONDITION.PRINTS CODE WHEN TEST CONDITION FAILS AND ABORT THE PROGRAM.
    //PRE RECORDED MESSAGE SCREEN
    prerecord = new PreRecorded;
    connect(prerecord, SIGNAL(back_running_route()), this, SLOT(back_to_running_route()));
    connect(prerecord, SIGNAL(dis_prr_packet(qint64)), this, SLOT(display_and_announcement_packets(qint64)));

    //ROUTE SELECTION SCREEN
    route_sel = new route_selection;
    connect(route_sel, SIGNAL(route_selected(qint64)), this, SLOT(route_selected()));
    connect(route_sel, SIGNAL(route_selected(qint64)), this, SLOT(display_and_announcement_packets(qint64)));

    //RUNNING ROUTE SCREEN
    run_route = new running_route;
    connect(run_route, SIGNAL(Journey_Start(qint64)), this, SLOT(disable_route_selection()));
    connect(run_route, SIGNAL(Journey_Start(qint64)), this, SLOT(display_and_announcement_packets(qint64)));
    connect(run_route, SIGNAL(Pre_Recorded_Display()), this, SLOT(show_pre_recorded()));
    connect(run_route, SIGNAL(route_ended()), this, SLOT(enable_route_selection()));
    connect(run_route, SIGNAL(dis_ann_packet(qint64)), this, SLOT(display_and_announcement_packets(qint64)));

    //serial = new SerialPort;
    //connect(serial, SIGNAL(initiate_reverse()), this, SLOT(reverse_cam_initiate()));
    //connect(serial, SIGNAL(Door_Close(qint64)), this, SLOT(display_packets(qint64)));
    //connect(serial, SIGNAL(Door_Open(qint64)), this, SLOT(display_packets(qint64)));
    //connect(serial, SIGNAL(Emergency(qint64)), this, SLOT(display_packets(qint64)));

    //gpsserial = new gps_serial;



    //SURVEILLANCE VIDEO SAVING

    //SURVEILLANCE SCREEN
   cam = new Camera;
    //QTimer::singleShot(5000, this, SLOT(delay_camera()));

    ffmpeg = new FFmpegTask;
    qDebug() << "INSIDE MAIN WINDOW "<< ffmpeg->global_video_location;

    //MEDIA PLAYER
   mplay = new player();
   mplay->player_video_location=ffmpeg->global_video_location;
    //ADDING SCREENS TO MAIN BUS WIDGET
    qDebug() << "geometry of stack widget" << ui->stackedWidget->geometry();
    ui->stackedWidget->addWidget(hom);
   ui->stackedWidget->addWidget(cam);
    ui->stackedWidget->addWidget(mplay);
    ui->stackedWidget->addWidget(route_sel);
    ui->stackedWidget->addWidget(run_route);
    //ui->stackedWidget->addWidget(revcam);
    ui->stackedWidget->addWidget(prerecord);

    ui->stackedWidget->setCurrentWidget(hom);
   //ui->camera->setEnabled(0);
    //QTimer::singleShot(1000, this, SLOT(enable_camera()));

    ui->bus->setEnabled(false);
    page_count = 0;
    //THREAD FOR GPS SIMULATION THROUGH FILE
    threads.append(new MyThread(1000, this->parent()));
    //THREAD FOR CHECKING CDC/HID STATE
    threads.append(new MyThread(1000, this->parent()));
    //THREAD FOR GETTING DATA ON HID
    threads.append(new MyThread(1000, this->parent()));

    //CONNECT EACH WIDGET TO CORRESPONDING THREAD
    connect(run_route, SIGNAL(gps_file_selected()), threads[0], SLOT(start()));
    connect(threads[0], SIGNAL(valueChanged(int)), this, SLOT(gps_filling()));
    connect(threads[1], SIGNAL(valueChanged(int)), this, SLOT(socket_check()));
    connect(this, SIGNAL(hid_detected()), threads[2], SLOT(start()));
    connect(threads[2], SIGNAL(valueChanged(int)), this, SLOT(getter()));

    //SERIAL PORT FOR CDC DATA EXCHANGE
    serial = new QSerialPort();
    threads[1]->start();
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    //  threads[0]->start();
    //TEMPORARY OBJECT TO SEND DATA THROUGH ANDROID
    server = new QTcpServer(this);
    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));
    if(!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }

    //TIMER
    timer = new QTimer;

    //MEDIA PLAYER AND PLAYLIST FOR AUDIO ANNOUNCEMENTS
    playlist = new QMediaPlaylist;
    mplayer = new QMediaPlayer;
    //    connect(playlist, SIGNAL(currentIndexChanged(int)), mplayer, SLOT(pause()));
    connect(playlist, SIGNAL(currentIndexChanged(int)), timer, SLOT(start()));
    connect(playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(handleMedia(int)));
    connect(timer, SIGNAL(timeout()), mplayer, SLOT(play()));
    mplayer->setPlaylist(playlist);

    sys_info.data.setting.data.cmd[0] = 'S';
    sys_info.data.setting.data.cmd[1] = 'E';
    sys_info.data.setting.data.cmd[2] = 'T';
}

BusMain::~BusMain()
{
    threads[0]->stop();
    threads[1]->stop();
    threads[2]->stop();
    closeSerialPort();
    //threads[1]->stop();


    delete cam;
    delete hom;
    //delete revcam;
    //delete socket;
     system("pkill -9 ffmpeg");
      delete ffmpeg;
    delete mplay;
    system("pkill -9 gst-launch");
       qDebug() << "Inside main Destructor";
    delete route_sel;
    delete run_route;
    delete prerecord;
    //delete serial;
    delete ui;
}

void BusMain::on_camera_clicked()
{
    ui->statusBar->showMessage("Surveillance");
    ui->stackedWidget->setCurrentWidget(cam);
}

void BusMain::on_home_clicked()
{
    ui->statusBar->showMessage("Home");
    ui->stackedWidget->setCurrentWidget(hom);
}

void BusMain::on_pushButton_clicked()
{
    //EXIT PROGRAM
    BusMain::close();
}

void BusMain::enable_camera()
{
    ui->camera->setEnabled(1);
    ui->statusBar->showMessage("Camera Activated");
}

void BusMain::reverse_cam_initiate()
{
    //ui->stackedWidget->setCurrentWidget(revcam);
}

void BusMain::on_alarm_clicked()
{
    //serial->write_reverse_data();
    //emit this->trial_signal(1);
    setter();
}

void BusMain::on_play_clicked()
{
    ui->statusBar->showMessage("Media Player");
    ui->stackedWidget->setCurrentWidget(mplay);
}

void BusMain::on_pass_info_clicked()
{
    emit this->Route_Selection(3);
    ui->statusBar->showMessage("Passenger Information System");
    ui->stackedWidget->setCurrentWidget(route_sel);
}

void BusMain::route_selected()
{
    route_path.status.bits.route_info_avail = 1;
    run_route->initialise_fields();
    prerecord->enable_back_button();
    ui->statusBar->showMessage("Route Selected");
    ui->stackedWidget->setCurrentWidget(run_route);
}

void BusMain::disable_route_selection()
{
    ui->pass_info->setEnabled(false);
    ui->bus->setEnabled(true);
}

void BusMain::enable_route_selection()
{
    ui->pass_info->setEnabled(true);
    ui->bus->setEnabled(false);
    ui->statusBar->showMessage("Passenger Information System");
    ui->stackedWidget->setCurrentWidget(route_sel);
}

void BusMain::on_bus_clicked()
{
    ui->statusBar->showMessage("Route Running");
    ui->stackedWidget->setCurrentWidget(run_route);
}

void BusMain::gps_filling()
{
    switch(gps_filling_state)
    {
    case 0:
    {
        //OPEN SIMULATION FILE
        file.setFileName(gps_file);
        if (file.exists())
        {
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            in.setDevice(&file);
            gps_filling_state++;
            gps.data.status.bits.onsimulation = 1;
        }
    }
        break;
    case 1:
        //READ LINE BY LINE FROM SIMULATION FILE
        if(!in.atEnd())
        {
            gps_validity = 0;
            file_data = in.readLine();
            update_isr_data(file_data);
            if(gps_validity)
                process_n_fill_packet();
        }
        else
            gps.data.status.bits.onsimulation = 0;
        break;
    }
}

void BusMain::process_n_fill_packet()
{
    gps.data.status.bits.to_be_processed = 0;
    gps.data.status.bits.isr_to_cpu = 1;
    gps.data.cpu = gps.data.isr;
    gps.data.status.bits.isr_to_cpu = 0;

    if( gps.data.status.bits.date_time)
    {
        //TIME CONVERSION
        tim = QString::number(gps.data.cpu.time.hrs) + ":" + QString::number(gps.data.cpu.time.min) + ":" + QString::number(gps.data.cpu.time.sec);
        memcpy( gps.data.time, tim.toStdString().c_str(), 8);
        //DATE CONVERSION
        date = QString::number(gps.data.cpu.date.day) + "/" + QString::number(gps.data.cpu.date.month) + "/20" + QString::number(gps.data.cpu.date.yrs);
        memcpy( gps.data.date, date.toStdString().c_str(), 10);

        gps.data.status.bits.date_time_processed = 1;
    }
    if( gps.data.status.bits.lat_long)
    {
        //LATITUDE,LONGITUDE,SPEED CONVERSION
        uword temp_lat_long1, temp_lat_long2;
        uinteger temp_speed;

        temp_lat_long1 = (uword)(gps.data.cpu.latit*10000);
        temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
        temp_lat_long2 += (temp_lat_long1%1000000);
        gps.data.cpu.latit = (float)temp_lat_long2;

        temp_lat_long1 = (uword)(gps.data.cpu.longit*10000);
        temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
        temp_lat_long2 += (temp_lat_long1%1000000);
        gps.data.cpu.longit = (float)temp_lat_long2;
        gps.data.status.bits.lat_long_processed = 1;
        route_path.status.bits.new_gps_data = 1;

        temp_speed = gps.data.cpu.speed / 100;
        speed = QString::number(temp_speed);
        memcpy( gps.data.speed, speed.toStdString().c_str(), 3);
        gps.data.speed[3] = 0;

        emit this->gps_valid_packet();
    }
}

void BusMain::update_isr_data(QString gpsdata)
{
    //SPLITTING OF SIMULATION PACKETS INTO VARIOUS STRUCTURE FIELDS
    gps_data = gpsdata.split(",");//, QString::SkipEmptyParts);

    gps.data.isr.latit = gps_data[LATITUDE].toFloat();
    gps.data.isr.longit = gps_data[LONGITUDE].toFloat();
    gps.data.isr.speed = gps_data[SPEED].toFloat();
    gps.data.isr.speed = (KNOTS_TO_KMS_FACTOR*gps.data.isr.speed*1000)/10;
    gps.data.isr.heading = gps_data[TRUE_COURSE].toFloat();
    gps.data.status.bits.lat_long = 1;

    subString = gps_data[TIME_STAMP].mid(0,2);
    gps.data.isr.time.hrs = subString.toInt();
    subString = gps_data[TIME_STAMP].mid(2,2);
    gps.data.isr.time.min = subString.toInt();
    subString = gps_data[TIME_STAMP].mid(4,2);
    gps.data.isr.time.sec = subString.toInt();

    subString = gps_data[DATE_STAMP].mid(0,2);
    gps.data.isr.date.day = subString.toInt();
    subString = gps_data[DATE_STAMP].mid(2,2);
    gps.data.isr.date.month = subString.toInt();
    subString = gps_data[DATE_STAMP].mid(4,2);
    gps.data.isr.date.yrs = subString.toInt();

    gps.data.status.bits.date_time = 1;

    gps_validity = 1;
}

void BusMain::lost_path_recovery()
{
    //LOST PATH RECOVERY
    //THIS STARTS AS SOON AS THE ROUTE IS SELECTED TO FIGURE OUT WHERE THE BUS IS IN THE WHOLE PATH
    //TILL THE BUS IS TRACKED WE TRACK DISTANCE OF EACH STATION FROM CURRENT GPS LOCATION AND SYSTEMATICALLY GO DOWN TILL WE COME TO ONE STATION
    //ONCE WE GET THE STATION WE FIGURE OUT IF WE ARE APPROACHING TOWARDS OR AWAY FROM THE STATION AND ASSISNG STOP NUMBERS ACCORDINGLY
    if(!route_path.status.bits.bus_tracked)
    {
        for(int i=0; i < route_path.Header.no_of_stns; i++)
        {
            route_path.Stops[i].info.gps_distance_from_prev_loc = route_path.Stops[i].info.gps_distance_from_curr_loc;
            route_path.Stops[i].info.gps_distance_from_curr_loc = _GET_DISTANCE(i);
            if((route_path.Stops[i].info.gps_distance_from_curr_loc * 1000) < distance_restriction)
            {
                stations_within_range++;
                tracked_station_no = i;
            }
        }
        if(stations_within_range > 1)
        {
            stations_within_range = 0;
            distance_restriction = distance_restriction - 50;
            if(!distance_restriction)
                distance_restriction = distance_restriction + 50;
        }
        else if(stations_within_range == 1)
        {
            qDebug() << "BUS HAS BEEN TRACKED";
            route_path.status.bits.bus_tracked = 1;
            for(int y = 0; y < (tracked_station_no-1); y++)
                run_route->skip_event();
            //APPROACHING TOWARDS STATION
            if(route_path.Stops[tracked_station_no].info.gps_distance_from_prev_loc > route_path.Stops[tracked_station_no].info.gps_distance_from_curr_loc)
            {
                if(tracked_station_no)
                    route_path.Curr_stop = tracked_station_no - 1;
                route_path.Next_stop = tracked_station_no;
                if(tracked_station_no - 1)
                    route_path.Prev_stop = tracked_station_no - 2;
                qDebug() << "GOING TOWARDS " << QString::fromLatin1((const char*)route_path.Stops[route_path.Next_stop].info.station_name);
            }
            //GOING AWAY FROM STATION
            else if(route_path.Stops[tracked_station_no].info.gps_distance_from_prev_loc < route_path.Stops[tracked_station_no].info.gps_distance_from_curr_loc)
            {
                run_route->skip_event();
                if(tracked_station_no < (route_path.Header.no_of_stns - 1))
                    route_path.Next_stop = tracked_station_no + 1;
                route_path.Curr_stop = tracked_station_no;
                if(tracked_station_no - 1)
                    route_path.Prev_stop = tracked_station_no - 1;
                qDebug() << "LEFT FROM " << QString::fromLatin1((const char*)route_path.Stops[route_path.Next_stop - 1].info.station_name);
            }
        }
    }
}

void BusMain::route_tasks()
{
    //ROUTE TASKS
    //LOST PATH RECOVERY TILL THE BUS IS TRACKED
    //ONCE THE BUS IS TRACKED WE CALCULATE THE DISTANCE OF NEXT STATION FROM CURRENT GPS LOCATION
    //BASED ON THESE DISTANCES WE FIGURE OUT WHETHER WE ARE APPROACHING, ENTERING PERIPHERY OR LEAVING PERIPHERY OF A STATION
    if(route_path.status.bits.route_info_avail && (!route_path.status.bits.bus_tracked))
    {
        route_path.status.bits.bus_tracked = 0;
        lost_path_recovery();
    }

    if(route_path.status.bits.bus_tracked)
    {
        //CALCULATE DISTANCE OF STOP LAT/LONG FROM CURRENT GPS LAT/LONG
        route_path.Stops[route_path.Next_stop].info.gps_distance_from_prev_loc = route_path.Stops[route_path.Next_stop].info.gps_distance_from_curr_loc;
        route_path.Stops[route_path.Next_stop].info.gps_distance_from_curr_loc = _GET_DISTANCE(route_path.Next_stop);
        double curr_distance = 0;
        curr_distance = route_path.Stops[route_path.Next_stop].info.gps_distance_from_curr_loc * 1000;
        curr_distance = (((float)mul_factor[route_path.Next_stop - 1] * curr_distance) / 1000) + curr_distance;
#ifdef ACT_DIST
        route_path.Stops[route_path.Next_stop].info.distance_from_curr_loc = (uinteger)curr_distance;
#else
        route_path.Stops[route_path.Next_stop].info.distance_from_curr_loc = route_path.Stops[route_path.Next_stop].info.gps_distance_from_curr_loc;
#endif
        //CHECK ARRIVAL,DEPARTURE,APPROACHING BASED ON PRESENT DISTANCES
        route_path.status.bits.station_arrival = 0;
        route_path.status.bits.station_departure = 0;
        route_path.status.bits.station_approaching = 0;
        if(((route_path.Stops[route_path.Next_stop].info.gps_distance_from_curr_loc*1000) <= route_path.Stops[route_path.Next_stop].info.approaching_peri) && ((route_path.Stops[route_path.Next_stop].info.gps_distance_from_prev_loc*1000) > route_path.Stops[route_path.Next_stop].info.approaching_peri) && ((route_path.Stops[route_path.Next_stop].info.distance_frm_src - route_path.Stops[route_path.Curr_stop].info.distance_frm_src) > 2))
        {
            route_path.status.bits.inside_peri = 0;
            route_path.status.bits.outside_peri = 0;
            route_path.status.bits.approaching_peri = 1;
            route_path.status.bits.station_approaching = 1;
            qDebug() << "WITHIN 1 KM OF " << QString::fromLatin1((const char*)route_path.Stops[route_path.Next_stop].info.station_name);
            emit this->Stop_Approaching(20);
        }
        else if(((route_path.Stops[route_path.Next_stop].info.gps_distance_from_curr_loc*1000) <= route_path.Stops[route_path.Next_stop].info.entry_peri) && ((route_path.Stops[route_path.Next_stop].info.gps_distance_from_prev_loc*1000) > (route_path.Stops[route_path.Next_stop].info.gps_distance_from_curr_loc*1000)) && !(route_path.status.bits.inside_peri))
        {
            route_path.status.bits.inside_peri = 1;
            route_path.status.bits.outside_peri = 0;
            route_path.status.bits.approaching_peri = 0;
            route_path.status.bits.station_arrival = 1;
            qDebug() << "ENTERED ENTRY PERIPHERY OF " << QString::fromLatin1((const char*)route_path.Stops[route_path.Next_stop].info.station_name);
            emit this->Stop_Arrival(20);
        }
        else if(((route_path.Stops[route_path.Next_stop].info.gps_distance_from_curr_loc*1000) > route_path.Stops[route_path.Next_stop].info.exit_peri) && ((route_path.Stops[route_path.Next_stop].info.gps_distance_from_prev_loc*1000) < (route_path.Stops[route_path.Next_stop].info.gps_distance_from_curr_loc*1000)) && !(route_path.status.bits.outside_peri) && (route_path.status.bits.inside_peri))
        {
            route_path.status.bits.inside_peri = 0;
            route_path.status.bits.outside_peri = 1;
            route_path.status.bits.approaching_peri = 0;
            route_path.status.bits.station_departure = 1;
            qDebug() << "LEFT EXIT PERIPHERY OF " << QString::fromLatin1((const char*)route_path.Stops[route_path.Next_stop].info.station_name);
            if(route_path.Next_stop!=0)
                run_route->skip_event();
            else
            {
                route_path.Curr_stop++;
                route_path.Prev_stop++;
                route_path.Next_stop++;
            }
            emit this->Stop_Departure(20);
        }
        /*********************************************************************************************************************************************************/
    }
}

void BusMain::display_and_announcement_packets(qint64 option)
{
    final_sending_data.clear();
    temp_final_sending_data.clear();
    ack_unresponsive_final_data.clear();
    querytext.clear();
    //   timer->stop();
    //  playlist->clear();
    //   mplayer->stop();

    //FIGURE OUT OPTION BASED ON TRIGGER
    switch(option)
    {
    case 20:
        mplayer->playlist()->clear();
        //querytext = "select * from message_configuration_table where Message_trigger = 'Next Station' and Path_code = '" + path_code + "' and Stop_code = '" + QString::fromLatin1((const char*)route_path.Stops[route_path.Next_stop].info.Code) + "'";// order by Device_code desc";
        querytext = "select * from message_configuration_table where Message_trigger = 'Entry Periphery' and Path_code = '" + path_code + "' and Stop_code = '" + QString::fromLatin1((const char*)route_path.Stops[route_path.Next_stop].info.Code) + "' order by Device_code desc";
        //querytext = "select * from message_configuration_table where Message_trigger = 'Door open' and Path_code = 'P001' and Stop_code = 'NDLS'";
        break;

    case 25:
        querytext = "select * from message_configuration_table where Message_trigger = 'Pre Record' and Stop_code = '" + pre_recorded + "'";
        //querytext = "select * from message_configuration_table where Message_trigger = 'Door open' and Path_code = 'P001' and Stop_code = 'NDLS'";
        break;

    case 30:
        //querytext = "select * from message_configuration_table where Message_trigger = 'Route Selected' and Path_code = '" + path_code + "' and Route = '" + route_no + "'";
        querytext = "select * from message_configuration_table where Message_trigger = 'On Route Selection' and Path_code = '" + path_code + "' and Route = '" + route_no + "'";
        //querytext = "select * from message_configuration_table where Message_trigger = 'Door open' and Path_code = 'P001' and Stop_code = 'NDLS'";
        break;

    default:
        break;
    }

    //PICK OUT ALL ROWS OF QUERY
    QSqlQuery query(querytext);
    while(query.next()){
        final_sending_data.clear();
        temp_final_sending_data.clear();
        ack_unresponsive_final_data.clear();
        table_data.clear();
        QSqlRecord record = query.record();
        for(int i=0; i < record.count(); i++)
            table_data << record.value(i).toString();

        //FIND WHICH DEVICE THE INFORMATION IS MEANT FOR
        QSqlQuery query1("select device_type from device_master_table where device_code = '" + table_data[DEVICE_CODE] + "' order by device_code desc");
        query1.first();
        dev_type = query1.value(0).toString();

        if(dev_type == "AAU")
        {
            //AUDIO ADDITION
            page_announce_segments[0]  = 0;
            page_announce_segments[1]  = 0;
            page_announce_segments[2]  = 0;
            page_announce_segments[3]  = 0;
            page_announce_segments[4]  = 0;
            querytextone = "select * from Annuciation_device_type_table where Stop_code = '" + table_data[STOP_CODE] + "' and Message_code = '" + table_data[MESSAGE_CODE]  + "' and Route = '" + route_no + "' order by Page ASC";
            QSqlQuery query3(querytextone);
            while(query3.next())
            {
                table_data_two.clear();
                QSqlRecord record_one = query3.record();
                for(int i=0; i < record_one.count(); i++)
                    table_data_two << record_one.value(i).toString();
                QString v_file ("/home/apaul/BUS_PIS_PROJECT/Resources/database/somnath/play_files/");
                v_file += table_data_two[SEGMENT_DATA];
                playlist->addMedia(QUrl::fromLocalFile(v_file));
                page_announce_segments[table_data_two[5].toInt() - 1] += 1;
            }
        }
        if(dev_type == "Display")
        {
            QSqlQuery query2("select * from Display_device_type_table where Stop_code = '" + table_data[STOP_CODE] + "' and Device_code = '" + table_data[DEVICE_CODE] + "' and Message_code = '" + table_data[MESSAGE_CODE] + "' and Route = '" + route_no + "'");
            //QSqlQuery query2("select * from Display_device_type_table where Stop_code = '" + table_data[STOP_CODE] + "' and Device_code = '" + table_data[DEVICE_CODE] + "' and Message_code = '10'");
            int pageCount = 0,tempCount,lineCount,frame_num = 1, SectionCount, tempSectionCount;
            bool ok,data_filling = 0;unsigned short temp_char;unsigned int temp_int;
            bool once_entered = 0;
            while(query2.next()){
                data_filling = 1;
                table_data_one.clear();
                QSqlRecord record1 = query2.record();
                for(int j=0; j < record1.count(); j++)
                    table_data_one << record1.value(j).toString();

                tempCount = pageCount;
                QString page_number = table_data_one[PAGE];
                //page_number.remove(0,5)
                pageCount = page_number.toInt();

                audio_repeat_count = table_data_one[REPEAT_COUNT].toInt();
                temp_audio_repeat_count = audio_repeat_count;

                //AUDIO ADDITION
                page_announce_segments[table_data_one[PAGE].toInt() - 1]  = 0;
                while(temp_audio_repeat_count > 0)
                {
                    querytextone = "select * from Annuciation_device_type_table where Stop_code = '" + table_data[STOP_CODE] + "' and Message_code = '" + table_data[MESSAGE_CODE]  + "' and Page = '" + table_data_one[PAGE] + "'";
                    QSqlQuery query3(querytextone);
                    while(query3.next()){
                        table_data_two.clear();
                        QSqlRecord record_one = query3.record();
                        for(int i=0; i < record_one.count(); i++)
                            table_data_two << record_one.value(i).toString();
                        QString v_file ("/home/apaul/BUS_PIS_PROJECT/Resources/database/somnath/play_files/");
                        v_file += table_data_two[SEGMENT_DATA];
                        playlist->addMedia(QUrl::fromLocalFile(v_file));
                        page_announce_segments[table_data_one[PAGE].toInt() - 1] += 1;
                    }
                    temp_audio_repeat_count--;
                }

                tempSectionCount = SectionCount;
                SectionCount = table_data_one[SECTION_NO].toInt();

                if(pageCount > tempCount)   //For Page Change
                {
                    if(once_entered)
                    {
                        for(int x=0; x < (6 - tempSectionCount); x++)
                        {
                            for(int y = 0; y < 12; y++)
                                final_sending_data = final_sending_data + QChar::Null;
                        }
                    }
                    once_entered = 1;

                    final_sending_data = final_sending_data + table_data_one[PAGE_DURATION] + ",";
                    temp_char = table_data_one[PAGE_DURATION].toInt();
                    final_sending_data = final_sending_data + QChar(temp_char);
                    if(SectionCount > 1)   //For initial empty fields in a page
                    {
                        for(int x=0; x < (SectionCount - 1); x++)
                        {
                            for(int y = 0; y < 12; y++)
                                final_sending_data = final_sending_data + QChar::Null;
                        }
                    }

                }

                if((pageCount == tempCount) && ((SectionCount - tempSectionCount) > 1))     //If same page and random sections
                {
                    for(int x=tempSectionCount; x < (SectionCount - 1); x++)
                    {
                        for(int y = 0; y < 12; y++)
                            final_sending_data = final_sending_data + QChar::Null;
                    }
                }

                //Properties Filling
                //X1
                temp_char = table_data_one[X1].toInt();
                final_sending_data = final_sending_data + QChar(temp_char);

                //X2
                temp_char = table_data_one[X2].toInt();
                final_sending_data = final_sending_data + QChar(temp_char);

                //Y1
                temp_char = table_data_one[Y1].toInt();
                final_sending_data = final_sending_data + QChar(temp_char);

                //Y2
                temp_char = table_data_one[Y2].toInt();
                final_sending_data = final_sending_data + QChar(temp_char);

                //DISPLAY EFFECT
                temp_char = table_data_one[DISPLAY_MODE].toInt();
                final_sending_data = final_sending_data + QChar(temp_char);

                //SCROLL_RATE
                temp_char = table_data_one[SCROLL_RATE].toInt();
                final_sending_data = final_sending_data + QChar(temp_char);

                //SCROLL_DIR
                temp_char = table_data_one[SCROLL_DIRECTION].toInt();
                final_sending_data = final_sending_data + QChar(temp_char);

                //FLASHING
                if(table_data_one[FLASHING] == "Disable")
                    table_data_one[FLASHING] = "0";
                temp_char = table_data_one[FLASHING].toInt();
                temp_char = 0;
                final_sending_data = final_sending_data + QChar(temp_char);

                //FLASH_RATE
                temp_char = table_data_one[FLASH_RATE].toInt();
                final_sending_data = final_sending_data + QChar(temp_char);


                //ALIGNMENT
                if(table_data_one[ALIGNMENT] == "R")
                    table_data_one[ALIGNMENT] = "1";
                else if(table_data_one[ALIGNMENT] == "L")
                    table_data_one[ALIGNMENT] = "2";
                else
                    table_data_one[ALIGNMENT] = "3";
                temp_char = table_data_one[ALIGNMENT].toInt();
                final_sending_data = final_sending_data + QChar(temp_char);


                //BITMAP LENGTH
                temp_int = table_data_one[BITMAP_LENGTH].toUInt();

                temp_char = ((temp_int) & 0xFF);
                final_sending_data = final_sending_data + QChar(temp_char);
                temp_char = ((temp_int >> 8) & 0xFF);
                final_sending_data = final_sending_data + QChar(temp_char);

                //BITMAP PROCESSING
                bitmap_data = table_data_one[BITMAP].split(",");
                for(int x = 0; x < (bitmap_data.size() - 1); x++)
                {
                    temp_char = bitmap_data.at(x).toInt(&ok,16);
                    final_sending_data = final_sending_data + QChar(temp_char);
                }
            }

            //If sections are leftover
            /*if((pageCount > tempCount) && SectionCount == 1)
            {
                for(int x=0; x < 5; x++)
                {
                    for(int y = 0; y < 11; y++)
                        final_sending_data = final_sending_data + QChar::Null;
                }
            }
            for(int x=0; x < (6 - SectionCount); x++)
            {
                for(int y = 0; y < 12; y++)
                    final_sending_data = final_sending_data + QChar::Null;
            }*/

            if(data_filling)
            {
                //Total data processing
                data_filling = 0;
                final_sending_data.prepend(QChar(audio_repeat_count));
                final_sending_data.prepend(QChar(pageCount));
                lineCount = final_sending_data.size() / 891;
                no_of_lines = lineCount;
                if(lineCount > 0)
                {
                    lineCount++;
                    no_of_lines = lineCount;
                    int ack_unresponsive_count = 0;
                    while(lineCount > 0)
                    {
                        ack_unresponsive_final_data = final_sending_data;
                        temp_final_sending_data = final_sending_data;
                        temp_final_sending_data.remove(891,(temp_final_sending_data.size() - 891));
                        final_sending_data.remove(0,891);

                        int frame_length = L_FRAME_START + L_FRAME_LENGTH + L_DEVICE_ID + L_DEVICE_PORT + L_FUNC_CODE_LENGTH + L_FRAME_ID + L_FRAME_NUM + temp_final_sending_data.size() + L_CRC_LENGTH + L_FRAME_END;
                        QString frm_len;
                        if(frame_length < 100)
                            frm_len = "00" + QString::number(frame_length) + ",";
                        else
                            frm_len = "0" + QString::number(frame_length) + ",";

                        QString frm_num = "0" + QString::number(frame_num) + ",";

                        if(lineCount == 1)
                            frm_num = "EF,";

                        //temp_final_sending_data.prepend("STX," + frm_len + table_data_one[DEVICE_COD] + "," + "1," + "D0," + "0001," + frm_num);
                        temp_final_sending_data.prepend("STX," + frm_len + table_data_one[DEVICE_COD] + ",0," + "D0," + "0001," + frm_num);

                        QByteArray temporary;
                        temporary.clear();
                        temporary.append(temp_final_sending_data.toLatin1());

                        //qDebug() << temp_final_sending_data.size();
                        //qDebug() << temporary.size();

                        crc_generate_modbus((unsigned char*)temporary.toStdString().c_str(),temporary.size());

                        temporary.append(crc_low_final);
                        temporary.append(crc_high_final);
                        temporary.append(",ETX");

                        //qDebug() << temporary;
                        //qDebug() << temporary.size();
                        //QTimer::singleShot(1500,mplayer,SLOT(play()));
                        if(serial->isOpen())
                        {
                            //SEND DATA
                            qint64 writtensize = serial->write(temporary);
                            qDebug() << writtensize;
                            bool ack_wait = serial->waitForBytesWritten(100);

                            if(ack_wait)
                            {
                                /* Create the QEventLoop */
                                qDebug() << "Waiting for ack";
                                //QEventLoop pause;
                                //connect(this, SIGNAL(ack_received()), &pause, SLOT(quit()));
                                this->readData();
                                serial->waitForReadyRead(20);
                                //QTimer::singleShot(2000, &pause, SLOT(quit()));
                                //pause.exec();
                            }
                            if(!successful_ack)
                            {
                                final_sending_data = ack_unresponsive_final_data;
                                ack_unresponsive_count++;
                                if(ack_unresponsive_count == 3)
                                {
                                    acknowledgement_unresponsive = 1;
                               /*     if(table_data_one[DEVICE_COD] == "D009")
                                    {
                                        QEventLoop pause;
                                        mplayer->play();                    //to be done after sending data to displays
                                        timer->setInterval((10000));        //to be added page duration here
                                        pause.exec();                       //to be used for announcement events triggers
                                    }*/
                                    //       handleMedia(-1);
                                    break;
                                }
                                continue;
                            }
                            ack_unresponsive_count = 0;
                            successful_ack =  0;
                            frame_num++;
                            lineCount--;
                            no_of_lines = lineCount;
                        }
                        else if(table_data_one[DEVICE_COD] == "D009")
                        {
                            QEventLoop pause;
                            mplayer->play();                    //to be done after sending data to displays
                            timer->setInterval((4000));        //to be added page duration here
                            pause.exec();                       //to be used for announcement events triggers
                            frame_num++;
                            lineCount--;
                            no_of_lines = lineCount;
                        }
                        else
                        {
                            frame_num++;
                            lineCount--;
                            no_of_lines = lineCount;
                        }
                    }
                }
                else
                {
                    int ack_unresponsive_count = 0;
                    int frame_length = L_FRAME_START + L_FRAME_LENGTH + L_DEVICE_ID + L_DEVICE_PORT + L_FUNC_CODE_LENGTH + L_FRAME_ID + L_FRAME_NUM + final_sending_data.size() + L_CRC_LENGTH + L_FRAME_END;
                    QString frm_len;
                    if(frame_length < 100)
                        frm_len = "00" + QString::number(frame_length) + ",";
                    else
                        frm_len = "0" + QString::number(frame_length) + ",";

                    QString frm_num = "0" + QString::number(frame_num) + ",";
                    frm_num = "EF,";

                    //final_sending_data.prepend("STX," + frm_len + table_data_one[DEVICE_COD] + "," + "1," + "D0," + "0001," + frm_num);
                    final_sending_data.prepend("STX," + frm_len + table_data_one[DEVICE_COD] + ",0," + "D0," + "0001," + frm_num);

                    QByteArray temporary;
                    temporary.clear();
                    temporary.append(final_sending_data.toLatin1());

                    crc_generate_modbus((unsigned char*)temporary.toStdString().c_str(),temporary.size());

                    temporary.append(crc_low_final);
                    temporary.append(crc_high_final);
                    temporary.append(",ETX");

                    //   qDebug() << temporary.size();
                    //qDebug() << temporary.size() << temporary;
                    //QTimer::singleShot(1500,mplayer,SLOT(play()));
                    page_count = 0;
                    if(serial->isOpen())
                    {
                        //SEND DATA
                        //qDebug() << temporary.size() << temporary.data()[temporary.size()];
                        //QTimer::singleShot(3000,mplayer,SLOT(play()));
                        while(!successful_ack)
                        {
                            qint64 writtensize = serial->write(temporary);
                            qDebug() << writtensize;
                            bool ack_wait = serial->waitForBytesWritten(100);
                            if(ack_wait)
                            {
                                qDebug() << "Waiting for ack";
                                /* Create the QEventLoop */
                                // QEventLoop pause;
                                // connect(this, SIGNAL(ack_received()), &pause, SLOT(quit()));
                                this->readData();
                                serial->waitForReadyRead(20);
                                //QTimer::singleShot(2000, &pause, SLOT(quit()));
                                // pause.exec();
                            }
                            if(!successful_ack)
                            {
                                ack_unresponsive_count++;
                                if(ack_unresponsive_count == 3)
                                {
                                    acknowledgement_unresponsive = 1;
                                    if(table_data_one[DEVICE_COD] == "D009")
                                    {
                                        QEventLoop pause;
                                        mplayer->play();                    //to be done after sending data to displays
                                        timer->setInterval((4000));        //to be added page duration here
                                        pause.exec();                       //to be used for announcement events triggers
                                    }
                                    //handleMedia(-1);
                                    break;
                                }
                                continue;
                            }
                        }
                        //mplayer->play();
                        ack_unresponsive_count = 0;
                        successful_ack =  0;
                    }
                    else if(table_data_one[DEVICE_COD] == "D009")
                    {
                        QEventLoop pause;
                        mplayer->play();                    //to be done after sending data to displays
                        timer->setInterval((4000));        //to be added page duration here
                        pause.exec();                       //to be used for announcement events triggers
                    }
                }
                //full_packet_sent = 1;
            }
        }

        //  else if(dev_type == "AAU")
        //  {
        /*while(audio_repeat_count > 0)
            {
                querytextone = "select * from Annuciation_device_type_table where Stop_code = '" + table_data[STOP_CODE] + "' and Message_code = '" + table_data[MESSAGE_CODE]  + "'";
                QSqlQuery query2(querytextone);
                //QSqlQuery query2("select * from Annuciation_device_type_table where Stop_code = '" + table_data[STOP_CODE] + "' and Message_code = '10'");
                while(query2.next()){
                        table_data_two.clear();
                        QSqlRecord record_one = query2.record();
                        for(int i=0; i < record_one.count(); i++)
                            table_data_two << record_one.value(i).toString();

                         playlist->addMedia(QUrl::fromLocalFile(table_data_two[SEGMENT_DATA]));
                }
                audio_repeat_count--;
            }*/
        //qDebug() << "Announcement Done";
        //  }
    }
}

void BusMain::crc_generate_modbus(unsigned char* rec_buff_address, unsigned int rec_buff_length)
{
    unsigned char crc_high = 0xFF;
    unsigned char crc_low = 0xFF;
    unsigned char crc_index;

    while(rec_buff_length--)
    {
        crc_index = crc_low ^ *rec_buff_address++;
        crc_low = crc_high ^ crc_high_lookup[crc_index];
        crc_high = crc_low_lookup[crc_index];
    }
    crc_low_final = crc_low;
    crc_high_final = crc_high;
}

//unsigned char BusMain::verify_crc_modbus(QString *rec_buff_address, unsigned int rec_buff_length)
//{
/*unsigned char dup_crc_low,dup_crc_high;

    //dup_crc_high = *(rec_buff_address + rec_buff_length);
    //dup_crc_low = *(rec_buff_address + rec_buff_length + 1);
    crc_generate_modbus(rec_buff_address, rec_buff_length);
    if((dup_crc_high == *(rec_buff_address + rec_buff_length)) && (dup_crc_low == *(rec_buff_address + rec_buff_length + 1)))
    {
        prev_dup_crc_high = dup_crc_high;
        prev_dup_crc_low = dup_crc_low;
        return (1);
    }
    else
    {
        prev_dup_crc_high = dup_crc_high;
        prev_dup_crc_low = dup_crc_low;
        return (0);
    }*/
//}

void BusMain::openSerialPort()
{
    QList<QSerialPortInfo> com_ports = QSerialPortInfo::availablePorts();
    QSerialPortInfo port;

    foreach(port, com_ports)
    {
        serial->setPortName(port.portName());
        serial->setBaudRate(QSerialPort::Baud57600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        if (serial->open(QIODevice::ReadWrite)) {
            qDebug() << "Connected to " << port.portName();
            openHidraw();
        } else {
            qDebug() << "Not Connected to " << port.portName();
        }
    }
}

void BusMain::closeSerialPort()
{
    if (serial->isOpen())
    {
        serial->close();
        m_read->deleteLater();
        m_write->deleteLater();
        qDebug() << "HID Disconnected";
    }
}

void BusMain::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        //QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        qDebug() << "Serial Port Disconnected";
        closeSerialPort();
    }
}

void BusMain::readData()
{
    QByteArray bytes_received = serial->readAll();
    recd_data = QString(bytes_received);
    if(!recd_data.isEmpty())
    {
        received_data = recd_data.split(",");
        if(received_data[DEVICE_ID] == table_data_one[DEVICE_COD])
        {
            successful_ack = 1;
            qDebug() << "Display Responded";
            Sleeper::msleep(100);
            if(no_of_lines <= 1 && received_data[DEVICE_ID]  == "D009")
            {
                QTimer::singleShot(1500,mplayer,SLOT(play()));
                timer->setInterval((table_data_one[PAGE_DURATION].toInt() * 1000));
            }
            emit this->ack_received();
        }
    }
}

void BusMain::trial_data_send()
{
    //serial->write("A");
    //emit this->trial_datasend();
}

float get_distance(float x1, float y1, float x2, float y2)
{
    float temp_distance;
    temp_distance = (x1 - x2)*(x1 - x2)+(y1 - y2)*(y1 - y2);
    temp_distance = sqrt(temp_distance);
    temp_distance = temp_distance * 176 / 945 / 1000;
    return(temp_distance);
}

void BusMain::on_alert_clicked()
{
    close();
    //emit this->trial_datasend();
    // setter();
}

void BusMain::newConnection()
{
    // need to grab the socket
    socket1 = server->nextPendingConnection();
    connect(socket1, SIGNAL(readyRead()), this, SLOT(read_socket_data()));
}

void BusMain::read_socket_data()
{
    QString data_recevd = socket1->readAll();
    if(data_recevd == "two")
        emit this->trial_signal(1);
}

bool BusMain::openHidraw()
{
    // Enumerate and print the HID devices on the system
    struct hid_device_info *devs, *cur_dev;

    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    while (cur_dev) {
        qDebug() << cur_dev->vendor_id << cur_dev->product_id << cur_dev->path;
        if(cur_dev->vendor_id == 1240 && cur_dev->product_id == 87)
        {
            int fd = open(cur_dev->path,O_NONBLOCK | O_RDWR);
            if(fd <= 0)
            {
                qDebug()<<"[WARN]rcHIDHandler::open-> Cant open!";
                return false;
            }
            qDebug() << fd << ": HID Connected";
            m_read = new QSocketNotifier(fd, QSocketNotifier::Read);
            m_read->setEnabled(true);
            connect(m_read, SIGNAL(activated(int)), this, SLOT(readyHIDRead()));

            m_write = new QSocketNotifier(fd, QSocketNotifier::Write);
            m_write->setEnabled(true);
            emit this->hid_detected();
            break;
        }
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

    return true;
}

void BusMain::readyHIDRead()
{
    read(m_read->socket(),&buffer,34);
    uword temp_lat_long1, temp_lat_long2;
    if(buffer[0] == 'G' && buffer[1] == 'E' && buffer[2] == 'T')
    {
        sys_info.data.pheri_info.data.cmd[0] = buffer[0];
        sys_info.data.pheri_info.data.cmd[1] = buffer[1];
        sys_info.data.pheri_info.data.cmd[2] = buffer[2];
        sys_info.data.pheri_info.data.IR_key = buffer[3];
        sys_info.data.pheri_info.data.keypad_key = buffer[4];
        sys_info.data.pheri_info.data.odometer = ((buffer[8]<<24) & 0xff000000) | ((buffer[7]<<16) & 0x00ff0000) | ((buffer[6]<<8) & 0x0000ff00) | (buffer[5] & 0x000000ff);
        sys_info.data.pheri_info.data.device_input.data.input_1 = buffer[9];
        sys_info.data.pheri_info.data.device_input.data.input_2 = buffer[10];
        sys_info.data.pheri_info.data.device_input.data.input_3 = buffer[11];
        sys_info.data.pheri_info.data.device_input.data.input_4 = buffer[12];
        sys_info.data.pheri_info.data.date.data.day = buffer[13];
        sys_info.data.pheri_info.data.date.data.month = buffer[14];
        sys_info.data.pheri_info.data.date.data.yrs = buffer[15];
        sys_info.data.pheri_info.data.time.data.hrs = buffer[17];
        sys_info.data.pheri_info.data.time.data.min = buffer[18];
        sys_info.data.pheri_info.data.time.data.sec = buffer[19];
        sys_info.data.pheri_info.data.latitude = ((buffer[24]<<24) & 0xff000000) | ((buffer[23]<<16) & 0x00ff0000) | ((buffer[22]<<8) & 0x0000ff00) | (buffer[21] & 0x000000ff);
        temp_lat_long1 = (uword)sys_info.data.pheri_info.data.latitude;
        temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
        temp_lat_long2 += (temp_lat_long1%1000000);
        sys_info.data.pheri_info.data.latitude = (float)temp_lat_long2;

        sys_info.data.pheri_info.data.longitude = ((buffer[28]<<24) & 0xff000000) | ((buffer[27]<<16) & 0x00ff0000) | ((buffer[26]<<8) & 0x0000ff00) | (buffer[25] & 0x000000ff);
        temp_lat_long1 = (uword)sys_info.data.pheri_info.data.longitude;
        temp_lat_long2 = (temp_lat_long1/1000000)*60*10000;
        temp_lat_long2 += (temp_lat_long1%1000000);
        sys_info.data.pheri_info.data.longitude = (float)temp_lat_long2;

        sys_info.data.pheri_info.data.heading[0] = buffer[29];
        sys_info.data.pheri_info.data.heading[1] = buffer[30];
        sys_info.data.pheri_info.data.heading[2] = buffer[31];
        sys_info.data.pheri_info.data.heading[3] = buffer[32];
        sys_info.data.pheri_info.data.heading[4] = buffer[33];

        if(sys_info.data.pheri_info.data.heading[0] == 1)
            system("shutdown -P now");

        if(!gps.data.status.bits.onsimulation)
        {
            //time conversion
            tim = QString::number(sys_info.data.pheri_info.data.time.data.hrs) + ":" + QString::number(sys_info.data.pheri_info.data.time.data.min) + ":" + QString::number(sys_info.data.pheri_info.data.time.data.sec);
            memcpy( gps.data.time, tim.toStdString().c_str(), 8);
            //date conversion
            date = QString::number(sys_info.data.pheri_info.data.date.data.day) + "/" + QString::number(sys_info.data.pheri_info.data.date.data.month) + "/20" + QString::number(sys_info.data.pheri_info.data.date.data.yrs);
            memcpy( gps.data.date, date.toStdString().c_str(), 10);

            gps.data.status.bits.date_time_processed = 1;

            gps.data.cpu.latit = (float)sys_info.data.pheri_info.data.latitude;

            gps.data.cpu.longit = (float)sys_info.data.pheri_info.data.longitude;

            gps.data.status.bits.lat_long_processed = 1;

            route_path.status.bits.new_gps_data = 1;

            /*temp_speed = gps.data.cpu.speed / 100;
            speed = QString::number(temp_speed);
            memcpy( gps.data.speed, speed.toStdString().c_str(), 3);
            gps.data.speed[3] = 0;*/

            emit this->gps_valid_packet();
        }
    }
    else if(sys_info.data.pheri_info.data.cmd[0] == 'S' && sys_info.data.pheri_info.data.cmd[1] == 'E' && sys_info.data.pheri_info.data.cmd[2] == 'T')
    {
        qDebug() << "SET Received";
    }
}

void BusMain::handleMedia(int state_val)
{
    //qDebug() << playlist->currentIndex();
    if(playlist->currentIndex() == page_announce_segments[page_count])
    {
        page_count++;
        mplayer->pause();
    }
    else if(state_val < 0)
    {
        timer->stop();
        playlist->clear();
        mplayer->stop();
    }
}

void BusMain::back_to_running_route()
{
    ui->stackedWidget->setCurrentWidget(run_route);
}

void BusMain::show_pre_recorded()
{
    ui->stackedWidget->setCurrentWidget(prerecord);
}

void BusMain::socket_check()
{
    if (!serial->isOpen())
        openSerialPort();
}

void BusMain::setter()
{
    if(serial->isOpen())
        write(m_write->socket(),sys_info.data.setting.bytes,11);
}

void BusMain::delay_camera()
{
    cam = new Camera;
}

void BusMain::getter()
{
    if(serial->isOpen())
        write(m_write->socket(),"GET",3);
}

