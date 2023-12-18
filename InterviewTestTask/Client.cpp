#include "Client.h"


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
}

void Client::stop()
{
    qDebug() << "Client stop: stop downloading...";
}

void Client::handleNewColor(const QString &color)
{
    qDebug() << "Client handleNewColor: edit current color to " << color;
}
