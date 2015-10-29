#include "sender.h"
#include "ui_sender.h"

Sender::Sender(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sender)
{
    ui->setupUi(this);
    statusLabel = new QLabel(tr("Ready to broadcast on port 45454"));
  //  statusLabel->setText(tr("broadcast sender"));
    ui->horizontalLayout->addWidget(statusLabel);
    //startButton = new QPushButton;
    //quitButton = new QPushButton;
    //buttonBox = new QDialogButtonBox;
    //buttonBox->addButton(startButton,QDialogButtonBox::AcceptRole	);
    //buttonBox->addButton(quitButton,QDialogButtonBox::AcceptRole	);
    timer =new QTimer;
    udpSocket = new QUdpSocket;
    messageNo = 1;
    connect(ui->startbutton,SIGNAL(clicked()),this,SLOT(startBroadcasting()));
    connect(ui->quitbutton,SIGNAL(clicked()),this,SLOT(close()));
    connect(timer,SIGNAL(timeout()),this,SLOT(broadcastDatagram()));

}
Sender::~Sender()
{
    delete ui;
}

void Sender::startBroadcasting()
{
ui->startbutton->setEnabled(false);
timer->start(50);
}

void Sender::broadcastDatagram()
{
statusLabel->setText(tr("Now Broadcasting datagram %1").arg(messageNo));
QByteArray datagram = "gurpartap" + QByteArray::number(messageNo);
udpSocket->writeDatagram(datagram.data(),datagram.size(),QHostAddress::Broadcast,45454);
++messageNo;
}
