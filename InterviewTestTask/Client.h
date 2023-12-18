#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client();
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
    void sendCommand(const QString& command);

    QTcpSocket m_socket;
};

#endif // CLIENT_H
