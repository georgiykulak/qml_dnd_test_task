#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QQmlContext>
#include <QObject>

#include "Client.h"
#include "ColorModel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    ColorModel* colorModel = new ColorModel;
    qmlRegisterSingletonInstance<ColorModel>("ColorModels", 1, 0, "ColorModel", colorModel);

    Client client;

    QObject::connect(&client, &Client::setColorItemsVector,
                     colorModel, &ColorModel::onSetColorItemsVector);
    QObject::connect(&client, &Client::changeItemColor,
                     colorModel, &ColorModel::onChangeItemColor);

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
