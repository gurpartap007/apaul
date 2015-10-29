#ifndef SENDER_H
#define SENDER_H
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QUdpSocket>
#include <QDialogButtonBox>
#include <QTimer>
#include <QHBoxLayout>

namespace Ui {
class Sender;
}

class Sender : public QMainWindow
{
    Q_OBJECT // required macro in order to use signals and slots

public:
    explicit Sender(QWidget *parent = 0);
    ~Sender();

private slots:
    void startBroadcasting();
    void broadcastDatagram();

private:
    QLabel *statusLabel;
    QPushButton *startButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QUdpSocket *udpSocket;
    QHBoxLayout *mainlayout;
    QTimer *timer;
    int messageNo;
    Ui::Sender *ui;
};

#endif // SENDER_H
