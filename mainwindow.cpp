#include "mainwindow.h"
#include "ui_mainwindow.h"
bool CALL_CONNECTED = false,flag = false;
char input[3];
 int input_count = 0;
 int cursor_position = 0;
char *ptr;
char input_characters_list[11]={'0','1','2','3','4','5','6','7','8','9','.'};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptr = &input[0];
    call_switch_poll =  new QTimer;
    get_input_poll   =  new QTimer;
    emergency_call = new qlinphone;
    lcd = new Lcd_lib ;
    memset(input,0,sizeof(input));
    //input = &input_characters_list[0];
    get_input_poll->setInterval(200);
    call_switch_poll->setInterval(500);
    //call_switch_poll->start();
    connect(call_switch_poll,SIGNAL(timeout()),this,SLOT(check_call_button_state()));
    connect(get_input_poll,SIGNAL(timeout()),this,SLOT(check_input_buttons_state()));
    connect(this,SIGNAL(call_driver()),emergency_call,SLOT(talk_to_driver()));
    connect(emergency_call,SIGNAL(Call_ended()),this,SLOT(show_call_ended()));
    connect(emergency_call,SIGNAL(Call_connected()),this,SLOT(show_call_connected()));
    connect(this,SIGNAL(terminate_call()),emergency_call,SLOT(end_current_call()));
    input_ip_address();
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

void MainWindow::check_input_buttons_state()
{

    char value_up_button,value_enter_button;
    int up_button_fd,enter_button_fd;
    up_button_fd=open("/sys/class/gpio/gpio23_ph16/value",O_RDONLY);
    enter_button_fd=open("/sys/class/gpio/gpio22_ph15/value",O_RDONLY);
    read(up_button_fd,&value_up_button,sizeof(char));
    read(enter_button_fd,&value_enter_button,sizeof(char));
    lseek(up_button_fd,0,SEEK_SET);
    lseek(enter_button_fd,0,SEEK_SET);
    if((value_up_button == '0'))
    {
        if(input_count>=11)
            input_count = 0;
        qDebug() << "value_up_button presses" ;
        qDebug() << "count = " << input_count ;
        qDebug() << "Character = " << input_characters_list[input_count];
        lcd->send_command(0x80 + cursor_position);
        send_byte(input_characters_list[input_count]);
        input_count ++;
    }
    if((value_enter_button == '0') && !flag )
    {
       // get_input_poll->start();
        send_clear();
        flag = true;
    }
    else if(value_enter_button == '0' && flag)
    {

        input[cursor_position]  = input_characters_list[input_count-1];
//        ptr ++;
        qDebug() << "Enetered IP  = " << input;
        cursor_position ++ ;
        input_count = 0;
        if(cursor_position == 2)
        {
            qDebug() << "get_input_poll Stopped";
            get_input_poll->stop();
            call_switch_poll->start();
        }
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
void MainWindow::send_byte( char byte)
{
    lcd->send_character(byte);
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

void MainWindow::input_ip_address()
{
    send_clear();
    send_string("Please Enter MOP","IP ADDRESS",3,5);
    qDebug() << "Inside input_ip_address()";
    get_input_poll->start();
}

