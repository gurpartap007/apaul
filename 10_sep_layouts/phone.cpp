#include <QString>
#include <qstring.h>
#include "phone.h"
#include "mainwindow.h"
#include "ui_phone.h"

phone::phone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::phone)
{
    ui->setupUi(this);
    //system("linphonecsh exit");
    system("linphonecsh init");
    //ui->lineEdit->setText("  Dialling 192.168.0.115");
    connect(ui->call_button,SIGNAL(clicked()),this,SLOT(call_to_board()));
    connect(ui->stop_button,SIGNAL(clicked()),this,SLOT(stop_call_to_board()));

}

phone::~phone()
{
    delete ui;
}

void phone::call_to_board()
{
  // ui->call_button->styleSheet(QString("border-color:green"));
   ui->lineEdit->setText("     calling 192.168.0.115");
   system("linphonecsh generic \"soundcard use 1\"");
   system("linphonecsh dial root@192.168.0.115");

}

void phone::stop_call_to_board()
{
    ui->lineEdit->clear();
    system("linphonecsh generic \"terminate\"");
    ui->lineEdit->setText("              Call is stopped");
}


