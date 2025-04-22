#ifndef WIDGET_H
#define WIDGET_H

#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>

#include "EventType.hh"
#include "../ConsoleBuffer.hh"
#include "ParentProvider.hh"

enum class Size {
    MatchParent  = 0,
    MatchContent = 1,
    None         = 2,
};

// Abstract class for all widgets
class Widget : public ParentProvider {
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

    template<typename T>
    void Subscribe(EventType type, T&& callback) {
        m_handlers[type].emplace_back(callback);
    }
protected:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    Size m_dynamicWidth  = Size::None;
    Size m_dynamicHeight = Size::None;

    std::shared_ptr<ParentProvider> m_parent;
    std::unordered_map<EventType, std::vector<std::function<void(const Event&)>>> m_handlers;
};
#endif