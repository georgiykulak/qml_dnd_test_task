#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QAbstractListModel>

class MainModel : public QAbstractListModel
{
public:
    enum MyRoles {
        NameRole = Qt::UserRole + 1,
    };

    MainModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int,QByteArray> roleNames() const override;

private:
    QStringList m_colorList;
};

#endif // MAINMODEL_H
