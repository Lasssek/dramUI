#pragma once

#include "../Layout.hh"

class DynamicLayout : public Layout {
public:
    enum class Alignment {
        Start  = 0,
        Center = 1,
        End    = 2
    };
    enum class LayoutMode {
        Horizontal = 0,
        Vertical   = 1,
    };

    DynamicLayout(std::shared_ptr<ParentProvider> parent, 
        int x, int y, 
        Size dynamicWidth, Size dynamicHeight, 
        int gap = 0, LayoutMode mode = LayoutMode::Vertical);
    void PositionWidgets();
    void CalculateSize();
    void UpdateHierarchy();

    void SetHorizontalAlignment(Alignment alignment);
    void SetVerticalAlignment(Alignment alignment);

private:
    int CalculateHorizontalStart(int contentWidth);
    int CalculateVerticalStart(int contentHeight);

    LayoutMode m_mode;
    Alignment m_horizontalAlignment = Alignment::Start;
    Alignment m_verticalAlignment = Alignment::Start;
    int m_gap;
};  