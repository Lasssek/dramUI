#include "StaticLayout.hh"

StaticLayout::StaticLayout(std::shared_ptr<IParentProvider> parent,
                    int x, int y,
                    int width, int height) {
    m_parent = parent;
    m_x      = x;
    m_y      = y;
    m_width  = width;
    m_height = height;
}

void StaticLayout::UpdateHierarchy() {
    PositionWidgets();
    for (auto& [_, widget] : m_widgets) {
        if (auto layout = std::dynamic_pointer_cast<Layout>(widget)) {
            layout->UpdateHierarchy();
        }
    }
}

void StaticLayout::PositionWidgets() {
    for (auto& [_, widget] : m_widgets) {
        widget->SetPosition(m_x + widget->GetX(), m_y + widget->GetY());
    }
};