#include "listviewmodel.h"

ListViewModel::ListViewModel(InputType inputType, QObject * parent)
    : QAbstractItemModel(parent),
      m_inputType(inputType)
{

}

void ListViewModel::SetData(const QList<ModelArg> & arglist)
{
    beginResetModel();
    m_argList = arglist;
    endResetModel();
}

void ListViewModel::AddItem(const ModelArg &arg)
{
    beginResetModel();
    m_argList << arg;
    endResetModel();
}

void ListViewModel::DelItem(int row)
{
    if(m_argList.size() < row)
        return;
    beginResetModel();
    m_argList.removeAt(row);
    endResetModel();
}

void ListViewModel::AmendItem(const ModelArg &arg, int row)
{
    if(m_argList.size() < row)
        return;
    beginResetModel();
    m_argList[row] = arg;
    endResetModel();
}

void ListViewModel::DeleteAllItems()
{
    beginResetModel();
    m_argList.clear();
    endResetModel();
}

QList<Qt::Key> ListViewModel::GetKeys()
{
    QList<Qt::Key> returnList;
    for(int i = 0; i < m_argList.size(); ++i)
    {
        returnList << m_argList.at(i).qKey;
    }
    return returnList;
}

QList<QPoint> ListViewModel::GetMousePos()
{
    QList<QPoint> returnList;
    for(int i = 0; i < m_argList.size(); ++i)
    {
        QPoint tmpPos;
        tmpPos.setX(m_argList.at(i).x);
        tmpPos.setY(m_argList.at(i).y);
        returnList << tmpPos;
    }
    return returnList;
}

int ListViewModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

int ListViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_argList.size();
}

QVariant ListViewModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        QVariant var;
        var.setValue(m_argList[index.row()]);
        return var;
    }
    return QVariant();
}

QModelIndex ListViewModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (parent.isValid())
        return QModelIndex();

    return createIndex(row, column, const_cast<ModelArg*>(&m_argList[row]));
}

QModelIndex ListViewModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QModelIndex(); // 无父项
}
