#ifndef TEXT_LABEL_H
#define TEXT_LABEL_H

#include "../Widget.hh"
#include <memory>
#include <string>

class TextLabel : public Widget {
public:
    TextLabel(std::shared_ptr<ParentProvider> parent, int width, int height, std::string_view label, int x = 0, int y = 0, bool centerText = false); 
    
    void SetLabel(std::string_view label);
    void SetTextCentering(bool center);

    void CalculateSize();
    void Draw(ConsoleBuffer& buffer);
    void HandleEvent(Event& event);

private:
    std::string m_label;
    bool m_centerText  = false;
    WORD m_color;
};

#endif