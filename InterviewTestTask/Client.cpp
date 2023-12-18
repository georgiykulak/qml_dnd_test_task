#include "Client.h"
#include "Conf.h"

#include <QColor>
#include <QDataStream>
#include <QDebug>

#include <thread>
#include <chrono>

using namespace std::chrono_literals;

Client::Client(ColorModel& model)
    : m_model{model}
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
    std::this_thread::sleep_for(100ms);
    sendCommand(STOP_MESSAGE_REQUEST);

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
    if (m_socket.state() == QTcpSocket::ConnectedState)
    {
        m_socket.write(command.toUtf8());
        m_socket.waitForBytesWritten(100);
        qDebug() << "Client sendCommand: command ->" << command;
    }
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

        while (continueDownloading && i <= ITEMS_COUNT)
        {
            std::this_thread::sleep_for(300ms);
            socket.write(NEXT_MESSAGE_REQUEST.toUtf8());
            socket.waitForBytesWritten(100);
            qDebug() << "Client sendNextCommands: Sending 'next' command, i =" << i;
            ++i;
        }
    });

    thr.detach();
}

void Client::readData()
{
    qDebug() << "Client readData: readyRead emitted";

    QTextStream stream(&m_socket);
    QString colorString;
    m_socket.waitForBytesWritten();
    stream >> colorString;
    qDebug() << "Received data:" << colorString;

    QColor color(colorString);

    m_downloadedColors.push_back(color);
    std::vector<ColorItem*> vec; // One-time memory-leak, ignore for now
    for (const auto& color : m_downloadedColors)
    {
        vec.emplace_back(new ColorItem(color));
    }

    m_model.setColorItemsVector(vec);
}
