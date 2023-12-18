#include "MainModel.h"

#include <QDebug>

MainModel::MainModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int MainModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "MainModel rowCount: rows =" << parent.row() << " columns =" << parent.column();
    if (!parent.isValid())
        return 0;

    return m_colorList.size();
}

QVariant MainModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "MainModel data: rows =" << index.row() << " columns =" << index.column() << " role =" << role;
    if (!index.isValid())
        return QVariant();

    if (role == NameRole)
        return m_colorList.at(index.row());

    return QVariant();
}

QHash<int, QByteArray> MainModel::roleNames() const
{
    qDebug() << "MainModel roleNames: get role names";
    QHash<int, QByteArray> roles;
    roles[NameRole] = "UserRole";
    return roles;
}
