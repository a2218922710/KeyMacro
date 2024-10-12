#include "inputlineedit.h"
#include "services/comfunc.h"

#include <QKeyEvent>
#include <QMetaEnum>

InputLineedit::InputLineedit(QWidget *parent)
    : QLineEdit(parent)
{
    setAttribute(Qt::WA_InputMethodEnabled, false);
}

void InputLineedit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() >= Qt::Key_F1 && e->key() <= Qt::Key_F35) {
        return;
    }
    QMetaEnum keyE = QMetaEnum::fromType<Qt::Key>();
    m_key = e->key();
    this->setText(keyE.valueToKey(e->key()));
}
