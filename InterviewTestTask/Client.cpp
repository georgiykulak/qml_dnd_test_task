#include "Client.h"
#include "Conf.h"

#include <QDataStream>
#include <QDebug>

#include <thread>
#include <chrono>

Client::Client()
{
    connect(&m_socket, &QTcpSocket::readyRead, this, &Client::readData);
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
    using namespace std::chrono_literals;
    m_socket.connectToHost(ADDRESS, PORT);
    if( m_socket.waitForConnected(3000) )
    {
        qDebug() << "Client connectTcp: Connection established!";

        std::thread sendCommandThread([this]() // Pass socket fd instead to remove warning (later)
        {
            for (int i = 0; i < ITEMS_COUNT; ++i)
            {
                sendCommand(NEXT_MESSAGE_REQUEST);
                std::this_thread::sleep_for(500ms);
            }
        });
        sendCommandThread.detach();

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
    m_socket.write(command.toUtf8());
    m_socket.waitForBytesWritten();
    qDebug() << "Client sendCommand: command ->" << command;
}

void Client::readData()
{
    using namespace std::chrono_literals;
    qDebug() << "Client readData: readyRead emitted";

    QTextStream stream(&m_socket);

    QByteArray data = m_socket.readAll();
    std::this_thread::sleep_for(500ms);
    qDebug() << "Received data:" << data;
}
