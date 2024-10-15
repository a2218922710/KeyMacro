#ifndef DIALOGTITLE_H
#define DIALOGTITLE_H

#include <QWidget>
#include <QPushButton>

class CBtn;
class DialogTitle : public QWidget
{
    Q_OBJECT
public:
    DialogTitle(QWidget * parent, bool isHelpShow = false);

Q_SIGNALS:
    void SigClose();
    void SigHelp();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QWidget * m_dialog;
    bool    m_mouse_is_press = false;
    QPoint  m_mouse_move_len;
    QPoint  m_mouseStartPoint;

    CBtn    * m_closeBtn;
    CBtn    * m_helpBtn;
};

class CBtn : public QPushButton
{
    Q_OBJECT
public:
    CBtn(QWidget * parent = nullptr) : QPushButton(parent) {}
protected:
    void mouseMoveEvent(QMouseEvent *event) override { Q_UNUSED(event);  return; }
};

#endif // DIALOGTITLE_H
