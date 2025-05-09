#pragma once

#include "../Widget.hh"
#include <string>
#include <memory>

class Button : public Widget {
public:
    Button(std::shared_ptr<IParentProvider> parent, 
        int width, int height,
        std::wstring_view label,
        int x = 0, int y = 0,
        bool centerText = false
    );

    void Draw(ConsoleBuffer& buffer);
    void HandleEvent(Event& event);
    void CalculateSize();

    void SetActiveColor();
    void SetPasiveColor();
    void SetHoveredColor();
    void SetAllColors();

    void SetLabel(std::wstring_view label);
    void SetTextCentering(bool center);

    void SetOnClick(std::function<void()>&& callback);
    void SetOnHoverIn(std::function<void()>&& callback);
    void SetOnHoverOut(std::function<void()>&& callback); 

private:
    std::wstring m_label;
    bool m_active  = false;
    bool m_hovered = false;
    bool m_centerText;

    WORD m_activeColor;
    WORD m_passiveColor;
    WORD m_hoveredColor;

    std::function<void()> m_onClick;
    std::function<void()> m_onHoverIn;
    std::function<void()> m_onHoverOut;
};
