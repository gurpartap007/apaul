#include "fortuneserver.h"

FortuneServer::FortuneServer(QObject *parent) : QObject(parent)
{
    // first we set up the server and make it listen
    // for new connections on 127.0.0.1:56789

    server = new QTcpServer;
    if (!(server->listen(QHostAddress::LocalHost, 56789))) {
        qFatal("ERROR: Failed to bind TCP server to port 56789 on 127.0.0.1");
    }

    // now we connect the server's new connection signal
    // to the new connection slot in this object

    connect(server, SIGNAL(newConnection()), this, SLOT(sendFortune()));

    // let's populate the fortune list

    fortunes.append(QByteArray("You've been leading a dog's life. Stay off the furniture.\n"));
    fortunes.append(QByteArray("You've got to think about tomorrow.\n"));
    fortunes.append(QByteArray("You will be surprised by a loud noise.\n"));
    fortunes.append(QByteArray("You will feel hungry again in another hour.\n"));
    fortunes.append(QByteArray("You might have mail.\n"));
    fortunes.append(QByteArray("You cannot kill time without injuring eternity.\n"));
    fortunes.append(QByteArray("Computers are not intelligent. They only think they are.\n"));

    // and we're done here
}

FortuneServer::~FortuneServer()
{
    // shut down the server first

    server->close();

    // disconnect all signals and slots connected to
    // this server

    server->disconnect();

    // and finally, queue this object for deletion at
    // the first opportune moment

    server->deleteLater();

    // and that's it
}

void FortuneServer::sendFortune()
{
    // we'll grab a client socket off of the server
    // first

    QTcpSocket * socket = server->nextPendingConnection();

    // now we'll wait until the socket is connected

    if (!(socket->waitForConnected())) {
        qDebug() << socket->errorString();
        return;
    }

    // now we'll choose a random fortune and send it to the
    // reciever

    socket->write(fortunes.at(qrand() % fortunes.size()));

    // we'll now tear down the connection

    socket->disconnectFromHost();
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

    // and we're done
}


