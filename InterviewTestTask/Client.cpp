#include "Client.h"
#include "Conf.h"

#include <QDataStream>
#include <QDebug>

#include <thread>
#include <chrono>

using namespace std::chrono_literals;

Client::Client()
{
    connect(&m_socket, &QTcpSocket::readyRead, this, &Client::readData);
    connect(&m_socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
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

    m_continueDownloading = false;
    sendCommand(STOP_MESSAGE_REQUEST);
    std::this_thread::sleep_for(500ms);

    m_socket.close();

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

        m_continueDownloading = true;

        emit startDownload(ITEMS_COUNT);

        sendNextCommands();
    }
    else
    {
        qDebug() << "Client connectTcp: Can't connect to server!";
        emit errorSignal("Connection timed out!");
    }
}

void Client::onDisconnected()
{
    stop();
}

void Client::sendCommand(const QString& command)
{
    m_socket.write(command.toUtf8());
    m_socket.flush();
    qDebug() << "Client sendCommand: command ->" << command;
}

void Client::sendNextCommands()
{
    qintptr socketDesrciptor = m_socket.socketDescriptor();
    auto socketState = m_socket.state();
    const bool& continueDownloading = m_continueDownloading;

    std::thread thr([socketDesrciptor, socketState, &continueDownloading]()
    {
        QTcpSocket socket;
        if (!socket.setSocketDescriptor(socketDesrciptor, socketState))
        {
            qDebug() << "Can't initialize socket from socket descriptor! Socket state ="
                     << socketState;
            return;
        }

        std::size_t i = 0;

        while (continueDownloading && i < ITEMS_COUNT)
        {
            socket.write(NEXT_MESSAGE_REQUEST.toUtf8());
            socket.flush();
            qDebug() << "Client sendNextCommands: Sending 'next' command, i =" << i;
            std::this_thread::sleep_for(500ms);
            ++i;
        }
    });

    thr.detach();
}

void Client::readData()
{
    qDebug() << "Client readData: readyRead emitted";

    QTextStream stream(&m_socket);

    QByteArray data = m_socket.readAll();
    std::this_thread::sleep_for(500ms);
    qDebug() << "Received data:" << data;

    // Append to list
}
