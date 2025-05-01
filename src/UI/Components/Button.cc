#include "Button.hh"

#include <stdexcept>
#include <format>

Button::Button(std::shared_ptr<IParentProvider> parent, 
        int width, int height, 
        std::wstring_view label,
        int x, int y, 
        bool centerText
    ): m_label(label), m_centerText(centerText) {
        m_x = x;
        m_y = y;

        m_width  = width;
        m_height = height;

        if (parent.get() == nullptr) {
            throw std::runtime_error("You need to specify parent");
        }
        m_parent = parent;
        
        Subscribe(EventType::onMousePress, [this](const Event& e) {
            if (Contains(e.mouse.position)) {
                m_active = true;
                if (m_onClick) m_onClick();
            }
        });

        Subscribe(EventType::onMouseRelease, [this](const Event& e) {
            m_active = false;
        });
        
        Subscribe(EventType::onMouseMove, [this](const Event& e) {
            bool wasHovered = m_hovered;
            m_hovered = Contains(e.mouse.position);

            if (m_hovered  && !wasHovered && m_onHoverIn)  m_onHoverIn();
            if (!m_hovered &&  wasHovered && m_onHoverOut) m_onHoverOut();
        });   
        
        m_activeColor = ConsoleBuffer::MakeConsoleColor(ConsoleBuffer::WHITE, ConsoleBuffer::BLUE);
        m_passiveColor = ConsoleBuffer::MakeConsoleColor(ConsoleBuffer::WHITE, ConsoleBuffer::BLACK);
        m_hoveredColor = ConsoleBuffer::MakeConsoleColor(ConsoleBuffer::WHITE, ConsoleBuffer::GREEN);
};

void Button::Draw(ConsoleBuffer& buffer) {
    WORD color = m_passiveColor;

    if (m_hovered) color = m_hoveredColor;
    if (m_active)  color = m_activeColor;

    size_t labelLength = m_label.size();

    int offset = 0;
    if (m_centerText) offset = (m_width - labelLength) / 2;
    const int borderOffset = (m_border != BorderType::None) ? 1 : 0;

    std::pair<int, int> textOffset = DrawBorder(buffer);
    const int textOffsetX = m_centerText ? (textOffset.first - labelLength) / 2 : borderOffset;

    for (size_t i = 0; i < labelLength; ++i) {
        const int xPos = m_x + textOffsetX + i;

        buffer.Draw(xPos, m_y + borderOffset, m_label[i], color);
    }
}

void Button::HandleEvent(Event& event) {
    auto it = m_handlers.find(event.type);

    if (it != m_handlers.end()) {
        auto handlers = it->second;

        for (auto& handler : handlers) {
            handler(event);
        }
    }
}

void Button::CalculateSize() {
    if (m_dynamicHeight == Size::None && m_dynamicWidth == Size::None) return;

    if (m_dynamicWidth  == Size::MatchParent) m_width  = m_parent->GetWidth()  - m_x;
    if (m_dynamicHeight == Size::MatchParent) m_height = m_parent->GetHeight() - m_y;
    if (m_dynamicHeight == Size::MatchContent && m_border == BorderType::None) {
        m_height = 1;
    }
    else if (m_dynamicHeight == Size::MatchContent && m_border != BorderType::None &&
        m_height < 3) {
       m_height = 3; 
    }

    const int borderOffset = (m_border != BorderType::None) ? 2 : 0;
    if (m_dynamicWidth  == Size::MatchContent) m_width = m_label.size() + borderOffset;
}

void Button::SetLabel(std::wstring_view label) {
    m_label = label;
    CalculateSize();
}

void Button::SetTextCentering(bool center) {
    m_centerText = center;
}

void Button::SetOnClick(std::function<void()>&& callback)    { m_onClick    = callback; }
void Button::SetOnHoverIn(std::function<void()>&& callback)  { m_onHoverIn  = callback; }
void Button::SetOnHoverOut(std::function<void()>&& callback) { m_onHoverOut = callback; }