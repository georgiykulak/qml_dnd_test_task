#include "Client.h"
#include "Conf.h"

#include <QColor>
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

    if (m_socket.state() != QTcpSocket::ClosingState)
        m_socket.close();

    emit finishDownload();
}

void Client::tryChangeItemColor(int visualIndex, const QString &colorText)
{
    qDebug() << "Client tryChangeItemColor: visualIndex =" << visualIndex
             << "text =" << colorText;

    QColor newColor(colorText);

    if (!newColor.isValid())
    {
        qDebug() << "Client tryChangeItemColor: Invalid color"
                 << colorText << ", not changing color";
        return;
    }

    emit changeItemColor(visualIndex, newColor);
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
    if (m_continueDownloading.load() && m_socket.state() == QTcpSocket::ConnectedState)
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

    std::thread thr([socketDesrciptor, socketState](std::atomic_bool& cd)
    {
        QTcpSocket socket;
        if (!socket.setSocketDescriptor(socketDesrciptor, socketState))
        {
            qDebug() << "Can't initialize socket from socket descriptor! Socket state ="
                     << socketState;
            return;
        }

        std::size_t i = 0;

        while (cd && i <= ITEMS_COUNT)
        {
            std::this_thread::sleep_for(300ms);
            socket.write(NEXT_MESSAGE_REQUEST.toUtf8());
            socket.waitForBytesWritten(100);
            qDebug() << "Client sendNextCommands: Sending 'next' command, i =" << i;
            ++i;
        }
    }, std::ref(m_continueDownloading));

    thr.detach();
}

void Client::readData()
{
    qDebug() << "Client readData: readyRead emitted";

    if (!m_socket.isReadable())
        return;

    QTextStream stream(&m_socket);
    QString colorString;
    m_socket.waitForBytesWritten();
    stream >> colorString;
    qDebug() << "Received data:" << colorString;

    QColor color(colorString);

    m_downloadedColors.push_back(color);
    emit elementDownloaded(m_downloadedColors.size());

    std::vector<std::shared_ptr<ColorItem>> vec;
    for (const auto& color : m_downloadedColors)
    {
        vec.emplace_back(std::make_shared<ColorItem>(color));
    }

    emit setColorItemsVector(vec);
}
