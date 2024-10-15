#include "mainwindow.h"

#include "GlobalMouseKey/globalkeyevent.h"
#include "services/comfunc.h"
#include "tipdialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QMetaEnum>
#include <QButtonGroup>
#include <QGraphicsDropShadowEffect>

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
      m_mouseListView(new InputListView(MouseType, this)),
      m_centerWidget(new QWidget(this)),
      m_dialogTitle(new DialogTitle(this, true))
{
    m_keyBG->addButton(m_singleRBtn, 0);
    m_keyBG->addButton(m_orderRBtn, 1);
    m_keyBG->addButton(m_comRBtn, 2);

    m_mouseBG->addButton(m_clickRBtn, 0);
    m_mouseBG->addButton(m_doubleClickRBtn, 1);

    m_keyDelayLineEdit->setFixedWidth(60);
    m_keyDelayLineEdit->setText(QString::number(300));
    QIntValidator *validator = new QIntValidator(0, INT_MAX, m_keyDelayLineEdit);
    m_keyDelayLineEdit->setValidator(validator);

    m_mouseDelayLineEdit->setFixedWidth(60);
    m_mouseDelayLineEdit->setText(QString::number(300));
    QIntValidator *mvalidator = new QIntValidator(0, INT_MAX, m_mouseDelayLineEdit);
    m_mouseDelayLineEdit->setValidator(mvalidator);

    m_addKeyBtn->setObjectName("addKeyBtn");
    m_clearKeyBtn->setObjectName("clearKeyBtn");
    m_addMouseBtn->setObjectName("addMouseBtn");
    m_clearMouseBtn->setObjectName("clearMouseBtn");

    m_addKeyBtn->setText(QObject::tr("Add key"));
    m_clearKeyBtn->setText(QObject::tr("Clear all key"));
    m_addMouseBtn->setText(QObject::tr("Add mouse"));
    m_clearMouseBtn->setText(QObject::tr("Clear all mouse"));

    m_keyListView->setMaximumHeight(92);
    m_mouseListView->setMaximumHeight(92);

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
    connect(m_dialogTitle, &DialogTitle::SigClose, this, &MainWindow::close);
    connect(m_dialogTitle, &DialogTitle::SigHelp, this, [=](){
        TipDialog tip(this);
        QString text;
        text.append(QObject::tr("Instructions:"
"F1F2,F5F6"
"Bug moremore.please check,"
"This open source tool is developed by \"Haibuying\", "
"any questions can contact QQ: 2218922710, use at your own risk, no guarantee, "
"comply with the terms of the license. "
"Haibuying shall not be liable for any damage caused by its use. "
"\n"
"Prohibited for commercial use. "
"\n"
"source address https://github.com/a2218922710/KeyMacro"));
        tip.SetText(text);
        tip.setFixedSize(430, 482);
        tip.exec();
    });

    connect(GlobalKeyEvent::getInstance(), &GlobalKeyEvent::keyEvent, this, &MainWindow::OnStarter);
    GlobalKeyEvent::installKeyEvent();


    //单按钮模式
    m_singleRBtn->setText(QObject::tr("Single mode, Only the first one takes effect"));
    m_singleRBtn->setChecked(true);
    QHBoxLayout * slyt = new QHBoxLayout;
    slyt->setMargin(0);
    slyt->setSpacing(6);
    slyt->addWidget(m_singleRBtn);
    slyt->addStretch();

    //顺序模式
    m_orderRBtn->setText(QObject::tr("Order mode, Sequential execution"));
    QHBoxLayout * olyt = new QHBoxLayout;
    olyt->setMargin(0);
    olyt->setSpacing(6);
    olyt->addWidget(m_orderRBtn);
    olyt->addStretch();

    //组合模式
    m_comRBtn->setText(QObject::tr("Concurrent mode, The keys are pressed simultaneously"));
    QHBoxLayout * clyt = new QHBoxLayout;
    clyt->setMargin(0);
    clyt->setSpacing(6);
    clyt->addWidget(m_comRBtn);
    clyt->addStretch();

    //增加按键item按钮区
    QHBoxLayout * blyt = new QHBoxLayout;
    QLabel * blb = new QLabel(this);
    blb->setText(QObject::tr("Add keys"));
    blyt->setMargin(0);
    blyt->setSpacing(6);
    blyt->addWidget(blb);
    blyt->addStretch();
    blyt->addWidget(m_addKeyBtn);
    blyt->addWidget(m_clearKeyBtn);

    QHBoxLayout * dlyt = new QHBoxLayout;
    QLabel * dlb = new QLabel(this);
    dlb->setText(QObject::tr("Delay time"));
    dlyt->setMargin(0);
    dlyt->setSpacing(6);
    dlyt->addWidget(dlb);
    dlyt->addStretch();
    dlyt->addWidget(m_keyDelayLineEdit);

    //单击模式
    m_clickRBtn->setText(QObject::tr("Click mode"));
    m_clickRBtn->setChecked(true);
    QHBoxLayout * mclyt = new QHBoxLayout;
    mclyt->setMargin(0);
    mclyt->setSpacing(6);
    mclyt->addWidget(m_clickRBtn);
    mclyt->addStretch();

    //双击模式
    m_doubleClickRBtn->setText(QObject::tr("Double Click mode"));
    QHBoxLayout * mdlyt = new QHBoxLayout;
    mdlyt->setMargin(0);
    mdlyt->setSpacing(6);
    mdlyt->addWidget(m_doubleClickRBtn);
    mdlyt->addStretch();

    //增加按键item按钮区
    QHBoxLayout * mblyt = new QHBoxLayout;
    QLabel * mblb = new QLabel(this);
    mblb->setText(QObject::tr("Add mouse keys"));
    mblyt->setMargin(0);
    mblyt->setSpacing(6);
    mblyt->addWidget(mblb);
    mblyt->addStretch();
    mblyt->addWidget(m_addMouseBtn);
    mblyt->addWidget(m_clearMouseBtn);

    QHBoxLayout * mddlyt = new QHBoxLayout;
    QLabel * mddlb = new QLabel(this);
    mddlb->setText(QObject::tr("Delay time"));
    mddlyt->setMargin(0);
    mddlyt->setSpacing(6);
    mddlyt->addWidget(mddlb);
    mddlyt->addStretch();
    mddlyt->addWidget(m_mouseDelayLineEdit);

    QLabel *line = new QLabel(this);
    line->setObjectName("line");
    line->setFixedHeight(1);
    QHBoxLayout * linelyt = new QHBoxLayout;
    linelyt->setContentsMargins(0, 8, 0, 8);
    linelyt->addWidget(line);

    QLabel * kl = new QLabel(this);
    kl->setWordWrap(true);
    kl->setText(QObject::tr("F1 start, F2 stop(without F1-F12)"));

    QLabel * ml = new QLabel(this);
    ml->setWordWrap(true);
    ml->setText(QObject::tr("F5 start, F6 stop"));

    QVBoxLayout * mainLyt = new QVBoxLayout;
    mainLyt->setContentsMargins(32, 8, 32, 32);
    mainLyt->setSpacing(6);
    mainLyt->addWidget(kl);
    mainLyt->addLayout(slyt);
    mainLyt->addLayout(olyt);
    mainLyt->addLayout(clyt);
    mainLyt->addLayout(dlyt);
    mainLyt->addLayout(blyt);
    mainLyt->addWidget(m_keyListView);
    mainLyt->addLayout(linelyt);
    mainLyt->addWidget(ml);
    mainLyt->addLayout(mclyt);
    mainLyt->addLayout(mdlyt);
    mainLyt->addLayout(mddlyt);
    mainLyt->addLayout(mblyt);
    mainLyt->addWidget(m_mouseListView);
    mainLyt->addStretch();

    QWidget * tmpWidget = new QWidget(this);
    tmpWidget->setLayout(mainLyt);

    QVBoxLayout * mainWidgetlyt = new QVBoxLayout;
    mainWidgetlyt->setMargin(0);
    mainWidgetlyt->addWidget(m_dialogTitle);
    mainWidgetlyt->addWidget(tmpWidget);

    m_centerWidget->setObjectName("mainWidget");
    m_centerWidget->setLayout(mainWidgetlyt);

    QVBoxLayout * flyt = new QVBoxLayout;
    flyt->setMargin(20);
    flyt->addWidget(m_centerWidget);

    this->setLayout(flyt);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowSystemMenuHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(350, 602);

    ComFunc::getInstance()->SetWidgetShadow(m_centerWidget);
}

