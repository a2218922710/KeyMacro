#ifndef INPUTLINEEDIT_H
#define INPUTLINEEDIT_H

#include "services/defines.h"

#include <QLineEdit>

class InputLineedit : public QLineEdit
{
    Q_OBJECT
public:
    InputLineedit(InputType inputType = MouseType, QWidget * parent = nullptr);

    int GetKey()    { return m_key; }

Q_SIGNALS:
    void SigFocusOut();

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    int             m_key;
    InputType       m_inputType;
};

#endif // INPUTLINEEDIT_H
