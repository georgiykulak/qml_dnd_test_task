#include "ColorItemListModel.h"

#include <QDebug>

ColorItemListModel::ColorItemListModel(QObject *parent)
    : QAbstractListModel{parent}
{}

void ColorItemListModel::updateFromVector(std::vector<ColorItem *> newColorItems)
{
    beginResetModel();
    m_colorItems.clear();
    for (const auto &item : newColorItems)
    {
        m_colorItems << item;
    }
    endResetModel();
}

QHash<int, QByteArray> ColorItemListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ColorRole] = "color";
    roles[ModelIndexRole] = "modelIndex";
    return roles;
}

QVariant ColorItemListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const ColorItem* colorItem = m_colorItems[index.row()];
    switch (role)
    {
    case ColorRole:
        return colorItem->color();

    case ModelIndexRole:
        if (std::find(m_colorItems.begin(), m_colorItems.end(), colorItem)
            != m_colorItems.end())
        {
            return std::distance(
                        m_colorItems.begin(),
                        std::find(m_colorItems.begin(), m_colorItems.end(), colorItem)
                    );
        }
        else
        {
            return -1;
        }

    default:
        return QVariant();
    }
}

int ColorItemListModel::rowCount(const QModelIndex &) const
{
    return m_colorItems.count();
}

void ColorItemListModel::changeItemColor(int visualIndex, const QColor &newColor)
{
    if (visualIndex >= 0 && visualIndex < rowCount())
    {
        beginResetModel();
        m_colorItems[visualIndex]->setColor(newColor);
        endResetModel();
    }
}

void ColorItemListModel::move(int from, int to)
{
    if (from >= 0 && from < rowCount()
       && to >= 0 && to < rowCount() && from != to)
    {
        if (from == to - 1)
        {
            // Allow item moving to the bottom
            to = from++;
        }

        beginResetModel();
        qDebug() << "model move from: " << from << " to: " << to;
        m_colorItems.move(from, to);
        endResetModel();
    }
}

QString ColorItemListModel::print()
{
    QString tmp;
    for(int i = 0; i < m_colorItems.size(); ++i) {
        tmp.append(QString::number(i));
        tmp.append(": ");
        tmp.append(m_colorItems.at(i)->color().name());
        tmp.append("; ");
    }
    return tmp;
}
