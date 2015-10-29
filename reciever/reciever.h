#ifndef RECIEVER_H
#define RECIEVER_H

#include <QMainWindow>
#include <QUdpSocket>

namespace Ui {
class reciever;
}

class reciever : public QMainWindow
{
    Q_OBJECT

public:
    explicit reciever(QWidget *parent = 0);
    ~reciever();
private slots:
    void processPendingDatagrams();
private:
QUdpSocket *udpsocket ;
private:
    Ui::reciever *ui;
};

#endif // RECIEVER_H
