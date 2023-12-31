#ifndef COLORMODEL_H
#define COLORMODEL_H

#include "ColorItemListModel.h"

#include <QObject>

#include <memory>

class ColorItem;
class ColorModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ColorItemListModel* listOfColorItems READ listOfColorItems CONSTANT)
public:
    ColorModel(QObject* = nullptr) {}

    Q_INVOKABLE QString printModel() { return m_listOfColorItems.print(); }
    ColorItemListModel* listOfColorItems() { return &m_listOfColorItems; }

public slots:
    void onSetColorItemsVector(const std::vector<std::shared_ptr<ColorItem>>& vec)
    { m_listOfColorItems.updateFromVector(vec); }
    void onChangeItemColor(int visualIndex, const QColor& newColor)
    { m_listOfColorItems.changeItemColor(visualIndex, newColor); }

private:
    ColorItemListModel m_listOfColorItems;
};

#endif // COLORMODEL_H
