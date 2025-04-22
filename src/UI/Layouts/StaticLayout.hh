#pragma once

#include "../Layout.hh"

class StaticLayout : public Layout {
public:
    StaticLayout();
    void PositionWidgets();
    void CalculateSize();
    void UpdateHierarchy();

private:
};