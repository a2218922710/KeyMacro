#include "tipdialog.h"

#include "services/comfunc.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#define TEXTBEGIN QString("<p style='line-height:%1px; width:100% ; white-space: pre-wrap; '>").arg(20)
#define TEXTEND   QString("</p>")

TipDialog::TipDialog(QWidget *parent)
    : QDialog(parent),
      m_title(new DialogTitle(this)),
      m_center(new QWidget(this)),
      m_label(new QLabel(this)),
      m_okBtn(new QPushButton(this))
{
    m_okBtn->setText("OK");
    m_okBtn->setObjectName("okBtn");
    m_okBtn->setFixedSize(54, 24);
    connect(m_okBtn, &QPushButton::clicked, this, &TipDialog::close);
    connect(m_title, &DialogTitle::SigClose, this, &TipDialog::close);

    m_center->setObjectName("centerWidget");

    m_label->setWordWrap(true);

    QHBoxLayout * blyt = new QHBoxLayout;
    blyt->addStretch();
    blyt->setMargin(0);
    blyt->addWidget(m_okBtn);

    QVBoxLayout * vlyt = new QVBoxLayout;
    vlyt->setContentsMargins(16, 8, 16, 16);
    vlyt->setSpacing(8);
    vlyt->addWidget(m_label);
    vlyt->addLayout(blyt);

    QVBoxLayout * alyt = new QVBoxLayout;
    alyt->setMargin(0);
    alyt->addWidget(m_title);
    alyt->addLayout(vlyt);

    m_center->setLayout(alyt);

    QVBoxLayout * mlyt = new QVBoxLayout;
    mlyt->setMargin(20);
    mlyt->addWidget(m_center);

    this->setLayout(mlyt);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowSystemMenuHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    ComFunc::getInstance()->SetWidgetShadow(m_center);
}

void TipDialog::SetText(const QString &text)
{
    QString tmpT = TEXTBEGIN + text + TEXTEND;
    m_label->setText(tmpT);
}
