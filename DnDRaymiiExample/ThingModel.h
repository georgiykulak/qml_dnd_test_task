/* Author: Remy van Elst, https://raymii.org
 * License: GNU AGPLv3
 */

#ifndef THINGMODEL_H
#define THINGMODEL_H

#include <QObject>
#include <ThingieListModel.h>

class Thingie;
class ThingModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ThingieListModel* listOfThingies READ listOfThingies CONSTANT)
public:
    ThingModel(QObject* parent = nullptr);

    Q_INVOKABLE QString printModel() { return _listOfThingies.print(); }
    ThingieListModel* listOfThingies() { return &_listOfThingies; }

public slots:

signals:

private:
    ThingieListModel _listOfThingies;
};

#endif // THINGMODEL_H
