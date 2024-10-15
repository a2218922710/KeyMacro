#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inputlistview.h"
#include "dialogtitle.h"

#include <QDialog>
#include <QRadioButton>

class MainWindow : public QDialog
{
    Q_OBJECT
public:
    MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

private slots:
    void OnStarter(QKeyEvent* event);

private:
    QButtonGroup      *    m_keyBG;
    QRadioButton      *    m_singleRBtn;
    QRadioButton      *    m_orderRBtn;
    QRadioButton      *    m_comRBtn;
    QPushButton       *    m_addKeyBtn;
    QPushButton       *    m_clearKeyBtn;
    QLineEdit         *    m_keyDelayLineEdit;
    InputListView     *    m_keyListView;

    QButtonGroup      *    m_mouseBG;
    QRadioButton      *    m_clickRBtn;
    QRadioButton      *    m_doubleClickRBtn;
    QPushButton       *    m_addMouseBtn;
    QPushButton       *    m_clearMouseBtn;
    QLineEdit         *    m_mouseDelayLineEdit;
    InputListView     *    m_mouseListView;
    bool m_test = false;

    QWidget           *    m_centerWidget;
    DialogTitle       *    m_dialogTitle;
};

#endif // MAINWINDOW_H
