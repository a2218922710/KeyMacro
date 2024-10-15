#include "dialogtitle.h"

#include <QApplication>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QHBoxLayout>

DialogTitle::DialogTitle(QWidget * parent, bool isHelpShow)
    : QWidget(parent),
      m_dialog(parent),
      m_closeBtn(new CBtn(this)),
      m_helpBtn(new CBtn(this))
{
    if(!isHelpShow)
        m_helpBtn->hide();

    m_closeBtn->setObjectName("closeBtn");
    m_closeBtn->setFixedSize(24, 24);
    connect(m_closeBtn, &QPushButton::clicked, this, &DialogTitle::SigClose);

    m_helpBtn->setObjectName("helpBtn");
    m_helpBtn->setFixedSize(24, 24);
    connect(m_helpBtn, &QPushButton::clicked, this, &DialogTitle::SigHelp);

    QHBoxLayout * mainlyt = new QHBoxLayout;
    mainlyt->setMargin(0);
    mainlyt->setSpacing(0);
    mainlyt->addStretch();
    mainlyt->addWidget(m_helpBtn);
    mainlyt->addWidget(m_closeBtn);

    this->setLayout(mainlyt);
    this->setFixedHeight(24);
}

void DialogTitle::mouseMoveEvent(QMouseEvent *event)
{
    int screen_count = QApplication::desktop()->screenCount();
    int prim_screen = QApplication::desktop()->primaryScreen();
    QRect desktopR;

    if(screen_count>1)
    {
        desktopR = QApplication::desktop()->screenGeometry(prim_screen+(screen_count-1));
    }else{
        desktopR = QApplication::desktop()->availableGeometry();
    }

    int nDefaultW = this->width();
    int nDefaultH = this->height();

    int x = QPoint(event->globalPos() - m_mouse_move_len).x();
    int y = QPoint(event->globalPos() - m_mouse_move_len).y();

    if(x < 0)
    {
        return;
    }
    if(y < 0)
    {
        return;
    }
    if(x > desktopR.right() - nDefaultW)
    {
        return;
    }
    if(y > desktopR.bottom() - nDefaultH)
    {
        return;
    }
    m_dialog->move(m_dialog->pos() + (event->pos() - m_mouse_move_len));
}

void DialogTitle::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_dialog)
    {
        m_mouse_is_press = true;
        m_mouse_move_len = event->pos();
    }
}

void DialogTitle::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_mouse_is_press = false;
    }
}
