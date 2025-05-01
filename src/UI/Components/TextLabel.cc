#include "TextLabel.hh"
#include <assert.h>

TextLabel::TextLabel(
        std::shared_ptr<IParentProvider> parent, 
        int width, int height, 
        std::wstring_view label, 
        int x, int y, 
        bool centerText
    ) : m_label(label) {

    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;

    assert(("Parent must be a non null value", parent.get() != nullptr));

    m_parent = parent;

    m_centerText = centerText;
    m_color = ConsoleBuffer::MakeConsoleColor(ConsoleBuffer::LIGHT_GRAY, ConsoleBuffer::BLACK);
}

void TextLabel::HandleEvent(Event& event) {
    return;
}

void TextLabel::CalculateSize() {
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

void TextLabel::Draw(ConsoleBuffer& buffer) {
    size_t labelLength = m_label.size();

    int offset = 0;
    if (m_centerText) offset = (m_width - labelLength) / 2;
    const int borderOffset = (m_border != BorderType::None) ? 1 : 0;

    std::pair<int, int> textOffset = DrawBorder(buffer);
    const int textOffsetX = m_centerText ? (textOffset.first - labelLength) / 2 : borderOffset;

    for (size_t i = 0; i < labelLength; ++i) {
        const int xPos = m_x + textOffsetX + i;

        buffer.Draw(xPos, m_y + borderOffset, m_label[i], m_color);
    }
}

void TextLabel::SetTextCentering(bool center) {
    m_centerText = center;

}

void TextLabel::SetLabel(std::wstring_view label) {
    m_label = label;
    CalculateSize();

}