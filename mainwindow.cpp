#include "mainwindow.h"
#include "ui_mainwindow.h"
bool CALL_CONNECTED = false;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    call_switch_poll =  new QTimer;
    emergency_call = new qlinphone;
    lcd = new Lcd_lib ;
    call_switch_poll->setInterval(1000);
    call_switch_poll->start();
    connect(call_switch_poll,SIGNAL(timeout()),this,SLOT(check_call_button_state()));
    connect(this,SIGNAL(call_driver()),emergency_call,SLOT(talk_to_driver()));
    connect(emergency_call,SIGNAL(Call_ended()),this,SLOT(show_call_ended()));
    connect(emergency_call,SIGNAL(Call_connected()),this,SLOT(show_call_connected()));
    connect(this,SIGNAL(terminate_call()),emergency_call,SLOT(end_current_call()));
    show_wait_for_driver_reply();
}

MainWindow::~MainWindow()
{
    delete ui;
}


// This function will poll the state of call and stop buttons and emit appropriate signals accordingly
void MainWindow::check_call_button_state()
{
    char value_call_button,value_stop_button;
    int call_button_fd,stop_button_fd;
    call_button_fd=open("/sys/class/gpio/gpio23_ph16/value",O_RDONLY);
    stop_button_fd=open("/sys/class/gpio/gpio22_ph15/value",O_RDONLY);
    read(call_button_fd,&value_call_button,sizeof(char));
    read(stop_button_fd,&value_stop_button,sizeof(char));
    lseek(call_button_fd,0,SEEK_SET);
    lseek(stop_button_fd,0,SEEK_SET);
    if(!CALL_CONNECTED & (value_call_button == '0'))
    {
        qDebug() << "inside Call button routine";
        show_wait_for_driver_reply();
        emit call_driver() ;
    }
    if(CALL_CONNECTED & (value_stop_button == '0'))
    {
        qDebug() << "inside stop button routine";
        emit terminate_call() ;
    }
}

// show Call ended notification on lcd and after that show default message on LCD
void MainWindow::show_call_ended()
{
    send_string("Emergency Call","Ended",2,4);
    sleep(5);
    CALL_CONNECTED = false;
    show_default_message();
}

// show Call Connected notification on lcd
void MainWindow::show_call_connected()
{
    CALL_CONNECTED = true;
    send_string("Call Connected","Please Speak Now",4,1);
}

// show default message on lcd
void MainWindow::show_default_message()
{
    send_string("Press Call","in Emergency",4,3);
}

// show message when Call is ringing remotely
void MainWindow::show_wait_for_driver_reply()
{
    send_string("Please Wait For","Driver Reply",1,4);
}

// lcd routine to write single charcter
void MainWindow::send_byte(QChar byte)
{

}

// lcd routine to write string along with line 1 starting postion x and line 2 starting position y
void MainWindow::send_string(const char * line1,const char * line2,int x,int y)
{
    int counter;
    unsigned int hex_x_position,hex_y_position;
    hex_x_position = x + 0x80;
    hex_y_position = y + 0xc0;
    send_clear();
    lcd->send_command(hex_x_position);
    for(counter=0;counter  <(strlen(line1));counter++)
        lcd->send_character(line1[counter]);
    lcd->send_command(hex_y_position);
    for(counter=0;counter<(strlen(line2));counter++)
        lcd->send_character(line2[counter]);
}

// lcd routine to clear the screen
void MainWindow::send_clear()
{
lcd->send_command(0x01);
}

