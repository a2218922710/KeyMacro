#ifndef INPUTLISTVIEW_H
#define INPUTLISTVIEW_H

#include "services/defines.h"
#include "listviewdelegate.h"
#include "listviewmodel.h"

#include <QListView>

class InputListView : public QListView
{
    Q_OBJECT
public:
    InputListView(InputType inputType, QWidget * parent = nullptr);

    void AddItem();
    void DelItem(int row);
    void ClearItems();

    QList<Qt::Key> GetKeys();
    QList<QPoint>  GetMousePos();

protected:
    void Update();

private:
    ListViewDelegate * m_delegate;
    ListViewModel    * m_model;
};

#endif // INPUTLISTVIEW_H
