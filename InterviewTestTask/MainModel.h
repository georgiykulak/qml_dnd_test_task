#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QAbstractListModel>

class MainModel : public QAbstractListModel
{
public:
    MainModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray> roleNames() const override;
};

#endif // MAINMODEL_H
