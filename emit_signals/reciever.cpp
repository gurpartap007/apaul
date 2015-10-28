#include "reciever.h"
#include "ui_reciever.h"
#include <stdio.h>
#include <sys/types.h>
#include <linux/wait.h>

reciever::reciever(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reciever)
{
    ui->setupUi(this);
    int counter=0,i=0;
    for(counter=0;counter<=6536;counter++)
    {
        for(i=0;i<=2000;i++)
        {}
    }
    //sleep(5);
           // emit this->counter();

}

reciever::~reciever()
{
    delete ui;
}




void reciever::on_pushButton_clicked()
{
    emit this->play();
}


void reciever::on_pushButton_2_clicked()
{
    emit this->pause();
}

void reciever::on_pushButton_3_clicked()
{
    emit this->stop();
}
