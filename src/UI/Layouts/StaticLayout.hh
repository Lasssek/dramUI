#pragma once

#include "../Layout.hh"

class StaticLayout : public Layout {
public:
    StaticLayout(std::shared_ptr<IParentProvider> parent,
            int x, int y,
            int width, int height);

    //This doesn't work on StaticLayout because there isn't any positioning happening
    void PositionWidgets();
    void CalculateSize() override {};
    void UpdateHierarchy();
};