MainWindow::~MainWindow()
{
    GlobalKeyEvent::removeKeyEvent();
}

void MainWindow::OnStarter(QKeyEvent* event)
{
    if(event->type() == QEvent::KeyRelease)
    {
        switch (event->key()) {
        case Qt::Key_F1:
            if(m_keyDelayLineEdit->text().isEmpty())
            {
                TipDialog tip(this);
                tip.SetText(QObject::tr("Please check the delay parameters"));
                tip.setFixedSize(250, 146);
                tip.exec();
                return;
            }
            if(!ComFunc::getInstance()->StartKeyThread(m_keyListView->GetKeys(), m_keyBG->checkedId(), m_keyDelayLineEdit->text().toInt()))
            {
                TipDialog tip(this);
                tip.SetText(QObject::tr("Please add key parameters"));
                tip.setFixedSize(250, 146);
                tip.exec();
            }
            break;
        case Qt::Key_F2:
            ComFunc::getInstance()->StopKeyThread();
            break;
        case Qt::Key_F5:
            if(m_mouseDelayLineEdit->text().isEmpty())
            {
                TipDialog tip(this);
                tip.SetText(QObject::tr("Please check the delay parameters"));
                tip.setFixedSize(250, 146);
                tip.exec();
                return;
            }
            if(!ComFunc::getInstance()->StartMouseThread(m_mouseListView->GetMousePos(), m_mouseBG->checkedId(), m_mouseDelayLineEdit->text().toInt()))
            {
                TipDialog tip(this);
                tip.SetText(QObject::tr("Please add mouse coordinate parameters"));
                tip.setFixedSize(250, 146);
                tip.exec();
            }
            break;
        case Qt::Key_F6:
            ComFunc::getInstance()->StopMouseThread();
            break;
        default:
            break;
        }
    }

    delete event;
}
