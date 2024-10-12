#ifndef THREADHANDLE_H
#define THREADHANDLE_H

#include "services/defines.h"

#include <QObject>
#include <QMutex>

class ThreadHandle : public QObject
{
    Q_OBJECT
public:
    ThreadHandle(QObject * parent = nullptr);

    bool StartKeyThread(const QList<Qt::Key> & argList, int keyMode, int mesc);
    bool StartMouseThread(const QList<QPoint> & posList, int clickMode, int mesc);

    void StopThread();

private:
    void startKeyThread(const QList<Qt::Key> & argList, int keyMode, int mesc);
    void startMouseThread(const QList<QPoint> & posList, int clickMode, int mesc);

private:
    bool    m_keyFlag = true;
    bool    m_mouseFlag = true;
    QMutex  m_mutex;
};

#endif // THREADHANDLE_H
