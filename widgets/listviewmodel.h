#ifndef LISTVIEWMODEL_H
#define LISTVIEWMODEL_H

#include "services/defines.h"

#include <QAbstractItemModel>
#include <QList>


class ListViewModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ListViewModel(InputType inputType, QObject * parent = NULL);

    void SetData(const QList<ModelArg> & arglist);

    void AddItem(const ModelArg & arg);
    void DelItem(int row);
    void AmendItem(const ModelArg & arg, int row);
    void DeleteAllItems();

    QList<Qt::Key> GetKeys();
    QList<QPoint>  GetMousePos();

public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role) const;
    // 创建并返回索引
     QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
     // 返回父索引
     QModelIndex parent(const QModelIndex &index) const;
private:
    InputType       m_inputType;
    QList<ModelArg> m_argList;
};

#endif // LISTVIEWMODEL_H
