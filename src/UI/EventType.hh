#ifndef EVENT_TYPE_H
#define EVENT_TYPE_H

#include <windows.h>

enum class EventType {
    onMousePress   = 0,
    onMouseRelease = 1,
    onMouseMove    = 2,
    onKeyPress     = 3,
    onKeyRelease   = 4,
    onFocusIn      = 5,
    onFocusOut     = 6
};

struct MouseEvent {
    COORD position;
    DWORD buttons;
    DWORD flags;
};

struct KeyEvent {
    WORD key;
    CHAR asciiChar;
    DWORD controlKeyState;
};

struct Event {
    EventType type;
    union {
        MouseEvent mouse;
        KeyEvent keyboard;
    };
};

#endif