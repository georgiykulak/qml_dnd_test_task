#include "Client.h"
#include "Conf.h"

#include <QDataStream>
#include <QDebug>

Client::Client()
{
}

Client::~Client()
{
    stop();
}

void Client::run()
{
    qDebug() << "Client run: start downloading...";

    connectTcp();
}

void Client::stop()
{
    qDebug() << "Client stop: stop downloading...";

    sendCommand(STOP_MESSAGE_REQUEST);

    emit finishDownload();
}

void Client::handleNewColor(const QString &color)
{
    qDebug() << "Client handleNewColor: edit current color to " << color;
}

void Client::connectTcp()
{
    m_socket.connectToHost(ADDRESS, PORT);
    if( m_socket.waitForConnected(3000) )
    {
        qDebug() << "Client connectTcp: Connection established!";
        sendCommand(NEXT_MESSAGE_REQUEST);

        emit startDownload(ITEMS_COUNT);
    }
    else
    {
        qDebug() << "Client connectTcp: Can't connect to server!";
        emit errorSignal("Connection timed out!");
    }
}

void Client::sendCommand(const QString& command)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << command;

    m_socket.write(data);
    m_socket.flush();
    qDebug() << "Client sendCommand: command ->" << command;
}
