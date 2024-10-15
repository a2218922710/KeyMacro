#include "inputlistview.h"

InputListView::InputListView(InputType inputType, QWidget *parent)
    : QListView(parent),
      m_delegate(new ListViewDelegate(inputType, this)),
      m_model(new ListViewModel(inputType, this))
{
    switch (inputType) {
    case KeyType:
        break;
    case MouseType:
        break;
    default:
        break;
    }

    connect(m_delegate, &ListViewDelegate::SigRemoveItem, this, [=](QModelIndex index) {
        this->DelItem(index.row());
    });

    connect(m_delegate, &ListViewDelegate::SigArgChanged, this, [=](ModelArg arg, int row) {
        m_model->AmendItem(arg, row);
    });

    QList<ModelArg> list;
    ModelArg arg1;
    arg1.qKey = Qt::Key_F;
    arg1.showKeyWord = "Key_F";
    list << arg1;
    m_model->SetData(list);

    this->setItemDelegate(m_delegate);
    this->setModel(m_model);
    this->Update();
}

void InputListView::AddItem()
{
    ModelArg tmpArg;
    m_model->AddItem(tmpArg);
    this->Update();
}

void InputListView::DelItem(int row)
{
    m_model->DelItem(row);
    this->Update();
}

void InputListView::ClearItems()
{
    m_model->DeleteAllItems();
    this->Update();
}

QList<Qt::Key> InputListView::GetKeys()
{
    return m_model->GetKeys();
}

QList<QPoint> InputListView::GetMousePos()
{
    return m_model->GetMousePos();
}

void InputListView::Update()
{
    for(int i = 0; i < m_model->rowCount(); ++i)
    {
        this->openPersistentEditor(m_model->index(i, 0));
    }
}
