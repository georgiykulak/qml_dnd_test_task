#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <QObject>
#include "ColorItemListModel.h"

class ColorItem;
class ColorModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ColorItemListModel* listOfColorItems READ listOfColorItems CONSTANT)
public:
    ColorModel(QObject* = nullptr) {}

    Q_INVOKABLE QString printModel() { return m_listOfColorItems.print(); }
    ColorItemListModel* listOfColorItems() { return &m_listOfColorItems; }
    void changeItemColor(int visualIndex, const QColor& newColor)
    { m_listOfColorItems.changeItemColor(visualIndex, newColor); }
    void setColorItemsVector(const std::vector<ColorItem*>& vec)
    { m_listOfColorItems.updateFromVector(vec); }

private:
    ColorItemListModel m_listOfColorItems;
};

#endif // COLORMODEL_H
