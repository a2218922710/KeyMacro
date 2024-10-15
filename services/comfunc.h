#ifndef COMFUNC_H
#define COMFUNC_H

#include "defines.h"

#include "threadhandle.h"


class ComFunc : public QObject
{
public:
    // 获取单例实例
    static ComFunc* getInstance()
    {
        QMutexLocker locker(&mutex); // 使用互斥锁确保线程安全
        if (!instance) {
            instance = new ComFunc();
        }
        return instance;
    }

    // 释放单例实例
    static void releaseInstance()
    {
        QMutexLocker locker(&mutex); // 使用互斥锁确保线程安全
        delete instance;
        instance = nullptr;
    }

    bool StartKeyThread(const QList<Qt::Key>& keyList, int keyMode, int msec);
    void StopKeyThread();

    bool StartMouseThread(const QList<QPoint> &posList, int clickMode, int msec);
    void StopMouseThread();

    void SetWidgetShadow(QWidget * widget);

    // 鼠标点击
    void DoPressAct(int x, int y, int type_id);

    LKey_CODE MapKeyToVkCode(Qt::Key keyCode);



private:
    ComFunc();
    // 析构函数
    ~ComFunc()
    {

    }

    static ComFunc* instance; // 静态成员变量用于存储单例实例
    static QMutex mutex; // 互斥锁用于线程安全

    ThreadHandle * m_keyThread = nullptr;
    ThreadHandle * m_mouseThread = nullptr;
};




#endif // COMFUNC_H
