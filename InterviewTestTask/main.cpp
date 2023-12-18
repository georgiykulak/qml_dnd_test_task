#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQmlContext>
#include "Client.h"
#include "MainModel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    Client client;

    qmlRegisterType<MainModel>("MainModels", 1, 0, "MainModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("client", &client);
    engine.load(url);

    qDebug() << "Start the application!";
    client.run();

    return app.exec();
}
