#ifndef INPUTLINEEDIT_H
#define INPUTLINEEDIT_H

#include <QLineEdit>

class InputLineedit : public QLineEdit
{
    Q_OBJECT
public:
    InputLineedit(QWidget * parent = nullptr);

    int GetKey()    { return m_key; }
protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    int     m_key;
};

#endif // INPUTLINEEDIT_H
