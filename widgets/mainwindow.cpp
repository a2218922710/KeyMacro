#include "mainwindow.h"

#include "GlobalMouseKey/globalkeyevent.h"
#include "services/comfunc.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QMetaEnum>
#include <QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
      m_keyBG(new QButtonGroup(this)),
      m_singleRBtn(new QRadioButton(this)),
      m_orderRBtn(new QRadioButton(this)),
      m_comRBtn(new QRadioButton(this)),
      m_addKeyBtn(new QPushButton(this)),
      m_clearKeyBtn(new QPushButton(this)),
      m_keyDelayLineEdit(new QLineEdit(this)),
      m_keyListView(new InputListView(KeyType, this)),
      m_mouseBG(new QButtonGroup(this)),
      m_clickRBtn(new QRadioButton(this)),
      m_doubleClickRBtn(new QRadioButton(this)),
      m_addMouseBtn(new QPushButton(this)),
      m_clearMouseBtn(new QPushButton(this)),
      m_mouseDelayLineEdit(new QLineEdit(this)),
      m_mouseListView(new InputListView(MouseType, this))
{
    m_keyBG->addButton(m_singleRBtn, 0);
    m_keyBG->addButton(m_orderRBtn, 1);
    m_keyBG->addButton(m_comRBtn, 2);

    m_mouseBG->addButton(m_clickRBtn, 0);
    m_mouseBG->addButton(m_doubleClickRBtn, 1);

    m_keyDelayLineEdit->setText(QString::number(300));
    QIntValidator *validator = new QIntValidator(0, INT_MAX, m_keyDelayLineEdit);
    m_keyDelayLineEdit->setValidator(validator);

    m_mouseDelayLineEdit->setText(QString::number(300));
    QIntValidator *mvalidator = new QIntValidator(0, INT_MAX, m_mouseDelayLineEdit);
    m_mouseDelayLineEdit->setValidator(mvalidator);

    m_addKeyBtn->setText(QObject::tr("Add key"));
    m_clearKeyBtn->setText(QObject::tr("Clear all key"));
    m_addMouseBtn->setText(QObject::tr("Add mouse"));
    m_clearMouseBtn->setText(QObject::tr("Clear all mouse"));

    connect(m_addKeyBtn, &QPushButton::clicked, this, [=](){
        m_keyListView->AddItem();
    });
    connect(m_addMouseBtn, &QPushButton::clicked, this, [=](){
        m_mouseListView->AddItem();
    });
    connect(m_clearKeyBtn, &QPushButton::clicked, this, [=](){
        m_keyListView->ClearItems();
    });
    connect(m_clearMouseBtn, &QPushButton::clicked, this, [=](){
        m_mouseListView->ClearItems();
    });


    //单按钮模式
    m_singleRBtn->setText(QObject::tr("Single mode, Only the first one takes effect"));
    m_singleRBtn->setChecked(true);
    QHBoxLayout * slyt = new QHBoxLayout;
    slyt->setMargin(0);
    slyt->setSpacing(8);
    slyt->addWidget(m_singleRBtn);
    slyt->addStretch();

    //顺序模式
    m_orderRBtn->setText(QObject::tr("Order mode, Sequential execution"));
    QHBoxLayout * olyt = new QHBoxLayout;
    olyt->setMargin(0);
    olyt->setSpacing(8);
    olyt->addWidget(m_orderRBtn);
    olyt->addStretch();

    //组合模式
    m_comRBtn->setText(QObject::tr("Concurrent mode, The keys are pressed simultaneously"));
    QHBoxLayout * clyt = new QHBoxLayout;
    clyt->setMargin(0);
    clyt->setSpacing(8);
    clyt->addWidget(m_comRBtn);
    clyt->addStretch();

    //增加按键item按钮区
    QHBoxLayout * blyt = new QHBoxLayout;
    QLabel * blb = new QLabel(this);
    blb->setFixedWidth(80);
    blb->setText(QObject::tr("Add keys"));
    blyt->setMargin(0);
    blyt->setSpacing(8);
    blyt->addWidget(blb);
    blyt->addWidget(m_addKeyBtn);
    blyt->addWidget(m_clearKeyBtn);
    blyt->addStretch();

    QHBoxLayout * dlyt = new QHBoxLayout;
    QLabel * dlb = new QLabel(this);
    dlb->setFixedWidth(80);
    dlb->setText(QObject::tr("Delay time"));
    dlyt->setMargin(0);
    dlyt->setSpacing(8);
    dlyt->addWidget(dlb);
    dlyt->addWidget(m_keyDelayLineEdit);
    dlyt->addStretch();


    //单击模式
    m_clickRBtn->setText(QObject::tr("Click mode"));
    m_clickRBtn->setChecked(true);
    QHBoxLayout * mclyt = new QHBoxLayout;
    mclyt->setMargin(0);
    mclyt->setSpacing(8);
    mclyt->addWidget(m_clickRBtn);
    mclyt->addStretch();

    //双击模式
    m_doubleClickRBtn->setText(QObject::tr("Double Click mode"));
    QHBoxLayout * mdlyt = new QHBoxLayout;
    mdlyt->setMargin(0);
    mdlyt->setSpacing(8);
    mdlyt->addWidget(m_doubleClickRBtn);
    mdlyt->addStretch();

    //增加按键item按钮区
    QHBoxLayout * mblyt = new QHBoxLayout;
    QLabel * mblb = new QLabel(this);
    mblb->setFixedWidth(80);
    mblb->setText(QObject::tr("Add mouse keys"));
    mblyt->setMargin(0);
    mblyt->setSpacing(8);
    mblyt->addWidget(mblb);
    mblyt->addWidget(m_addMouseBtn);
    mblyt->addWidget(m_clearMouseBtn);
    mblyt->addStretch();

    QHBoxLayout * mddlyt = new QHBoxLayout;
    QLabel * mddlb = new QLabel(this);
    mddlb->setFixedWidth(80);
    mddlb->setText(QObject::tr("Delay time"));
    mddlyt->setMargin(0);
    mddlyt->setSpacing(8);
    mddlyt->addWidget(mddlb);
    mddlyt->addWidget(m_mouseDelayLineEdit);
    mddlyt->addStretch();

    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Plain);
    QHBoxLayout * linelyt = new QHBoxLayout;
    linelyt->setContentsMargins(0, 16, 0, 16);
    linelyt->addWidget(line);

    QVBoxLayout * mainLyt = new QVBoxLayout;
    mainLyt->setMargin(32);
    mainLyt->setSpacing(8);
    mainLyt->addLayout(slyt);
    mainLyt->addLayout(olyt);
    mainLyt->addLayout(clyt);
    mainLyt->addLayout(dlyt);
    mainLyt->addLayout(blyt);
    mainLyt->addWidget(m_keyListView);

    mainLyt->addLayout(linelyt);

    mainLyt->addLayout(mclyt);
    mainLyt->addLayout(mdlyt);
    mainLyt->addLayout(mddlyt);
    mainLyt->addLayout(mblyt);
    mainLyt->addWidget(m_mouseListView);

    this->setLayout(mainLyt);

    connect(GlobalKeyEvent::getInstance(), &GlobalKeyEvent::keyEvent, this, &MainWindow::OnStarter);
    GlobalKeyEvent::installKeyEvent();
}

MainWindow::~MainWindow()
{
    GlobalKeyEvent::removeKeyEvent();
}

void MainWindow::OnStarter(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_F1:
        if(m_keyDelayLineEdit->text().isEmpty())
        {
            return;
        }
        ComFunc::getInstance()->StartKeyThread(m_keyListView->GetKeys(), m_keyBG->checkedId(), m_keyDelayLineEdit->text().toInt());
        break;
    case Qt::Key_F2:
        ComFunc::getInstance()->StopKeyThread();
        break;
    case Qt::Key_F5:
        if(m_mouseDelayLineEdit->text().isEmpty())
        {
            return;
        }
        ComFunc::getInstance()->StartMouseThread(m_mouseListView->GetMousePos(), m_mouseBG->checkedId(), m_mouseDelayLineEdit->text().toInt());
        break;
    case Qt::Key_F6:
        ComFunc::getInstance()->StopMouseThread();
        break;
    default:
        break;
    }

    delete event;
}
