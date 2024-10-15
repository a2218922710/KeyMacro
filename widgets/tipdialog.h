#ifndef TIPDIALOG_H
#define TIPDIALOG_H

#include "dialogtitle.h"

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class TipDialog : public QDialog
{
    Q_OBJECT
public:
    TipDialog(QWidget * parent = nullptr);
    void SetText(const QString & text);

private:
    DialogTitle * m_title;
    QWidget     * m_center;
    QLabel      * m_label;
    QPushButton * m_okBtn;
};

#endif // TIPDIALOG_H
