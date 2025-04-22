#include "TextLabel.hh"
#include <assert.h>

TextLabel::TextLabel(std::shared_ptr<ParentProvider> parent, int width, int height, std::string_view label, int x, int y, bool centerText)
    : m_label(label) {
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
    if (m_dynamicHeight == Size::MatchContent) {
        m_height = 1;
    }
    if (m_dynamicWidth  == Size::MatchContent) m_width = m_label.size();
}

void TextLabel::Draw(ConsoleBuffer& buffer) {
    size_t labelLength = m_label.size();
    int offset = 0;

    if (m_centerText) offset = (m_width - labelLength) / 2;

    for (size_t i = 0; i < m_width; ++i) {
        char c = ' ';

        if (i >= offset && i < offset + labelLength) {
            size_t labelIndex = i - offset;

            if (labelIndex < labelLength) c = m_label[labelIndex];
        }

        buffer.Draw(m_x + i, m_y, c, m_color);
    }
}

void TextLabel::SetTextCentering(bool center) {
    m_centerText = center;
}

void TextLabel::SetLabel(std::string_view label) {
    m_label = label;
    CalculateSize();
}