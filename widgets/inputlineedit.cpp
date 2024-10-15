#include "inputlineedit.h"
#include "services/comfunc.h"

#include <QKeyEvent>
#include <QMetaEnum>

InputLineedit::InputLineedit(InputType inputType, QWidget *parent)
    : QLineEdit(parent),
      m_inputType(inputType)
{
    setAttribute(Qt::WA_InputMethodEnabled, false);
}

void InputLineedit::keyPressEvent(QKeyEvent *e)
{
    if(MouseType == m_inputType)
    {
        return QLineEdit::keyPressEvent(e);
    }
    if(e->key() >= Qt::Key_F1 && e->key() <= Qt::Key_F35) {
        return;
    }
    QMetaEnum keyE = QMetaEnum::fromType<Qt::Key>();
    m_key = e->key();
    this->setText(keyE.valueToKey(e->key()));
}

void InputLineedit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    emit SigFocusOut();
}
