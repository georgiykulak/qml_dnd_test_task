/* Author: Remy van Elst, https://raymii.org
 * License: GNU AGPLv3
 */

#include "ThingModel.h"
//#include "Thingie.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    //qRegisterMetaType<std::vector<Thingie*>>("std::vector<Thingie*>");
    ThingModel* thingModel = new ThingModel;
    qmlRegisterSingletonInstance<ThingModel>("org.raymii.ThingModel", 1, 0, "ThingModel", thingModel);


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
