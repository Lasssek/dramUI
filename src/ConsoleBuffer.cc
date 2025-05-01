#include "ConsoleBuffer.hh"


ConsoleBuffer::ConsoleBuffer(short width, short height) : m_size{width, height} {
    m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD prevMode;
    GetConsoleMode(m_handle, &prevMode);
    SetConsoleMode(m_handle, prevMode & ~ENABLE_QUICK_EDIT_MODE);

    m_buffer = new CHAR_INFO[width * height];
    Clear();
}

ConsoleBuffer::ConsoleBuffer() {
    m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD prevMode;
    GetConsoleMode(m_handle, &prevMode);
    SetConsoleMode(m_handle, prevMode & ~ENABLE_QUICK_EDIT_MODE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(m_handle, &csbi);

    m_size = csbi.dwMaximumWindowSize;

    m_buffer = new CHAR_INFO[m_size.X * m_size.Y];
    Clear();
}

void ConsoleBuffer::Clear(wchar_t c, WORD attr) {
    for (int i = 0; i < m_size.X * m_size.Y; ++i) {
        m_buffer[i].Char.UnicodeChar = c;
        m_buffer[i].Attributes = attr;
    }
}

void ConsoleBuffer::Draw(int x, int y, wchar_t c, WORD attr) {
    if (x < 0 || x >= m_size.X ||
        y < 0 || y >= m_size.Y) return;

    m_buffer[y * m_size.X + x].Char.UnicodeChar = c;
    m_buffer[y * m_size.X + x].Attributes = attr;
}

Vector2D ConsoleBuffer::GetSize() {
    return { m_size.X, m_size.Y };
}

void ConsoleBuffer::Render() {
    SMALL_RECT rect = { 0, 0, m_size.X, m_size.Y };
    WriteConsoleOutputW(m_handle, m_buffer, m_size, {0, 0}, &rect);
}

ConsoleBuffer::~ConsoleBuffer() { delete[] m_buffer; }