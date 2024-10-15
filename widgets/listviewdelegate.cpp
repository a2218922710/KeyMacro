#include "listviewdelegate.h"

#include <QHBoxLayout>
#include <QPainter>

ListViewDelegate::ListViewDelegate(InputType input, QWidget *parent)
    : QStyledItemDelegate(parent),
      m_inputType(input)
{

}

QWidget *ListViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    InputWidget * inWidget = new InputWidget(m_inputType, parent);
    connect(inWidget, &InputWidget::SigCurrentWidgetRemove, this, [=](){
        emit SigRemoveItem(index);
    });
    connect(inWidget, &InputWidget::SigArgChanged, this, [=](ModelArg arg){
        emit SigArgChanged(arg, index.row());
    });

    inWidget->SetData(index.data().value<ModelArg>());

    return inWidget;
}

QSize ListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 30);
}

InputWidget::InputWidget(InputType input, QWidget *parent)
    : QWidget(parent),
      m_inputType(input),
      m_xLabel(new QLabel(this)),
      m_xLine(new InputLineedit(MouseType, this)),
      m_yLabel(new QLabel(this)),
      m_yLine(new InputLineedit(MouseType, this)),
      m_keyLabel(new QLabel(this)),
      m_keyLine(new InputLineedit(KeyType, this)),
      m_delBtn(new QPushButton(this)),
      m_signalFlag(true)
{
    switch (input) {
    case MouseType:
        m_xLabel->show();
        m_xLine->show();
        m_yLabel->show();
        m_yLine->show();
        m_keyLabel->hide();
        m_keyLine->hide();
        break;
    case KeyType:
        m_xLabel->hide();
        m_xLine->hide();
        m_yLabel->hide();
        m_yLine->hide();
        m_keyLabel->show();
        m_keyLine->show();
        break;
    default:
        break;
    }

    m_xLabel->setText(QObject::tr("x:"));
    m_yLabel->setText(QObject::tr("y:"));
    m_keyLabel->setText(QObject::tr("key:"));

    QHBoxLayout * lyt = new QHBoxLayout;
    lyt->setContentsMargins(16, 0, 16 ,0);
    lyt->setSpacing(8);
    lyt->addWidget(m_xLabel);
    lyt->addWidget(m_xLine);
    lyt->addWidget(m_yLabel);
    lyt->addWidget(m_yLine);
    lyt->addWidget(m_keyLabel);
    lyt->addWidget(m_keyLine);
    lyt->addWidget(m_delBtn);

    QIntValidator *xvalidator = new QIntValidator(0, INT_MAX, m_xLine);
    m_xLine->setValidator(xvalidator);

    QIntValidator *yvalidator = new QIntValidator(0, INT_MAX, m_yLine);
    m_yLine->setValidator(yvalidator);

    m_xLine->setFixedHeight(24);
    m_yLine->setFixedHeight(24);
    m_keyLine->setFixedHeight(24);

    connect(m_xLine, &InputLineedit::SigFocusOut, this, [=](){
        if(m_signalFlag)
            emit SigArgChanged(this->GetArg());
    });
    connect(m_yLine, &InputLineedit::SigFocusOut, this, [=](){
        if(m_signalFlag)
            emit SigArgChanged(this->GetArg());
    });
    connect(m_keyLine, &InputLineedit::textChanged, this, [=](){
        if(m_signalFlag)
            emit SigArgChanged(this->GetArg());
    });

    m_delBtn->setObjectName("delItemBtn");
    m_delBtn->setFixedSize(16, 16);
    connect(m_delBtn, &QPushButton::clicked, this, [=](){
        m_signalFlag = false;
        emit SigCurrentWidgetRemove();
    });

    this->setLayout(lyt);
}

void InputWidget::SetData(const ModelArg &key)
{
    m_signalFlag = false;
    switch (m_inputType) {
    case MouseType:
        m_xLine->setText(QString::number(key.x));
        m_yLine->setText(QString::number(key.y));
        break;
    case KeyType:
        m_keyLine->setText(key.showKeyWord);
        break;
    default:
        break;
    }
    m_signalFlag = true;
}

ModelArg InputWidget::GetArg()
{
    ModelArg returnArg;
    returnArg.x = m_xLine->text().toInt();
    returnArg.y = m_yLine->text().toInt();
    returnArg.showKeyWord = m_keyLine->text();
    returnArg.qKey = static_cast<Qt::Key>(m_keyLine->GetKey()) ;

    return returnArg;
}
