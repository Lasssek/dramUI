#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>

#include "EventType.hh"
#include "../ConsoleBuffer.hh"
#include "IParentProvider.hh"

enum class Size {
    MatchParent  = 0,
    MatchContent = 1,
    None         = 2,
};

enum class BorderType {
    None    = 0,
    Square  = 1,
    Rounded = 2
};

// Abstract class for all widgets
class Widget : public IParentProvider {
public:
    virtual void Draw(ConsoleBuffer& buffer) = 0;
    virtual void HandleEvent(Event& event) = 0;
    virtual void CalculateSize() = 0;
    virtual ~Widget() = default;

    bool Contains(COORD pos) const {
        return pos.X >= m_x && pos.X < m_x + m_width &&
               pos.Y >= m_y && pos.Y < m_y + m_height;
    }
    void SetDynamicSize(Size dynamicWidth, Size dynamicHeight) { 
        m_dynamicWidth  = dynamicWidth;
        m_dynamicHeight = dynamicHeight;
        CalculateSize();
    }

    void SetPosition(int x, int y) { m_x = x; m_y = y; }
    void SetSize(int width, int height) { m_width = width; m_height = height; }
    int GetWidth() { return m_width; }
    int GetHeight() { return m_height; }
    int GetX() { return m_x; }
    int GetY() { return m_y; }
    void SetBorder(BorderType border) { m_border = border; CalculateSize(); }
    BorderType GetBorder() { return m_border; }

    template<typename T>
    void Subscribe(EventType type, T&& callback) {
        m_handlers[type].emplace_back(callback);
    }

    std::pair<int, int> DrawBorder(
        ConsoleBuffer& buffer, 
        ConsoleBuffer::ConsoleColor color = ConsoleBuffer::LIGHT_GRAY
    ) {
        wchar_t topLeft;
        wchar_t topRight;
        wchar_t botLeft;
        wchar_t botRight;
        wchar_t horLine;
        wchar_t verLine;

        switch(m_border) {
            case BorderType::None: return { 0, 0 };
            case BorderType::Rounded: 
                topLeft  = L'╭';
                topRight = L'╮';
                botLeft  = L'╰';
                botRight = L'╯';
                horLine  = L'─';
                verLine  = L'│';
                break;
            case BorderType::Square: 
                topLeft  = L'┌';
                topRight = L'┐';
                botLeft  = L'└';
                botRight = L'┘';
                horLine  = L'─';
                verLine  = L'│';
                break;
        }
        
        buffer.Draw(m_x, m_y, topLeft, color);
        for (int i = 1; i < m_width; ++i) {
            buffer.Draw(m_x + i, m_y, horLine, color);
        }
        buffer.Draw(m_x + m_width - 1, m_y, topRight, color);
    
        buffer.Draw(m_x, m_y + m_height - 1, botLeft, color);
        for (int i = 1; i < m_width; ++i) {
            buffer.Draw(m_x + i, m_y + m_height - 1, horLine, color);
        }
        buffer.Draw(m_x + m_width - 1, m_y + m_height - 1, botRight, color);
    
        for (int y = m_y + 1; y < m_y + m_height - 1; ++y) {
            buffer.Draw(m_x, y, verLine, color);
            buffer.Draw(m_x + m_width - 1, y, verLine, color);
        }
                
        const int textY = m_y + (m_height / 2);
        const int avaibleWidth = m_width - 2;

        return { avaibleWidth, textY };
    }
protected:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    Size m_dynamicWidth  = Size::None;
    Size m_dynamicHeight = Size::None;
    BorderType m_border  = BorderType::None;

    std::shared_ptr<IParentProvider> m_parent;
    std::unordered_map<EventType, std::vector<std::function<void(const Event&)>>> m_handlers;
};
