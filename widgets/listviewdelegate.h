#ifndef LISTVIEWDELEGATE_H
#define LISTVIEWDELEGATE_H

#include "inputlineedit.h"

#include "services/defines.h"

#include <QStyledItemDelegate>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class ListViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ListViewDelegate(InputType input, QWidget *parent = nullptr);

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

Q_SIGNALS:
    void SigRemoveItem(QModelIndex index) const;
    void SigArgChanged(ModelArg arg, int row) const;

private:
    InputType m_inputType;
};

class InputWidget : public QWidget
{
    Q_OBJECT
public:
    InputWidget(InputType input, QWidget *parent = nullptr);

    void SetData(const ModelArg & key);

Q_SIGNALS:
    void SigCurrentWidgetRemove();
    void SigArgChanged(ModelArg arg);

protected:
    ModelArg GetArg();

private:
    InputType           m_inputType;

    QLabel              *m_xLabel;
    InputLineedit       *m_xLine;
    QLabel              *m_yLabel;
    InputLineedit       *m_yLine;

    QLabel              *m_keyLabel;
    InputLineedit       *m_keyLine;

    QPushButton         *m_delBtn;

    bool                m_signalFlag;
};

#endif // LISTVIEWDELEGATE_H
