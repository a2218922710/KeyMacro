#include "comfunc.h"

#include <QGraphicsDropShadowEffect>
#include <QWidget>
// 初始化静态成员变量
ComFunc* ComFunc::instance = nullptr;
QMutex ComFunc::mutex;

ComFunc::ComFunc()
{

}

bool ComFunc::StartKeyThread(const QList<Qt::Key>& keyList, int keyMode, int msec)
{
    if(m_keyThread) {
        StopKeyThread();
    }
    m_keyThread = new ThreadHandle;
    return m_keyThread->StartKeyThread(keyList, keyMode, msec);
}

void ComFunc::StopKeyThread()
{
    if(!m_keyThread)
        return;
    m_keyThread->StopThread();
}

bool ComFunc::StartMouseThread(const QList<QPoint> &posList, int clickMode, int msec)
{
    if(m_mouseThread) {
        StopMouseThread();
    }
    m_mouseThread = new ThreadHandle;
    return m_mouseThread->StartMouseThread(posList, clickMode, msec);
}

void ComFunc::StopMouseThread()
{
    if(!m_mouseThread)
        return;
    m_mouseThread->StopThread();
}

void ComFunc::SetWidgetShadow(QWidget *widget)
{
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setOffset(0, 8);
    shadow->setColor(QColor(0,0,0,76));
    shadow->setBlurRadius(26);
    widget->setGraphicsEffect(shadow);
}

void ComFunc::DoPressAct(int x, int y, int type_id)
{
    SetCursorPos(x,y);
    if(type_id==0)
    {//鼠标单击一下左键
        mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,x, y, 0, 0);
        mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,x, y, 0, 0);
    }
    else if(type_id==1)
    {//鼠标双击左键
        mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,x, y, 0, 0);
        mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,x, y, 0, 0);
        mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,x, y, 0, 0);
        mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,x, y, 0, 0);
    }
}

LKey_CODE ComFunc::MapKeyToVkCode(Qt::Key keyCode)
{
    switch (keyCode) {
        case Qt::Key_Escape: return LKey_ESCAPE;
        case Qt::Key_1: return LKey_1;
        case Qt::Key_2: return LKey_2;
        case Qt::Key_3: return LKey_3;
        case Qt::Key_4: return LKey_4;
        case Qt::Key_5: return LKey_5;
        case Qt::Key_6: return LKey_6;
        case Qt::Key_7: return LKey_7;
        case Qt::Key_8: return LKey_8;
        case Qt::Key_9: return LKey_9;
        case Qt::Key_0: return LKey_0;
        case Qt::Key_Minus: return LKey_MINUS;
        case Qt::Key_Backspace: return LKey_BACK;
        case Qt::Key_Tab: return LKey_TAB;
        case Qt::Key_Q: return LKey_Q;
        case Qt::Key_W: return LKey_W;
        case Qt::Key_E: return LKey_E;
        case Qt::Key_R: return LKey_R;
        case Qt::Key_T: return LKey_T;
        case Qt::Key_Y: return LKey_Y;
        case Qt::Key_U: return LKey_U;
        case Qt::Key_I: return LKey_I;
        case Qt::Key_O: return LKey_O;
        case Qt::Key_P: return LKey_P;
        case Qt::Key_BracketLeft: return LKey_LEFT_BRACKET;
        case Qt::Key_BracketRight: return LKey_RIGHT_BRACKET;
        case Qt::Key_Return: return LKey_RETURN;
        case Qt::Key_Control: return LKey_LCONTROL;
        case Qt::Key_A: return LKey_A;
        case Qt::Key_S: return LKey_S;
        case Qt::Key_D: return LKey_D;
        case Qt::Key_F: return LKey_F;
        case Qt::Key_G: return LKey_G;
        case Qt::Key_H: return LKey_H;
        case Qt::Key_J: return LKey_J;
        case Qt::Key_K: return LKey_K;
        case Qt::Key_L: return LKey_L;
        case Qt::Key_Semicolon: return LKey_SEMICOLON;
        case Qt::Key_Apostrophe: return LKey_APOSTROPHE;
        case Qt::Key_Shift: return LKey_LSHIFT;
        case Qt::Key_Backslash: return LKey_BACKSLASH;
        case Qt::Key_Z: return LKey_Z;
        case Qt::Key_X: return LKey_X;
        case Qt::Key_C: return LKey_C;
        case Qt::Key_V: return LKey_V;
        case Qt::Key_B: return LKey_B;
        case Qt::Key_N: return LKey_N;
        case Qt::Key_M: return LKey_M;
        case Qt::Key_Comma: return LKey_COMMA;
        case Qt::Key_Period: return LKey_PERIOD;
        case Qt::Key_Slash: return LKey_SLASH;
        case Qt::Key_Asterisk: return LKey_MULTIPLY;
        case Qt::Key_Alt: return LKey_LMENU;
        case Qt::Key_Space: return LKey_SPACE;
        case Qt::Key_CapsLock: return LKey_CAPITAL;
        case Qt::Key_F1: return LKey_F1;
        case Qt::Key_F2: return LKey_F2;
        case Qt::Key_F3: return LKey_F3;
        case Qt::Key_F4: return LKey_F4;
        case Qt::Key_F5: return LKey_F5;
        case Qt::Key_F6: return LKey_F6;
        case Qt::Key_F7: return LKey_F7;
        case Qt::Key_F8: return LKey_F8;
        case Qt::Key_F9: return LKey_F9;
        case Qt::Key_F10: return LKey_F10;
        case Qt::Key_NumLock: return LKey_NUMLOCK;
        case Qt::Key_ScrollLock: return LKey_SCROLL;
        case Qt::Key_F11: return LKey_F11;
        case Qt::Key_F12: return LKey_F12;
        case Qt::Key_Print: return LKey_PRINT;
        case Qt::Key_Insert: return LKey_INSERT;
        case Qt::Key_Home: return LKey_HOME;
        case Qt::Key_Up: return LKey_UP;
        case Qt::Key_PageUp: return LKey_PRIOR;
        case Qt::Key_Delete: return LKey_DELETE;
        case Qt::Key_End: return LKey_END;
        case Qt::Key_PageDown: return LKey_NEXT;
        case Qt::Key_Left: return LKey_LEFT;
        case Qt::Key_Down: return LKey_DOWN;
        case Qt::Key_Right: return LKey_RIGHT;
        case Qt::Key_Sleep: return LKey_SLEEP;
        case Qt::Key_VolumeMute: return LKey_VOLUME_MUTE;
        case Qt::Key_VolumeDown: return LKey_VOLUME_DOWN;
        case Qt::Key_VolumeUp: return LKey_VOLUME_UP;
        case Qt::Key_MediaNext: return LKey_MEDIA_NEXT_TRACK;
        case Qt::Key_MediaPrevious: return LKey_MEDIA_PREV_TRACK;
        case Qt::Key_MediaStop: return LKey_MEDIA_STOP;
        case Qt::Key_MediaPlay: return LKey_MEDIA_PLAY_PAUSE;
        case Qt::Key_LaunchMail: return LKey_LAUNCH_MAIL;
        case Qt::Key_LaunchMedia: return LKey_LAUNCH_MEDIA_SELECT;
        default: return LKey_UNKNOWN;
    }
}
