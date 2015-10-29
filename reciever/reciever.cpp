#include "reciever.h"
#include "ui_reciever.h"

reciever::reciever(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::reciever)
{
    ui->setupUi(this);
    udpsocket = new QUdpSocket;
    udpsocket->bind(45454,QUdpSocket::ShareAddress);
    connect(udpsocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));


}

reciever::~reciever()
{
    delete ui;
}

void reciever::processPendingDatagrams()
{
    while(udpsocket->hasPendingDatagrams())
    {
       QByteArray datagram;
       datagram.resize(udpsocket->pendingDatagramSize());
       udpsocket->readDatagram(datagram.data(),datagram.size());
       ui->label->setText(tr("recieved datagram = %1").arg(datagram.data()));
    }
}
