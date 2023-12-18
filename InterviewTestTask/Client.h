#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "ColorModel.h"

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(ColorModel& model);
    ~Client();
    Q_INVOKABLE void run();
    Q_INVOKABLE void stop();

signals:
    void startDownload(int num);//signal which is sent when downloading is starting. num - number of elements fro downloading
    void finishDownload();//signal which is sent when downloading is finished
    void elementDownloaded(int count);//signal which is sent when elements is downloaded. num - number of downloaded element
    void errorSignal(const QString& err);//signal which is sent when error occured. err - error text

private slots:
    void handleNewColor(const QString& color);//slot for handling new color from server

private:
    void connectTcp();
    void onDisconnected();
    void sendNextCommands();
    void sendCommand(const QString& command);
    void readData();

    ColorModel& m_model;
    QTcpSocket m_socket;
    std::vector<QColor> m_downloadedColors;
    bool m_continueDownloading;
};

#endif // CLIENT_H
