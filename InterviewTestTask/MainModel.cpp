#include "MainModel.h"

#include <QDebug>

MainModel::MainModel()
{
    qRegisterMetaType<MainModel*>("MainModel*");
}

int MainModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "MainModel rowCount: rows =" << parent.row() << " columns =" << parent.column();
}

QVariant MainModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "MainModel data: rows =" << index.row() << " columns =" << index.column() << " role =" << role;
}

QHash<int, QByteArray> MainModel::roleNames() const
{
    qDebug() << "MainModel roleNames: get role names";
}
