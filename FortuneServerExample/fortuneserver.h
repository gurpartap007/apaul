#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QList>
#include <QByteArray>

class FortuneServer : public QObject
{
    Q_OBJECT

    private:

    QTcpServer * server;
    QList<QByteArray> fortunes;

    public:

    explicit FortuneServer(QObject *parent = 0);
    ~FortuneServer();

    signals:

    private slots:

    void sendFortune();
};

#endif // FORTUNESERVER_H
