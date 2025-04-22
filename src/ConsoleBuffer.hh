#ifndef CONSOLE_BUFFER_H
#define CONSOLE_BUFFER_H

#include <windows.h>
#include <vector>

struct Vector2D {
    int width;
    int height;
};

class ConsoleBuffer {
public:
    enum ConsoleColor {
        BLACK          = 0x0,
        DARK_BLUE      = 0x1,
        DARK_GREEN     = 0x2,
        DARK_CYAN      = 0x3,
        DARK_RED       = 0x4,
        DARK_MAGENTA   = 0x5,
        DARK_YELLOW    = 0x6,
        LIGHT_GRAY     = 0x7,
        GRAY           = 0x8,
        BLUE           = 0x9,
        GREEN          = 0xA,
        CYAN           = 0xB,
        RED            = 0xC,
        MAGENTA        = 0xD,
        YELLOW         = 0xE,
        WHITE          = 0xF
    };

    ConsoleBuffer(short width, short height);
    ConsoleBuffer();
    void Clear(char c = ' ', WORD attr = 0x07);
    void Draw(int x, int y, char c, WORD attr = 0x07);
    Vector2D GetSize();
    void Render();
    ~ConsoleBuffer();

    static WORD MakeConsoleColor(ConsoleColor text, ConsoleColor background) {
        return (background << 4) | text;
    }
private:
    HANDLE m_handle;
    COORD m_size;
    CHAR_INFO* m_buffer;
};

#endif