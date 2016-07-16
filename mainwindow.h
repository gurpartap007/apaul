#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qlinphone.h"
#include <QMainWindow>
#include <QChar>
#include <QString>
#include <lcd_lib.h>
#include <lcd_lib_global.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    qlinphone *emergency_call;
    Lcd_lib *lcd;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *call_switch_poll,*get_input_poll;
    QThread *call_button_polling;

 signals:
void call_driver();
void terminate_call();
public slots:

   void check_call_button_state();
   void check_input_buttons_state();
   void show_call_ended();
   void show_call_connected();
   void show_default_message();
   void show_wait_for_driver_reply();
   void send_byte( char  byte);
   void send_string(const char * line1,const char * line2,int x,int y);
   void send_clear();
   void input_ip_address();
};

#endif // MAINWINDOW_H
