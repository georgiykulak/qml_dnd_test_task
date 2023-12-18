#include "MainModel.h"

MainModel::MainModel()
{
    qRegisterMetaType<MainModel*>("MainModel*");
}

int MainModel::rowCount(const QModelIndex &parent) const
{
}

QVariant MainModel::data(const QModelIndex &index, int role) const
{
}

QHash<int, QByteArray> MainModel::roleNames() const
{
}
