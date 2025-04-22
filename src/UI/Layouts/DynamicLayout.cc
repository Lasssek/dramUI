#include "DynamicLayout.hh"
#include <assert.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

DynamicLayout::DynamicLayout(std::shared_ptr<ParentProvider> parent, 
    int x, int y,
    Size dynamicWidth, Size dynamicHeight,
    int gap, LayoutMode mode) : m_mode(mode) {

    m_x = x;
    m_y = y;

    assert(("Parent must be a non null value", parent.get() != nullptr));

    m_parent = parent;

    m_dynamicHeight = dynamicHeight;
    m_dynamicWidth  = dynamicWidth;
    
    m_gap = gap;

    CalculateSize();
}

void DynamicLayout::UpdateHierarchy() {
    CalculateSize();
    PositionWidgets();

    for (auto& widget : m_widgets) {
        if (auto dynWidget = std::dynamic_pointer_cast<DynamicLayout>(widget)) {
            dynWidget->UpdateHierarchy();
        }
    }
}

void DynamicLayout::CalculateSize() {
    for (auto& widget : m_widgets) {
        if (auto childLayout = std::dynamic_pointer_cast<DynamicLayout>(widget)) {
            childLayout->CalculateSize();
        }
    }
    
    if (m_dynamicHeight == Size::None && m_dynamicWidth == Size::None) return;

    if (m_dynamicWidth  == Size::MatchParent) m_width  = m_parent->GetWidth()  - m_x;
    if (m_dynamicHeight == Size::MatchParent) m_height = m_parent->GetHeight() - m_y;

    if (m_mode == LayoutMode::Horizontal && m_dynamicHeight == Size::MatchContent) {
        m_height = 0;
        for (auto& widget : m_widgets) {
            m_height = max(m_height, widget->GetHeight());
        }
    }
    if (m_mode == LayoutMode::Horizontal && m_dynamicWidth == Size::MatchContent) {
        m_width = 0;
        for (auto& widget : m_widgets) {
            m_width += widget->GetWidth() + m_gap;
        }
    }

    if (m_mode == LayoutMode::Vertical && m_dynamicHeight == Size::MatchContent) {
        m_height = 0;
        for (auto& widget : m_widgets) {
            m_height += widget->GetHeight() + m_gap;
        }
    }

    if (m_mode == LayoutMode::Vertical && m_dynamicWidth == Size::MatchContent) {
        m_width = 0;
        for (auto& widget : m_widgets) {
            m_width = max(m_width, widget->GetWidth());
        }
    }
}

int DynamicLayout::CalculateHorizontalStart(int contentWidth) {
    switch (m_horizontalAlignment) {
    case Alignment::Start:  return m_x;
    case Alignment::Center: return m_x + (m_width - contentWidth) / 2;
    case Alignment::End:    return m_x + m_width - contentWidth;
    }

    return m_x;
}
int DynamicLayout::CalculateVerticalStart(int contentHeight) {
    switch (m_verticalAlignment) {
        case Alignment::Start:  return m_y;
        case Alignment::Center: return m_y + (m_height - contentHeight) / 2;
        case Alignment::End:    return m_y + m_height - contentHeight;
    }

    return m_y;
}

void DynamicLayout::PositionWidgets() { 
    if (m_mode == LayoutMode::Vertical) {
        int contentWidth = 0;
        int totalHeight = 0;
    
        for (auto& widget : m_widgets) {
            totalHeight += widget->GetHeight();
    
            contentWidth = max(contentWidth, widget->GetWidth());
            if (&widget != &m_widgets.back()) {
                totalHeight += m_gap;
            }
        }

        int startY = CalculateVerticalStart(totalHeight);
        int currentY = startY;

        for (auto& widget : m_widgets) {
            int widgetX = CalculateHorizontalStart(widget->GetWidth());

            widget->SetPosition(widgetX, currentY);
            currentY += widget->GetHeight() + m_gap;
        }
    } else {
        int totalWidth = 0;
        int contentHeight = 0;
        
        for (auto& widget : m_widgets) {
            totalWidth += widget->GetWidth();
            contentHeight = max(contentHeight, widget->GetHeight());
            
            if (&widget != &m_widgets.back()) {
                totalWidth += m_gap;
            }
        }

        int startX = CalculateHorizontalStart(totalWidth);
        int currentX = startX;

        for (auto& widget : m_widgets) {
            int widgetY = CalculateVerticalStart(widget->GetHeight());

            widget->SetPosition(currentX, widgetY);
            currentX += widget->GetWidth() + m_gap;
        }
    }

    for (auto& widget : m_widgets) {
        if (std::shared_ptr<DynamicLayout> dynWidget = dynamic_pointer_cast<DynamicLayout>(widget)) {
            dynWidget->CalculateSize();
            dynWidget->PositionWidgets();
        }
    }
}

void DynamicLayout::SetHorizontalAlignment(Alignment alignment) { m_horizontalAlignment = alignment; }
void DynamicLayout::SetVerticalAlignment(Alignment alignment)   { m_verticalAlignment   = alignment; }