#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "ColorItem.h"

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client();
    ~Client();
    Q_INVOKABLE void run();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void tryChangeItemColor(int visualIndex, const QString& colorText);

signals:
    void startDownload(int num);//signal which is sent when downloading is starting. num - number of elements fro downloading
    void finishDownload();//signal which is sent when downloading is finished
    void elementDownloaded(int count);//signal which is sent when elements is downloaded. num - number of downloaded element
    void errorSignal(const QString& err);//signal which is sent when error occured. err - error text

    void setColorItemsVector(const std::vector<std::shared_ptr<ColorItem>>& vec);
    void changeItemColor(int visualIndex, const QColor& newColor);

private slots:
    void handleNewColor(const QString& color);//slot for handling new color from server

private:
    void connectTcp();
    void onDisconnected();
    void sendNextCommands();
    void sendCommand(const QString& command);
    void readData();

    QTcpSocket m_socket;
    std::vector<QColor> m_downloadedColors;
    std::atomic_bool m_continueDownloading;
};

#endif // CLIENT_H
