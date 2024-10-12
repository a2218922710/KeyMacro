#include "threadhandle.h"
#include "services/comfunc.h"

#include <QMutexLocker>
#include <QThread>

ThreadHandle::ThreadHandle(QObject * parent )
    : QObject(parent)
{

}

bool ThreadHandle::StartKeyThread(const QList<Qt::Key> &argList, int keyMode, int mesc)
{
    bool isHasKey = false;
    for(int i = 0; argList.size(); ++i) {
        isHasKey |= argList.at(i) != Qt::Key_unknown;
        if(isHasKey)
            break;
    }

    QThread * th = new QThread;
    moveToThread(th);
    connect(th, &QThread::started, this, [=](){
        m_keyFlag = true;
        startKeyThread(argList, keyMode, mesc);
    });
    connect(th, &QThread::finished, th, &QThread::deleteLater);
    connect(th, &QThread::finished, this, &ThreadHandle::deleteLater);
    th->start();

    return isHasKey;
}

bool ThreadHandle::StartMouseThread(const QList<QPoint> &posList, int clickMode, int mesc)
{
    if(posList.isEmpty())
        return false;

    QThread * th = new QThread;
    moveToThread(th);
    connect(th, &QThread::started, this, [=](){
        m_keyFlag = true;
        startMouseThread(posList, clickMode, mesc);
    });
    connect(th, &QThread::finished, th, &QThread::deleteLater);
    connect(th, &QThread::finished, this, &ThreadHandle::deleteLater);
    th->start();

    return true;
}

void ThreadHandle::StopThread()
{
    QMutexLocker locker(&m_mutex);
    m_keyFlag = false;
}

void ThreadHandle::startKeyThread(const QList<Qt::Key> &argList, int keyMode, int mesc)
{
    if(argList.size() == 0)
        return;

    while (m_keyFlag) {
        LKey_CODE vkCode = LKey_UNKNOWN;
        switch (keyMode) {
        case 0:
            vkCode = ComFunc::getInstance()->MapKeyToVkCode(argList.at(0));
            if(LKey_UNKNOWN == vkCode)
                return;
            keybd_event(vkCode, 0, 0, 0);
            QThread::msleep(mesc);
            break;
        case 1:
            for(int i = 0; i < argList.size() && m_keyFlag; ++i)
            {
                vkCode = ComFunc::getInstance()->MapKeyToVkCode(argList.at(i));
                if(LKey_UNKNOWN == vkCode)
                    continue;
                keybd_event(vkCode, 0, 0, 0);
                QThread::msleep(mesc);
            }
            break;
        case 2:
            for(int i = 0; i < argList.size() && m_keyFlag; ++i)
            {
                vkCode = ComFunc::getInstance()->MapKeyToVkCode(argList.at(i));
                if(LKey_UNKNOWN == vkCode)
                    continue;
                keybd_event(vkCode, 0, 0, 0);
            }
            QThread::msleep(mesc);
            break;
        default:
            return;
        }
    }
}

void ThreadHandle::startMouseThread(const QList<QPoint> &posList, int clickMode, int mesc)
{
    if(posList.isEmpty())
        return;
    while (m_keyFlag) {
        for(int i = 0; i < posList.size() && m_keyFlag; ++i)
        {
            QPoint tmpPos = posList.at(i);
            if(0 > tmpPos.x() || 0 > tmpPos.y())
                continue;
            ComFunc::getInstance()->DoPressAct(tmpPos.x(), tmpPos.y(), clickMode);
            QThread::msleep(mesc);
        }
    }
}
