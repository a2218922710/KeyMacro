#ifndef DEFINES_H
#define DEFINES_H

#include <QString>
#include <QMetaType>
#include <QKeyEvent>
#include <Windows.h>


enum InputType {
    KeyType,    //按键
    MouseType   //鼠标坐标
};

struct ModelArg{
    int x;
    int y;
    QString     showKeyWord;

    Qt::Key     qKey;

    ModelArg() :x(0), y(0), qKey(Qt::Key_unknown) {}
};

Q_DECLARE_METATYPE(ModelArg)

enum LKey_CODE {
    LKey_ESCAPE = 0x1B,
    LKey_1 = 0x31,
    LKey_2 = 0x32,
    LKey_3 = 0x33,
    LKey_4 = 0x34,
    LKey_5 = 0x35,
    LKey_6 = 0x36,
    LKey_7 = 0x37,
    LKey_8 = 0x38,
    LKey_9 = 0x39,
    LKey_0 = 0x30,
    LKey_MINUS = 0xBD, // `-` 和 `_`
    LKey_EQUALS = 0xBB, // `=` 和 `+`
    LKey_BACK = 0x08, // Backspace
    LKey_TAB = 0x09,
    LKey_Q = 0x51,
    LKey_W = 0x57,
    LKey_E = 0x45,
    LKey_R = 0x52,
    LKey_T = 0x54,
    LKey_Y = 0x59,
    LKey_U = 0x55,
    LKey_I = 0x49,
    LKey_O = 0x4F,
    LKey_P = 0x50,
    LKey_LEFT_BRACKET = 0xDB, // `[` 和 `{`
    LKey_RIGHT_BRACKET = 0xDD, // `]` 和 `}`
    LKey_RETURN = 0x0D, // Enter
    LKey_LCONTROL = 0xA2,
    LKey_A = 0x41,
    LKey_S = 0x53,
    LKey_D = 0x44,
    LKey_F = 0x46,
    LKey_G = 0x47,
    LKey_H = 0x48,
    LKey_J = 0x4A,
    LKey_K = 0x4B,
    LKey_L = 0x4C,
    LKey_SEMICOLON = 0xBA, // `;` 和 `:`
    LKey_APOSTROPHE = 0xDE, // `'` 和 `"`
    LKey_GRAVE = 0xC0, // `~` 和 ``
    LKey_LSHIFT = 0xA0, // 左 Shift
    LKey_BACKSLASH = 0xDC, // `\` 和 `|`
    LKey_Z = 0x5A,
    LKey_X = 0x58,
    LKey_C = 0x43,
    LKey_V = 0x56,
    LKey_B = 0x42,
    LKey_N = 0x4E,
    LKey_M = 0x4D,
    LKey_COMMA = 0xBC, // `,` 和 `<`
    LKey_PERIOD = 0xBE, // `.` 和 `>`
    LKey_SLASH = 0xBF, // `/` 和 `?`
    LKey_RSHIFT = 0xA1, // 右 Shift
    LKey_MULTIPLY = 0x6A, // NumPad *
    LKey_LMENU = 0xA4, // 左 Alt
    LKey_SPACE = 0x20,
    LKey_CAPITAL = 0x3A, // Caps Lock
    LKey_F1 = 0x70,
    LKey_F2 = 0x71,
    LKey_F3 = 0x72,
    LKey_F4 = 0x73,
    LKey_F5 = 0x74,
    LKey_F6 = 0x75,
    LKey_F7 = 0x76,
    LKey_F8 = 0x77,
    LKey_F9 = 0x78,
    LKey_F10 = 0x79,
    LKey_NUMLOCK = 0x90, // Num Lock
    LKey_SCROLL = 0x91, // Scroll Lock
    LKey_NUMPAD7 = 0x67,
    LKey_NUMPAD8 = 0x68,
    LKey_NUMPAD9 = 0x69,
    LKey_SUBTRACT = 0x6D, // NumPad -
    LKey_NUMPAD4 = 0x6B,
    LKey_NUMPAD5 = 0x6C,
    LKey_NUMPAD6 = 0x6B,
    LKey_ADD = 0x6B, // NumPad +
    LKey_NUMPAD1 = 0x61,
    LKey_NUMPAD2 = 0x62,
    LKey_NUMPAD3 = 0x63,
    LKey_NUMPAD0 = 0x60,
    LKey_DECIMAL = 0x6E, // NumPad .
    LKey_F11 = 0x7C,
    LKey_F12 = 0x7D,
    LKey_PRINT = 0x2A, // Print Screen
    LKey_INSERT = 0x2D, // Insert
    LKey_HOME = 0x24, // Home
    LKey_UP = 0x26, // Up Arrow
    LKey_PRIOR = 0x21, // Page Up
    LKey_DELETE = 0x2E, // Delete
    LKey_END = 0x23, // End
    LKey_NEXT = 0x22, // Page Down
    LKey_LEFT = 0x25, // Left Arrow
    LKey_DOWN = 0x28, // Down Arrow
    LKey_RIGHT = 0x27, // Right Arrow
    LKey_DIVIDE = 0x6F, // NumPad /
    LKey_LWIN = 0x5B, // Left Windows Key
    LKey_RWIN = 0x5C, // Right Windows Key
    LKey_APPS = 0x5D, // Application Key
    LKey_POWER = 0x93, // Power Key
    LKey_SLEEP = 0x5F, // Sleep Key
    LKey_BROWSER_BACK = 0xA6, // Browser Back Key
    LKey_BROWSER_FORWARD = 0xA7, // Browser Forward Key
    LKey_BROWSER_REFRESH = 0xA8, // Browser Refresh Key
    LKey_BROWSER_STOP = 0xA9, // Browser Stop Key
    LKey_BROWSER_SEARCH = 0xAA, // Browser Search Key
    LKey_BROWSER_FAVORITES = 0xAB, // Browser Favorites Key
    LKey_BROWSER_HOME = 0xAC, // Browser Home Key
    LKey_VOLUME_MUTE = 0xAD, // Volume Mute Key
    LKey_VOLUME_DOWN = 0xAE, // Volume Down Key
    LKey_VOLUME_UP = 0xAF, // Volume Up Key
    LKey_MEDIA_NEXT_TRACK = 0xB0, // Media Next Track Key
    LKey_MEDIA_PREV_TRACK = 0xB1, // Media Previous Track Key
    LKey_MEDIA_STOP = 0xB2, // Media Stop Key
    LKey_MEDIA_PLAY_PAUSE = 0xB3, // Media Play/Pause Key
    LKey_LAUNCH_MAIL = 0xB4, // Launch Mail Key
    LKey_LAUNCH_MEDIA_SELECT = 0xB5, // Launch Media Select Key
    LKey_LAUNCH_APP1 = 0xB6, // Launch Application 1 Key
    LKey_LAUNCH_APP2 = 0xB7, // Launch Application 2 Key
    LKey_UNKNOWN = 0xFF // 未知键码
};


#endif // DEFINES_H
