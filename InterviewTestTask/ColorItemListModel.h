#ifndef COLORITEMLISTMODEL_H
#define COLORITEMLISTMODEL_H

#include "ColorItem.h"

#include <QAbstractListModel>

class ColorItemListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ThingieRoles
    {
        ColorRole = Qt::UserRole + 1,
        ModelIndexRole
    };

    explicit ColorItemListModel(QObject *parent = nullptr);

    void updateFromVector(std::vector<ColorItem*> newColorItems);
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void changeItemColor(int visualIndex, const QColor& newColor);

    Q_INVOKABLE void move(int from, int to);
    Q_INVOKABLE QString print();

private:
    QList<ColorItem*> m_colorItems;
};

#endif // COLORITEMLISTMODEL_H
