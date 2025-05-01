#pragma once

#include "../Widget.hh"
#include <memory>
#include <string>

class TextLabel : public Widget {
public:
    TextLabel(
        std::shared_ptr<IParentProvider> parent, 
        int width, int height, 
        std::wstring_view label, 
        int x = 0, int y = 0, 
        bool centerText = false
    ); 

    void SetLabel(std::wstring_view label);
    void SetTextCentering(bool center);

    void CalculateSize();
    void Draw(ConsoleBuffer& buffer);
    void HandleEvent(Event& event);

private:
    std::wstring m_label;
    bool m_centerText  = false;
    WORD m_color;
};